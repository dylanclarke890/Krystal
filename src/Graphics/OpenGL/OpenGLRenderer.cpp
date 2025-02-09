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
#include "MTL/Matrices/Ext/Inverse.hpp"
#include "MTL/Matrices/Ext/Transpose.hpp"
#include "MTL/Matrices/Mat3x3.hpp"

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
        auto modelMatrix = transform.GetMatrix();
        auto normalMatrix = MTL::Transpose(MTL::Inverse(Mat3(modelMatrix)));

        SetUniform(program.GetNativeHandle(), "u_Model", modelMatrix);
        SetUniform(program.GetNativeHandle(), "u_Normal", normalMatrix);

        SetUniform(program.GetNativeHandle(), "u_View", camera.GetView());
        SetUniform(program.GetNativeHandle(), "u_Projection", camera.GetProjection());
        SetUniform(program.GetNativeHandle(), "u_CameraPosition", camera.GetPosition());

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

  void OpenGLRenderer::UpdateLightBuffer() noexcept
  {
    BufferWriter lightBufferWriter(*_lightBuffer);
    Vec4 pos {1.2f, 1.0f, -2.0f, 1.0f};
    Vec4 intensity {1.0f};

    lightBufferWriter.Seek(0);
    lightBufferWriter.Write(pos);
    lightBufferWriter.Write(intensity);
  }

  PhongMaterialData OpenGLRenderer::GetBufferDataFromPhongMaterial(const PhongMaterial &mat,
                                                                   int blankTextureIndex) noexcept
  {
    // TODO: we need to get the index differently once we have cubemaps.
    
    PhongMaterialData data;

    auto ambientTexture = mat.GetAmbientTexture();
    auto diffuseTexture = mat.GetDiffuseTexture();
    auto specularTexture = mat.GetSpecularTexture();

    data.Shininess = mat.GetShininess();
    data.AmbientTexture = ambientTexture.IsValid() ? ambientTexture.Id() : blankTextureIndex;
    data.DiffuseTexture = diffuseTexture.IsValid() ? diffuseTexture.Id() : blankTextureIndex;
    data.SpecularTexture = specularTexture.IsValid() ? specularTexture.Id() : blankTextureIndex;

    return data;
  }
}