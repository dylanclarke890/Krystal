#pragma once

#include "Core.h"
#include "Buffer.h"

namespace Krys
{
  class VertexArray
  {
  public:
    virtual ~VertexArray() = default;

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual void AddVertexBuffer(Ref<VertexBuffer> buffer) = 0;
    virtual void AddInstanceArrayBuffer(Ref<InstanceArrayBuffer> buffer) = 0;
    virtual void SetIndexBuffer(Ref<IndexBuffer> buffer) = 0;

    virtual const List<Ref<VertexBuffer>> &GetVertexBuffers() const = 0;
    virtual const List<Ref<InstanceArrayBuffer>> &GetInstanceArrayBuffers() const = 0;
    virtual const Ref<IndexBuffer> GetIndexBuffer() = 0;
  };
}