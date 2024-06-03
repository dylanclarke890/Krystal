#pragma once

#include "Core.h"
#include "Buffer.h"
#include "Framebuffer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "Textures/SubTexture2D.h"
#include "Textures/Texture2D.h"
#include "Textures/TextureCubemap.h"

namespace Krys
{
  enum class CullMode : ushort
  {
    None = 0,
    Front,
    Back,
    FrontAndBack
  };

  enum class WindingOrder : ushort
  {
    None = 0,
    Clockwise,
    CounterClockwise
  };

  enum class DepthTestFunc : ushort
  {
    None = 0,
    Never,
    Always,
    Less,
    EqualOrLess,
    EqualOrGreater,
    Greater
  };

  enum class StencilTestFunc : ushort
  {
    None = 0,
    Never,
    Always,
    Less,
    EqualOrLess,
    Equal,
    NotEqual,
    EqualOrGreater,
    Greater
  };

  enum class StencilOperation : ushort
  {
    None = 0,
    Keep,
    Zero,
    Replace,
    Increment,
    IncrementWithWrap,
    Decrement,
    DecrementWithWrap,
    Invert
  };

  enum class BlendFactor : ushort
  {
    None = 0,
    Zero,
    One,
    SourceColor,
    OneMinusSourceColor,
    DestinationColor,
    OneMinusDestinationColor,
    SourceAlpha,
    OneMinusSourceAlpha,
    DestinationAlpha,
    OneMinusDestinationAlpha,
    ConstantColor,
    OneMinusConstantColor,
    ConstantAlpha,
    OneMinusConstantAlpha
  };

  enum class BlendEquation : ushort
  {
    None = 0,
    Add,
    Subtract,
    ReverseSubtract,
    Min,
    Max
  };

  enum class ClearFlags : ushort
  {
    None = 0,
    Color = 1,
    Depth = 2,
    Stencil = 4
  };

  inline ClearFlags operator|(ClearFlags a, ClearFlags b)
  {
    return static_cast<ClearFlags>(static_cast<uint>(a) | static_cast<uint>(b));
  }

  inline bool operator&(ClearFlags a, ClearFlags b)
  {
    return (static_cast<uint>(a) & static_cast<uint>(b));
  }

  enum class DrawMode : ushort
  {
    None = 0,
    Points,
    Triangles
  };

  class GraphicsContext
  {
  public:
    virtual ~GraphicsContext() = default;
    virtual void Init() noexcept = 0;
    virtual void Clear(ClearFlags flags = ClearFlags::Color) noexcept = 0;

#pragma region State Settings
    virtual void SetClearColor(Vec4 &color) noexcept = 0;
    virtual void SetClearColor(Vec4 color) noexcept = 0;
    virtual void SetViewport(int width, int height) noexcept = 0;

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
    // Similar to `SetStencilBufferWritingEnabled`, but takes a custom mask to be
    // ANDed with the stencil value to be written
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

    virtual Ref<UniformBuffer> CreateUniformBuffer(uint32 size, uint32 binding) noexcept = 0;
    virtual Ref<UniformBuffer> CreateUniformBuffer(uint32 binding, UniformBufferLayout layout) noexcept = 0;

    virtual Ref<VertexArray> CreateVertexArray() noexcept = 0;

    virtual Ref<Shader> CreateShader() = 0;
    virtual Ref<Shader> CreateShader(const char *vertexFilepath, const char *fragmentFilepath) = 0;
    virtual Ref<Shader> CreateShader(const char *vertexFilepath, const char *fragmentFilepath, const char *geoFilepath) = 0;

    virtual Ref<Texture2D> CreateTexture2D(const char *filepath) noexcept = 0;
    virtual Ref<SubTexture2D> CreateSubTexture2D(Ref<Texture2D> texture, Vec2 &coords, Vec2 &cellSize, Vec2 &spriteSize) noexcept = 0;
    virtual Ref<TextureCubemap> CreateTextureCubemap(std::vector<std::string> paths) noexcept = 0;

    virtual Ref<Framebuffer> CreateFramebuffer() noexcept = 0;
#pragma endregion Graphics Objects

#pragma region Primitive Drawing
    virtual void DrawVertices(size_t count, DrawMode mode = DrawMode::Triangles) noexcept = 0;
    virtual void DrawIndexed(size_t count, DrawMode mode = DrawMode::Triangles) noexcept = 0;
#pragma endregion Primitive Drawing
  };
}