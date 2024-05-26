#pragma once

#include "Core.h"
#include "Buffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture2D.h"
#include "SubTexture2D.h"

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
    Clockwise,
    CounterClockwise
  };

  enum class DepthTestFunc : ushort
  {
    Never,
    Always,
    Less,
    EqualOrLess,
    EqualOrGreater,
    Greater
  };

  enum class StencilTestFunc : ushort
  {
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
    Keep,
    Zero,
    Replace,
    Increment,
    IncrementWithWrap,
    Decrement,
    DecrementWithWrap,
    Invert
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

  class GraphicsContext
  {
  public:
    virtual ~GraphicsContext() = default;
    virtual void Init() = 0;
    virtual void Clear(ClearFlags flags = ClearFlags::Color) = 0;

#pragma region State Settings
    virtual void SetClearColor(Vec4 &color) = 0;
    virtual void SetClearColor(Vec4 color) = 0;
    virtual void SetViewport(int width, int height) = 0;

    virtual void SetFaceCulling(CullMode mode) = 0;
    virtual void SetWindingOrder(WindingOrder mode) = 0;

    virtual void SetClearDepth(float value) = 0;
    virtual void SetDepthRange(float dNear, float dFar) = 0;
    virtual void SetDepthBufferWritingEnabled(bool enable) = 0;
    virtual void SetDepthTestingEnabled(bool enable) = 0;
    virtual void SetDepthTestFunc(DepthTestFunc func) = 0;
    virtual void SetDepthClampingEnabled(bool enable) = 0;

    virtual void SetStencilTestFunc(StencilTestFunc func, uint8 ref, uint8 mask) = 0;
    virtual void SetStencilOperation(StencilOperation fail, StencilOperation zFail, StencilOperation zPass) = 0;
    virtual void SetStencilTestingEnabled(bool enable) = 0;
    virtual void SetStencilBufferWritingEnabled(bool enable) = 0;
    // Similar to `SetStencilBufferWritingEnabled`, but takes a custom mask to be
    // ANDed with the stencil value to be written
    virtual void SetStencilBufferBitMask(uint8 mask) = 0;

    virtual void SetWireframeModeEnabled(bool enable) = 0;
#pragma endregion State Settings

#pragma region Graphics Objects
    virtual Ref<IndexBuffer> CreateIndexBuffer(uint32 count) = 0;
    virtual Ref<IndexBuffer> CreateIndexBuffer(const uint32 *indices, uint32 count) = 0;

    virtual Ref<VertexBuffer> CreateVertexBuffer(uint32 size) = 0;
    virtual Ref<VertexBuffer> CreateVertexBuffer(float *vertices, uint32 size) = 0;

    virtual Ref<VertexArray> CreateVertexArray() = 0;

    virtual Ref<Shader> CreateShader() = 0;

    virtual Ref<Texture2D> CreateTexture2D(const char *filepath) = 0;
    virtual Ref<SubTexture2D> CreateSubTexture2D(Ref<Texture2D> texture, Vec2 &coords, Vec2 &cellSize, Vec2 &spriteSize) = 0;

#pragma endregion Graphics Objects
  };
}