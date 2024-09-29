#pragma once

#include "Core.h"
#include "Buffer.h"
#include "Framebuffer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "Textures/SubTexture2D.h"
#include "Textures/Texture2D.h"
#include "Textures/TextureCubemap.h"
#include "Graphics/Enums.h"

#include <algorithm>

namespace Krys
{
  // TODO: this *could* be more fine-grained. Some of the limits vary based on shader stage.
  struct GraphicsCapabilities
  {
    int MaxDrawBuffers;
    int MaxInputComponents;
    int MaxOutputComponents;
    int MaxTextureImageUnits;
    int MaxTextureSize;
    int MaxUniformComponents;
    int MaxUniformBlocks;
    int MaxVertexAttributes;

    void Log() const
    {
      KRYS_LOG("Graphics Capabilities:");
      KRYS_LOG("MaxDrawBuffers: %d", MaxDrawBuffers);
      KRYS_LOG("MaxInputComponents: %d", MaxInputComponents);
      KRYS_LOG("MaxOutputComponents: %d", MaxOutputComponents);
      KRYS_LOG("MaxTextureImageUnits: %d", MaxTextureImageUnits);
      KRYS_LOG("MaxTextureSize: %d", MaxTextureSize);
      KRYS_LOG("MaxUniformComponents: %d", MaxUniformComponents);
      KRYS_LOG("MaxUniformBlocks: %d", MaxUniformBlocks);
      KRYS_LOG("MaxVertexAttributes: %d", MaxVertexAttributes);
    }
  };

  struct VertexData
  {
    Vec4 Position;
    Vec3 Normal;
    Vec4 Color;
    Vec2 TextureCoords;
    int TextureSlotIndex;
    int SpecularTextureSlotIndex;
    int EmissionTextureSlotIndex;
    int NormalTextureSlotIndex;
    int DisplacementTextureSlotIndex;
    float Shininess;
    Vec3 Tangent;
  };

  struct TextureData
  {
    const Vec2 *TextureCoords;
    Vec4 Tint;
    int Texture = -1;
    int Specular = -1;
    int Emission = -1;
    int Normal = -1;
    int Displacement = -1;
    float Shininess = 32.0f;
  };

  struct DeferredRendererData
  {
    Ref<Framebuffer> GBuffer;
    Ref<Texture2D> GPosition, GNormal, GAlbedoSpecular;
  };

  enum class RenderMode
  {
    Forward,
    Deferred
  };

  struct TextureBindingInfo
  {
    std::vector<Ref<Texture>> Slots;
    int CurrentSlotIndex, MaxSlots, ReservedSlots, BindingOffset;
    std::vector<int> Samplers;

    // TODO: We can have empty reserved slots if we've not yet added the textures. Maybe rethink this approach.
    void Bind() const noexcept
    {
      for (int i = ReservedSlots; i < CurrentSlotIndex; i++)
        if (Slots[i])
          Slots[i]->Bind(i + BindingOffset);
    }

    void BindReserved() const noexcept
    {
      for (int i = 0; i < ReservedSlots; i++)
        if (Slots[i])
          Slots[i]->Bind(i + BindingOffset);
    }

    void Unbind() const noexcept
    {
      for (int i = ReservedSlots; i < CurrentSlotIndex; i++)
        if (Slots[i])
          Slots[i]->Unbind();
    }

    void UnbindReserved() const noexcept
    {
      for (int i = 0; i < ReservedSlots; i++)
        if (Slots[i])
          Slots[i]->Unbind();
    }

    NO_DISCARD bool HasSlotsRemaining() const noexcept
    {
      return CurrentSlotIndex < MaxSlots;
    }

    NO_DISCARD int GetReservedSlotIndex(int i) const noexcept
    {
      KRYS_ASSERT(i < ReservedSlots, "Trying to access a reserved slot out of bounds", 0);
      return BindingOffset + i;
    }
  };

  struct ActiveTextureUnits
  {
    TextureBindingInfo Texture2D;
    TextureBindingInfo TextureCubemap;

    void Bind() const noexcept
    {
      Texture2D.Bind();
      TextureCubemap.Bind();
    }

    void BindReserved() const noexcept
    {
      Texture2D.BindReserved();
      TextureCubemap.BindReserved();
    }

    void Unbind() const noexcept
    {
      Texture2D.Unbind();
      TextureCubemap.Unbind();
    }

    void UnbindReserved() const noexcept
    {
      Texture2D.UnbindReserved();
      TextureCubemap.UnbindReserved();
    }

    void Reset() noexcept
    {
      Texture2D.CurrentSlotIndex = Texture2D.ReservedSlots;
      TextureCubemap.CurrentSlotIndex = TextureCubemap.ReservedSlots;
    }

    void SetSamplerUniforms(std::vector<Ref<Shader>> shaders) noexcept
    {
      std::for_each(shaders.begin(), shaders.end(),
                    [&](auto s)
                    { SetSamplerUniforms(s); });
    }

    void SetSamplerUniforms(Ref<Shader> shader) noexcept
    {
      shader->TrySetUniform("u_Textures", Texture2D.Samplers.data(), Texture2D.MaxSlots);
      shader->TrySetUniform("u_Cubemaps", TextureCubemap.Samplers.data(), TextureCubemap.MaxSlots);
    }

    NO_DISCARD int MaxUnits() const { return Texture2D.MaxSlots + TextureCubemap.MaxSlots; }
  };

  class GraphicsContext
  {
  public:
    virtual ~GraphicsContext() = default;
    virtual void Init() noexcept = 0;

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

    virtual Ref<VertexBuffer> CreateVertexBuffer(uint32 size) noexcept = 0;
    virtual Ref<VertexBuffer> CreateVertexBuffer(float *vertices, uint32 size) noexcept = 0;

    virtual Ref<InstanceArrayBuffer> CreateInstanceArrayBuffer(uint32 size) noexcept = 0;
    virtual Ref<InstanceArrayBuffer> CreateInstanceArrayBuffer(void *data, uint32 size) noexcept = 0;

    virtual Ref<UniformBuffer> CreateUniformBuffer(uint32 size, uint32 binding) noexcept = 0;
    virtual Ref<UniformBuffer> CreateUniformBuffer(uint32 binding, UniformBufferLayout layout) noexcept = 0;

    virtual Ref<VertexArray> CreateVertexArray() noexcept = 0;

    virtual Ref<Shader> CreateShader() = 0;
    virtual Ref<Shader> CreateShader(const stringview &vertexFilepath, const stringview &fragmentFilepath) = 0;
    virtual Ref<Shader> CreateShader(const stringview &vertexFilepath, const stringview &fragmentFilepath, const stringview &geoFilepath) = 0;

    virtual Ref<Texture2D> CreateTexture2D(const string &filepath) noexcept = 0;
    virtual Ref<SubTexture2D> CreateSubTexture2D(Ref<Texture2D> texture, Vec2 &coords, Vec2 &cellSize, Vec2 &spriteSize) noexcept = 0;
    virtual Ref<TextureCubemap> CreateTextureCubemap(std::array<string, 6> paths) noexcept = 0;
    virtual Ref<TextureCubemap> CreateTextureCubemap(uint width, uint height, TextureInternalFormat internalFormat) noexcept = 0;

    virtual Ref<Framebuffer> CreateFramebuffer(uint32 width, uint32 height, uint32 samples = 1) noexcept = 0;
    Ref<PingPongFramebuffer> CreatePingPongFramebuffer(Ref<Framebuffer> a, Ref<Framebuffer> b) noexcept { return CreateRef<PingPongFramebuffer>(a, b); }

#pragma endregion Graphics Objects

#pragma region Primitive Drawing
    virtual void DrawVertices(size_t count, DrawMode mode = DrawMode::Triangles) noexcept = 0;
    virtual void DrawVerticesInstanced(size_t instanceCount, size_t vertexCount, DrawMode mode = DrawMode::Triangles) noexcept = 0;

    virtual void DrawIndices(size_t count, DrawMode mode = DrawMode::Triangles) noexcept = 0;
    virtual void DrawIndicesInstanced(size_t instanceCount, size_t indexCount, DrawMode mode = DrawMode::Triangles) noexcept = 0;
#pragma endregion Primitive Drawing
  };
}