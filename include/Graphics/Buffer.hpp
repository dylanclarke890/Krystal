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

  /// @brief Represents a buffer object.
  /// @tparam THandle The handle type of the buffer.
  template <typename THandle>
  class Buffer
  {
    using handle_t = THandle;

  public:
    /// @brief Construct a buffer with the specified capacity and usage hint.
    /// @param capacity The initial capacity of the buffer.
    /// @param usageHint The usage hint of the buffer.
    explicit Buffer(handle_t handle, uint32 capacity,
                    BufferUsageHint usageHint = BufferUsageHint::Static) noexcept
        : _handle(handle), _capacity(capacity), _usageHint(usageHint)
    {
    }

    virtual ~Buffer() = default;

    /// @brief Get the handle of the buffer.
    NO_DISCARD const handle_t &GetHandle() const noexcept
    {
      return _handle;
    }

    /// @brief Get the capacity of the buffer.
    NO_DISCARD uint32 GetCapacity() const noexcept
    {
      return _capacity;
    }

    /// @brief Get the usage hint of the buffer, specified at creation.
    NO_DISCARD BufferUsageHint GetUsageHint() const noexcept
    {
      return _usageHint;
    }

    /// @brief Write data to the buffer at the specified offset.
    /// @param data The data to write.
    /// @param size The size of the data.
    /// @param offset The offset to write the data to.
    virtual void Write(const void *data, size_t size, size_t offset) noexcept = 0;

    /// @brief Bind the buffer.
    virtual void Bind() noexcept = 0;

    /// @brief Unbind the buffer.
    virtual void Unbind() noexcept = 0;

  protected:
    handle_t _handle;
    uint32 _capacity {0};
    BufferUsageHint _usageHint;
  };

  using VertexBuffer = Buffer<VertexBufferHandle>;
  using IndexBuffer = Buffer<IndexBufferHandle>;
  using UniformBuffer = Buffer<UniformBufferHandle>;
  using ShaderStorageBuffer = Buffer<ShaderStorageBufferHandle>;
}