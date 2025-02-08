#include "Graphics/OpenGL/OpenGLRenderer.hpp"
#include "Debug/Macros.hpp"
#include "Graphics/BufferWriter.hpp"
#include "Graphics/Cameras/Camera.hpp"
#include "Graphics/Materials/PhongMaterial.hpp"
#include "Graphics/OpenGL/OpenGLBuffer.hpp"
#include "Graphics/OpenGL/OpenGLGraphicsContext.hpp"
#include "Graphics/OpenGL/OpenGLMesh.hpp"
#include "Graphics/OpenGL/OpenGLMeshManager.hpp"
#include "Graphics/OpenGL/OpenGLProgram.hpp"
#include "Graphics/OpenGL/OpenGLTexture.hpp"
#include "Graphics/OpenGL/OpenGLTextureManager.hpp"
#include "Graphics/Scene/MaterialNode.hpp"
#include "Graphics/Scene/MeshNode.hpp"
#include "Graphics/Scene/Node.hpp"

namespace Krys::Gfx::OpenGL
{
  OpenGLRenderer::OpenGLRenderer(RenderContext context) noexcept : Renderer(context)
  {
  }

  void OpenGLRenderer::Init() noexcept
  {
    _phongMaterialBufferHandle = _ctx.GraphicsContext->CreateShaderStorageBuffer(
      _ctx.GraphicsContext->GetDeviceCapabilities().MaxShaderStorageBlockSize);
    _textureTableHandle = _ctx.GraphicsContext->CreateShaderStorageBuffer(
      _ctx.GraphicsContext->GetDeviceCapabilities().MaxShaderStorageBlockSize);
    _phongMaterialBuffer = _ctx.GraphicsContext->GetShaderStorageBuffer(_phongMaterialBufferHandle);
    _textureTable = _ctx.GraphicsContext->GetShaderStorageBuffer(_textureTableHandle);
  }

  void OpenGLRenderer::BeforeRender() noexcept
  {
    UpdateMaterialBuffers();
    UpdateTextureTable();

    static_cast<OpenGLShaderStorageBuffer &>(*_phongMaterialBuffer).Bind(0);
    static_cast<OpenGLShaderStorageBuffer &>(*_textureTable).Bind(1);
  }

  void OpenGLRenderer::Render(Node *node, const Transform &parentTransform, Camera &camera) noexcept
  {
    if (!node->IsLeaf())
    {
      for (auto &child : node->GetChildren())
        Render(child.get(), parentTransform * node->GetLocalTransform(), camera);
    }

    static MaterialHandle activeMaterial = _ctx.MaterialManager->GetDefaultPhongMaterial();

    switch (node->GetNodeType())
    {
      case SID("material"):
      {
        activeMaterial = static_cast<MaterialNode *>(node)->GetMaterial();
        break;
      }
      case SID("mesh"):
      {
        auto *meshNode = static_cast<MeshNode *>(node);
        auto &mesh = *_ctx.MeshManager->GetMesh(meshNode->GetMesh());

        auto &material = *_ctx.MaterialManager->GetMaterial(activeMaterial);
        activeMaterial = _ctx.MaterialManager->GetDefaultPhongMaterial();

        auto &program =
          static_cast<OpenGLProgram &>(*_ctx.GraphicsContext->GetProgram(material.GetProgram()));
        program.Bind();

        // TODO: we need to get the index differently once we add PBR materials.
        SetUniform<int>(program.GetNativeHandle(), "u_MaterialIndex", material.GetHandle().Id());

        auto transform = parentTransform * node->GetLocalTransform();
        SetUniform(program.GetNativeHandle(), "u_Transform", transform.GetMatrix());

        SetUniform(program.GetNativeHandle(), "u_View", camera.GetView());
        SetUniform(program.GetNativeHandle(), "u_Projection", camera.GetProjection());

        mesh.Bind();
        if (mesh.IsIndexed())
          _ctx.GraphicsContext->DrawElements(meshNode->GetType(), static_cast<uint32>(mesh.GetCount()));
        else
          _ctx.GraphicsContext->DrawArrays(meshNode->GetType(), static_cast<uint32>(mesh.GetCount()));
      }
      default: break;
    }
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