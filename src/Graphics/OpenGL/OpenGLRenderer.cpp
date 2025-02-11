#include "Graphics/OpenGL/OpenGLRenderer.hpp"
#include "Debug/Macros.hpp"
#include "Graphics/BufferWriter.hpp"
#include "Graphics/Cameras/Camera.hpp"
#include "Graphics/Lights/LightData.hpp"
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
#include "MTL/Matrices/Ext/Inverse.hpp"
#include "MTL/Matrices/Ext/Transpose.hpp"
#include "MTL/Matrices/Mat3x3.hpp"

namespace
{
  using namespace Krys::Gfx;

  static TextureHandle GetWhiteTexture(TextureManager &tm) noexcept
  {
    static TextureHandle handle;

    if (!handle.IsValid())
    {
      handle = tm.CreateFlatColourTexture(Colours::White);
    }

    return handle;
  }

  static TextureHandle GetBlackTexture(TextureManager &tm) noexcept
  {
    static TextureHandle handle;

    if (!handle.IsValid())
    {
      handle = tm.CreateFlatColourTexture(Colours::Black);
    }

    return handle;
  }
}

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

    _lightBufferHandle = _ctx.GraphicsContext->CreateShaderStorageBuffer(
      _ctx.GraphicsContext->GetDeviceCapabilities().MaxShaderStorageBlockSize);
    _lightBuffer = _ctx.GraphicsContext->GetShaderStorageBuffer(_lightBufferHandle);
  }

  void OpenGLRenderer::BeforeRender() noexcept
  {
    UpdateMaterialBuffers();
    UpdateTextureTable();
    UpdateLightBuffer();

    static_cast<OpenGLShaderStorageBuffer &>(*_phongMaterialBuffer).Bind(0);
    static_cast<OpenGLShaderStorageBuffer &>(*_textureTable).Bind(1);
    static_cast<OpenGLShaderStorageBuffer &>(*_lightBuffer).Bind(2);
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
        auto &meshNode = *static_cast<MeshNode *>(node);
        auto &mesh = *_ctx.MeshManager->GetMesh(meshNode.GetMesh());
        auto &material = *_ctx.MaterialManager->GetMaterial(activeMaterial);

        // Resetting it back for the next mesh.
        activeMaterial = _ctx.MaterialManager->GetDefaultPhongMaterial();

        auto &program =
          static_cast<OpenGLProgram &>(*_ctx.GraphicsContext->GetProgram(material.GetProgram()));
        program.Bind();

        // TODO: we need to get the index differently once we add PBR materials.
        SetUniform<int>(program.GetNativeHandle(), "u_MaterialIndex", material.GetHandle().Id());

        auto transform = parentTransform * node->GetLocalTransform();
        auto modelMatrix = transform.GetMatrix();
        auto normalMatrix = MTL::Transpose(MTL::Inverse(Mat3(modelMatrix)));

        SetUniform(program.GetNativeHandle(), "u_Model", modelMatrix);
        SetUniform(program.GetNativeHandle(), "u_Normal", normalMatrix);

        SetUniform(program.GetNativeHandle(), "u_View", camera.GetView());
        SetUniform(program.GetNativeHandle(), "u_Projection", camera.GetProjection());
        SetUniform(program.GetNativeHandle(), "u_CameraPosition", camera.GetPosition());
        SetUniform<int>(program.GetNativeHandle(), "u_LightCount",
                        static_cast<int>(_ctx.LightManager->GetLights().size()));

        mesh.Bind();
        if (mesh.IsIndexed())
          _ctx.GraphicsContext->DrawElements(meshNode.GetType(), static_cast<uint32>(mesh.GetCount()));
        else
          _ctx.GraphicsContext->DrawArrays(meshNode.GetType(), static_cast<uint32>(mesh.GetCount()));
      }
      default: break;
    }
  }

  void OpenGLRenderer::UpdateMaterialBuffers() noexcept
  {
    BufferWriter phongBufferWriter(*_phongMaterialBuffer);

    for (auto &[handle, material] : _ctx.MaterialManager->GetMaterials())
    {
      if (!material->IsDirty())
        continue;

      if (material->GetType() == MaterialType::Phong)
      {
        // TODO: we need to get the index differently once we add PBR materials.
        auto index = handle.Id();
        auto &phong = static_cast<PhongMaterial &>(*material);

        phongBufferWriter.Seek(index * sizeof(PhongMaterialData));
        PhongMaterialData data;

        auto ambientTexture = phong.GetAmbientTexture();
        auto diffuseTexture = phong.GetDiffuseTexture();
        auto specularTexture = phong.GetSpecularTexture();
        auto emissionTexture = phong.GetEmissionTexture();

        data.Shininess = phong.GetShininess();
        // TODO: we need to get the index differently once we have cubemaps.
        data.AmbientTexture =
          ambientTexture.IsValid() ? ambientTexture.Id() : GetWhiteTexture(*_ctx.TextureManager).Id();
        data.DiffuseTexture =
          diffuseTexture.IsValid() ? diffuseTexture.Id() : GetWhiteTexture(*_ctx.TextureManager).Id();
        data.SpecularTexture =
          specularTexture.IsValid() ? specularTexture.Id() : GetWhiteTexture(*_ctx.TextureManager).Id();
        data.EmissionTexture =
          emissionTexture.IsValid() ? emissionTexture.Id() : GetBlackTexture(*_ctx.TextureManager).Id();

        phongBufferWriter.Write(data);
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
    auto *whiteTexture = _ctx.TextureManager->GetTexture(GetWhiteTexture(*_ctx.TextureManager));
    for (uint32 i = 0; i < maxIndex; ++i)
    {
      auto it = std::find_if(textures.begin(), textures.end(),
                             [i](const TextureWithIndex &tex) { return tex.Index == i; });
      if (it == textures.end())
        textures.emplace_back(TextureWithIndex {whiteTexture, i});
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

  void OpenGLRenderer::UpdateLightBuffer() noexcept
  {
    BufferWriter lightBufferWriter(*_lightBuffer);

    for (const auto &[handle, light] : _ctx.LightManager->GetLights())
    {
      if (!light->IsDirty())
        continue;

      auto index = handle.Id();
      lightBufferWriter.Seek(index * sizeof(LightData));

      const auto &lightData = light.get()->GetData();
      lightBufferWriter.Write(lightData);

      light->ClearIsDirtyFlag();
    }
  }
}