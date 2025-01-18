#pragma once

#include "Base/Attributes.hpp"
#include "Graphics/Handles.hpp"

namespace Krys::Gfx
{
  enum class BufferUsageHint
  {
    Static,
    Dynamic,
    Stream
  };

  template <typename THandle>
  class Buffer
  {
    using handle_t = THandle;

  public:
    Buffer(uint32 capacity, BufferUsageHint usageHint = BufferUsageHint::Static) noexcept
        : _capacity(capacity), _usageHint(usageHint)
    {
    }

    virtual ~Buffer() = default;

    NO_DISCARD const handle_t &GetHandle() const noexcept
    {
      return _handle;
    }

    NO_DISCARD uint32 GetCapacity() const noexcept
    {
      return _capacity;
    }

    NO_DISCARD uint32 GetSize() const noexcept
    {
      return _size;
    }

    NO_DISCARD BufferUsageHint GetUsageHint() const noexcept
    {
      return _usageHint;
    }

    virtual void SetData(const void *data, uint32 size) noexcept = 0;

    virtual void Bind() noexcept = 0;
    virtual void Unbind() noexcept = 0;

  protected:
    handle_t _handle;
    uint32 _capacity {0}, _size {0};
    BufferUsageHint _usageHint;
  };

  using VertexBuffer = Buffer<VertexBufferHandle>;
  using IndexBuffer = Buffer<IndexBufferHandle>;
  using UniformBuffer = Buffer<UniformHandle>;
}