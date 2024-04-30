#pragma once

#include "Krystal.h"
#include "Buffer.h"
#include "VertexArray.h"
#include "Shader.h"

namespace Krys
{
  enum class CullMode
  {
    None = 0,
    Front,
    Back,
    FrontAndBack
  };

  enum class WindingOrder
  {
    Clockwise,
    CounterClockwise
  };

  enum class DepthTestFunc
  {
    Never,
    Always,
    Less,
    EqualOrLess,
    Greater,
    EqualOrGreater
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
    virtual void SetClearColor(float x, float y, float z, float a) = 0;
    virtual void SetViewport(int width, int height) = 0;

    virtual void SetFaceCulling(CullMode mode) = 0;
    virtual void SetWindingOrder(WindingOrder mode) = 0;

    virtual void SetClearDepth(float value) = 0;
    virtual void SetDepthTestingEnabled(bool enable) = 0;
    virtual void SetDepthRange(float dNear, float dFar) = 0;
    virtual void SetDepthTestFunc(DepthTestFunc func) = 0;
#pragma endregion State Settings

#pragma region Graphics Objects
    virtual Ref<IndexBuffer> CreateIndexBuffer(const uint32 *indices, uint32 count) = 0;
    virtual Ref<IndexBuffer> CreateIndexBuffer(const ushort *indices, uint32 count) = 0;
    virtual Ref<VertexBuffer> CreateVertexBuffer(uint32 size) = 0;
    virtual Ref<VertexBuffer> CreateVertexBuffer(float *vertices, uint32 size) = 0;
    virtual Ref<VertexArray> CreateVertexArray() = 0;
    virtual Ref<Shader> CreateShader() = 0;
#pragma endregion Graphics Objects
  };
}