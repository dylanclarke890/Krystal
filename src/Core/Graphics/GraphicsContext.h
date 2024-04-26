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

  class GraphicsContext
  {
  public:
    virtual ~GraphicsContext() = default;
    virtual void Init() = 0;
    virtual void Clear() = 0;
    virtual void SetClearColor(float x, float y, float z, float a) = 0;
    virtual void SetViewport(int width, int height) = 0;
    virtual void SetFaceCulling(CullMode mode) = 0;
    virtual void SetWindingOrder(WindingOrder mode) = 0;

    virtual IndexBuffer *CreateIndexBuffer(uint32 *indices, uint32 count) = 0;

    virtual VertexBuffer *CreateVertexBuffer(uint32 size) = 0;
    virtual VertexBuffer *CreateVertexBuffer(float *vertices, uint32 size) = 0;

    virtual VertexArray *CreateVertexArray() = 0;

    virtual Shader *CreateShader() = 0;
  };
}