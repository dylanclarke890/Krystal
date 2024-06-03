#pragma once

#include "Core.h"
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

  class UniformBuffer
  {
  public:
    virtual ~UniformBuffer() = default;

    virtual void Bind() = 0;

    virtual void SetData(const void *data, uint32 size, uint32 offset) = 0;
    virtual void SetData(const std::string &name, const void *data) = 0;

    virtual const UniformBufferLayout &GetLayout() const = 0;
    virtual void SetLayout(const UniformBufferLayout &layout) = 0;
  };
}