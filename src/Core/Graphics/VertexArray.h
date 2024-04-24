#pragma once

#include <vector>

#include "Krystal.h"
#include "Buffer.h"

namespace Krys
{
  class VertexArray
  {
  public:
    virtual ~VertexArray() = default;

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual void AddVertexBuffer(VertexBuffer *buffer) = 0;
    virtual void SetIndexBuffer(IndexBuffer *buffer) = 0;

    virtual const std::vector<VertexBuffer *> &GetVertexBuffers() const = 0;
    virtual const IndexBuffer *GetIndexBuffer() = 0;
  };
}