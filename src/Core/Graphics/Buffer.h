#pragma once

#include "Krystal.h"
#include "BufferLayout.h"

namespace Krys
{
  class IndexBuffer
  {
  public:
    virtual ~IndexBuffer() = default;

    virtual void Bind() = 0;
    virtual void Unbind() = 0;
    virtual void SetData(const uint32 *indices, uint32 count) = 0;

    virtual uint Size() = 0;
  };

  class VertexBuffer
  {
  public:
    virtual ~VertexBuffer() = default;

    virtual void Bind() = 0;
    virtual void Unbind() = 0;

    virtual void SetData(const void *data, uint32 size) = 0;

    virtual const BufferLayout &GetLayout() const = 0;
    virtual void SetLayout(const BufferLayout &layout) = 0;
  };
}