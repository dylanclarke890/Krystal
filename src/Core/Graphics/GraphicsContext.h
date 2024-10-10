#pragma once

#include "Core.h"

#include "Graphics/Assets/Factory.h"
#include "Graphics/Buffer.h"
#include "Graphics/Enums.h"
#include "Graphics/Framebuffer.h"
#include "Graphics/Graphics.h"
#include "Graphics/Shaders/Shader.h"
#include "Graphics/Shaders/ShaderPreprocessor.h"
#include "Graphics/Textures/SubTexture2D.h"
#include "Graphics/Textures/Texture2D.h"
#include "Graphics/Textures/TextureCubemap.h"
#include "Graphics/VertexArray.h"

#include <algorithm>

namespace Krys
{
  struct DeferredRendererData
  {
    Ref<Framebuffer> GBuffer;
    Ref<Texture2D> GPosition, GNormal, GAlbedoSpecular;
  };

  class GraphicsContext
  {
  private:
    Ref<Shader> DefaultMaterialShader;

  public:
    virtual ~GraphicsContext() = default;
    
    virtual void Init() noexcept
    {
      const auto &capabilities = QueryCapabilities();
      Framebuffer::SetDriverLimits(capabilities.MaxFramebufferColorAttachments, capabilities.MaxFramebufferDrawBuffers);
      Texture::SetDriverLimits(capabilities.MaxTextureSize, capabilities.MaxTextureColorSamples, capabilities.MaxTextureDepthSamples);
      VertexBuffer::SetDriverLimits(capabilities.MaxVertexAttributes);

      ShaderPreprocessorTemplateKeys templateKeys;
      templateKeys.SharedUniformBufferBinding = UNIFORM_BUFFER_BINDING_SHARED;
      templateKeys.MaxDirectionalLights = LIGHTING_MAX_DIRECTIONAL_LIGHTS;
      templateKeys.MaxPointLights = LIGHTING_MAX_POINT_LIGHTS;
      templateKeys.MaxSpotLights = LIGHTING_MAX_SPOT_LIGHTS;
      ShaderPreprocessor::SetTemplateKeys(std::move(templateKeys));

      DefaultMaterialShader = CreateShader("shaders/scene-object.vert", "shaders/scene-object.frag");
    }

    virtual const GraphicsCapabilities &QueryCapabilities() noexcept = 0;

#pragma region State Settings

    virtual void SetClearColor(const Vec4 &color) noexcept = 0;
    virtual void Clear(RenderBuffer flags = RenderBuffer::Color) noexcept = 0;
    virtual void BindScreenFramebuffer(FramebufferBindType bindType = FramebufferBindType::ReadAndDraw) noexcept = 0;

    virtual void SetViewport(int width, int height) noexcept = 0;
    virtual void SetMultisamplingEnabled(bool enable) noexcept = 0;
    virtual void SetGammaCorrectionEnabled(bool enable) noexcept = 0;

    virtual void SetFaceCullingEnabled(bool enable) noexcept = 0;
    virtual void SetFaceCulling(CullMode mode) noexcept = 0;
    virtual void SetWindingOrder(WindingOrder mode) noexcept = 0;

    virtual void SetClearDepth(float value) noexcept = 0;
    virtual void SetDepthRange(float dNear, float dFar) noexcept = 0;
    virtual void SetDepthBufferWritingEnabled(bool enable) noexcept = 0;
    virtual void SetDepthTestingEnabled(bool enable) noexcept = 0;
    virtual void SetDepthTestFunc(DepthTestFunc func) noexcept = 0;
    virtual void SetDepthClampingEnabled(bool enable) noexcept = 0;

    virtual void SetStencilTestFunc(StencilTestFunc func, uint8 ref, uint8 mask) noexcept = 0;
    virtual void SetStencilOperation(StencilOperation fail, StencilOperation zFail, StencilOperation zPass) noexcept = 0;
    virtual void SetStencilTestingEnabled(bool enable) noexcept = 0;
    virtual void SetStencilBufferWritingEnabled(bool enable) noexcept = 0;
    /// @brief Similar to `SetStencilBufferWritingEnabled`, but takes a custom mask to be
    /// ANDed with the stencil value to be written.
    virtual void SetStencilBufferBitMask(uint8 mask) noexcept = 0;

    virtual void SetBlendingEnabled(bool enable) noexcept = 0;
    virtual void SetBlendFunc(BlendFactor srcFactor, BlendFactor dstFactor) noexcept = 0;
    virtual void SetBlendFunc(BlendFactor rgbSrcFactor, BlendFactor rgbDstFactor, BlendFactor alphaSrcFactor, BlendFactor alphaDstFactor) noexcept = 0;
    virtual void SetBlendEquation(BlendEquation equation) noexcept = 0;
    virtual void SetBlendColor(Vec4 color) noexcept = 0;

    virtual void SetWireframeModeEnabled(bool enable) noexcept = 0;
#pragma endregion State Settings

#pragma region Graphics Objects

    virtual Ref<IndexBuffer> CreateIndexBuffer(uint32 count) noexcept = 0;
    virtual Ref<IndexBuffer> CreateIndexBuffer(const uint32 *indices, uint32 count) noexcept = 0;
    Ref<IndexBuffer> CreateIndexBuffer(const List<uint32> &indices) noexcept
    {
      return CreateIndexBuffer(&indices[0], static_cast<uint32>(indices.size()));
    }

    // TODO: a pointer to floats is a bit dodgy now, refactor to take a pointer to VertexData instead.
    virtual Ref<VertexBuffer> CreateVertexBuffer(uint32 size) noexcept = 0;
    virtual Ref<VertexBuffer> CreateVertexBuffer(float *vertices, uint32 size) noexcept = 0;

    virtual Ref<InstanceArrayBuffer> CreateInstanceArrayBuffer(uint32 size) noexcept = 0;
    virtual Ref<InstanceArrayBuffer> CreateInstanceArrayBuffer(void *data, uint32 size) noexcept = 0;

    virtual Ref<UniformBuffer> CreateUniformBuffer(uint32 size, uint32 binding) noexcept = 0;
    virtual Ref<UniformBuffer> CreateUniformBuffer(uint32 binding, UniformBufferLayout layout) noexcept = 0;

    virtual Ref<VertexArray> CreateVertexArray() noexcept = 0;
    Ref<VertexArray> CreateVertexArray(Ref<VertexBuffer> vertexBuffer, Ref<IndexBuffer> indexBuffer = nullptr) noexcept
    {
      auto vertexArray = CreateVertexArray();
      vertexArray->AddVertexBuffer(vertexBuffer);
      if (indexBuffer)
        vertexArray->SetIndexBuffer(indexBuffer);
      return vertexArray;
    }

    virtual Ref<Shader> CreateShader() = 0;
    virtual Ref<Shader> CreateShader(const stringview &vertexFilepath, const stringview &fragmentFilepath) = 0;
    virtual Ref<Shader> CreateShader(const stringview &vertexFilepath, const stringview &fragmentFilepath, const stringview &geoFilepath) = 0;

    virtual Ref<Texture2D> CreateTexture2D(const string &filepath) noexcept = 0;
    virtual Ref<SubTexture2D> CreateSubTexture2D(Ref<Texture2D> texture, Vec2 &coords, Vec2 &cellSize, Vec2 &spriteSize) noexcept = 0;
    virtual Ref<TextureCubemap> CreateTextureCubemap(std::array<string, 6> paths) noexcept = 0;
    virtual Ref<TextureCubemap> CreateTextureCubemap(uint width, uint height, TextureInternalFormat internalFormat) noexcept = 0;

    virtual Ref<Framebuffer> CreateFramebuffer(uint32 width, uint32 height, uint32 samples = 1) noexcept = 0;
    Ref<PingPongFramebuffer> CreatePingPongFramebuffer(Ref<Framebuffer> a, Ref<Framebuffer> b) noexcept { return CreateRef<PingPongFramebuffer>(a, b); }

    List<Ref<SceneObject>> CreateSceneObject(const stringview &path) noexcept
    {
      auto importer = Assets::Factory::CreateImporter(path);
      importer->Parse();

      KRYS_ASSERT(importer->GetResult(), "Import failed: %s", importer->GetResult().ErrorMessage.c_str());

      for (auto obj : importer->GetResult().SceneObjects)
      {
        if (!obj->Material)
          obj->Material = CreateMaterial();

        if (!obj->Material->Shader)
          obj->Material->Shader = DefaultMaterialShader;

        if (!obj->Transform)
          obj->Transform = CreateRef<Transform>(Vec3(0.0f), Vec3(1.0f), Vec3(0.0f));
      }

      return importer->GetResult().SceneObjects;
    }

    Ref<SceneObject> CreateSceneObject() noexcept
    {
      auto obj = CreateRef<SceneObject>();
      obj->Material = CreateMaterial();
      obj->Transform = CreateRef<Transform>(Vec3(0.0f), Vec3(1.0f), Vec3(0.0f));
      return obj;
    }

    Ref<Material> CreateMaterial() noexcept
    {
      static int id = 0;

      Ref<Material> material = CreateRef<Material>();
      material->Id = id++;
      material->Shader = DefaultMaterialShader;

      return material;
    }

#pragma endregion Graphics Objects

#pragma region Primitive Drawing
    virtual void DrawVertices(size_t count, PrimitiveType mode = PrimitiveType::Triangles) noexcept = 0;
    virtual void DrawVerticesInstanced(size_t instanceCount, size_t vertexCount, PrimitiveType mode = PrimitiveType::Triangles) noexcept = 0;

    virtual void DrawIndices(size_t count, PrimitiveType mode = PrimitiveType::Triangles) noexcept = 0;
    virtual void DrawIndicesInstanced(size_t instanceCount, size_t indexCount, PrimitiveType mode = PrimitiveType::Triangles) noexcept = 0;
#pragma endregion Primitive Drawing
  };
}