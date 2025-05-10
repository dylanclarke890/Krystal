#include "Graphics/OpenGL/OpenGLRenderer.hpp"
#include "Graphics/BufferWriter.hpp"
#include "Graphics/Materials/PhongMaterial.hpp"
#include "Graphics/OpenGL/OpenGLBuffer.hpp"
#include "Graphics/OpenGL/OpenGLGraphicsContext.hpp"
#include "Graphics/OpenGL/OpenGLMesh.hpp"
#include "Graphics/OpenGL/OpenGLMeshManager.hpp"
#include "Graphics/OpenGL/OpenGLProgram.hpp"
#include "Graphics/OpenGL/OpenGLTexture.hpp"
#include "Graphics/OpenGL/OpenGLTextureManager.hpp"

namespace Krys::Gfx::OpenGL
{
  OpenGLRenderer::OpenGLRenderer(RenderContext context) noexcept : Renderer(context)
  {
  }

  void OpenGLRenderer::Init() noexcept
  {
    _phongMaterialBufferHandle = _ctx.GraphicsContext->CreateShaderStorageBuffer(320);
    _textureTableHandle = _ctx.GraphicsContext->CreateShaderStorageBuffer(4'000);
    _phongMaterialBuffer = _ctx.GraphicsContext->GetShaderStorageBuffer(_phongMaterialBufferHandle);
    _textureTable = _ctx.GraphicsContext->GetShaderStorageBuffer(_textureTableHandle);

    glObjectLabel(GL_BUFFER,
                  static_cast<OpenGLShaderStorageBuffer &>(*_phongMaterialBuffer).GetNativeHandle(), -1,
                  "Phong Material Buffer");

    glObjectLabel(GL_BUFFER, static_cast<OpenGLShaderStorageBuffer &>(*_textureTable).GetNativeHandle(), -1,
                  "Texture Table Buffer");
  }

  void OpenGLRenderer::Execute() noexcept
  {
    UpdateMaterialBuffers();
    UpdateTextureTable();

    static_cast<OpenGLShaderStorageBuffer &>(*_phongMaterialBuffer).Bind(0);
    static_cast<OpenGLShaderStorageBuffer &>(*_textureTable).Bind(1);

    for (const auto &command : _commands)
    {
      auto &program = static_cast<OpenGLProgram &>(*_ctx.GraphicsContext->GetProgram(command.Program));
      program.Bind();

      KRYS_ASSERT(command.Mesh.IsValid(), "Mesh was not provided.");
      KRYS_ASSERT(command.Material.IsValid(), "Material was not provided.");

      auto &mesh = *_ctx.MeshManager->GetMesh(command.Mesh);

      auto &material = *_ctx.MaterialManager->GetMaterial(command.Material);
      switch (material.GetType())
      {
        case MaterialType::Phong:
        {
          auto &phong = static_cast<PhongMaterial &>(material);
          auto &texture =
            static_cast<OpenGLTexture &>(*_ctx.TextureManager->GetTexture(phong.GetAmbientTexture()));

          SetUniform(program.GetNativeHandle(), "u_Texture", texture.GetNativeBindlessHandle());
          SetUniform(program.GetNativeHandle(), "u_AmbientColour", phong.GetAmbientColour());
          break;
        }
        default: KRYS_ASSERT(false, "Unknown material type."); break;
      }

      mesh.Bind();
      if (mesh.IsIndexed())
        _ctx.GraphicsContext->DrawElements(command.Type, static_cast<uint32>(mesh.GetCount()));
      else
        _ctx.GraphicsContext->DrawArrays(command.Type, static_cast<uint32>(mesh.GetCount()));
    }

    _commands.clear();
  }

  void OpenGLRenderer::UpdateMaterialBuffers() noexcept
  {
    BufferWriter phongBufferWriter(*_phongMaterialBuffer);

    auto blankTextureIndex = _ctx.TextureManager->GetBlankTexture().Id();
    for (auto &[handle, material] : _ctx.MaterialManager->GetMaterials())
    {
      if (!material->IsDirty())
        continue;

      if (material->GetType() == MaterialType::Phong)
      {
        auto &phong = static_cast<PhongMaterial &>(*material);
        // TODO: we need to get the index differently once we add PBR materials.
        auto index = handle.Id();

        phongBufferWriter.Seek(index * sizeof(PhongMaterialData));
        phongBufferWriter.Write(GetBufferDataFromPhongMaterial(phong, blankTextureIndex));
      }

      material->ClearIsDirtyFlag();
    }
  }

  struct TextureWithIndex
  {
    const Texture *Texture;
    uint32 Index;
  };

  void OpenGLRenderer::UpdateTextureTable() noexcept
  {
    BufferWriter textureTableWriter(*_textureTable);
    List<TextureWithIndex> textures {};

    std::transform(_ctx.TextureManager->GetTextures().begin(), _ctx.TextureManager->GetTextures().end(),
                   std::back_inserter(textures),
                   [](const auto &element) { return TextureWithIndex {element.second, element.first.Id()}; });

    std::sort(std::begin(textures), std::end(textures),
              [](const TextureWithIndex a, const TextureWithIndex b) { return a.Index < b.Index; });

    auto maxIndex = textures.back().Index;
    auto *blankTexture = _ctx.TextureManager->GetTexture(_ctx.TextureManager->GetBlankTexture());
    for (uint32 i = 0; i < maxIndex; ++i)
    {
      auto it = std::find_if(textures.begin(), textures.end(),
                             [i](const TextureWithIndex &tex) { return tex.Index == i; });
      if (it == textures.end())
        textures.emplace_back(TextureWithIndex {blankTexture, i});
    }

    for (auto &textureWithIndex : textures)
    {
      const auto &tex = static_cast<const OpenGLTexture &>(*textureWithIndex.Texture);
      // TODO: we need to get the index differently once we add cubemaps.
      // Maybe we don't if we treat cubemaps separately here too.
      auto index = textureWithIndex.Index;

      textureTableWriter.Seek(index * sizeof(GLuint64));
      textureTableWriter.Write(tex.GetNativeBindlessHandle());
    }
  }

  PhongMaterialData OpenGLRenderer::GetBufferDataFromPhongMaterial(const PhongMaterial &mat,
                                                                   int blankTextureIndex) noexcept
  {
    PhongMaterialData data;
    data.AmbientColour = mat.GetAmbientColour();
    data.DiffuseColour = mat.GetDiffuseColour();
    data.SpecularColour = mat.GetSpecularColour();
    data.Shininess = mat.GetShininess();

    // TODO: if we don't have a texture use the blank one.
    auto ambientTexture = mat.GetAmbientTexture();
    auto diffuseTexture = mat.GetDiffuseTexture();
    auto specularTexture = mat.GetSpecularTexture();
    // TODO: we need to get the index differently once we have cubemaps.
    data.AmbientTexture = ambientTexture.IsValid() ? ambientTexture.Id() : blankTextureIndex;
    data.DiffuseTexture = diffuseTexture.IsValid() ? diffuseTexture.Id() : blankTextureIndex;
    data.SpecularTexture = specularTexture.IsValid() ? specularTexture.Id() : blankTextureIndex;

    return data;
  }
}