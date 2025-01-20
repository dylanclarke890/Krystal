#pragma once

#include "Base/Types.hpp"

namespace Krys::Gfx
{
  /// @brief A writer for a buffer.
  template <typename T>
  class BufferWriter
  {
  public:
    /// @brief Construct a buffer writer with the specified buffer and offset.
    BufferWriter(T &buffer, size_t offset = 0u) noexcept : _buffer(buffer), _offset(offset)
    {
    }

    /// @brief Write data to the buffer at the current offset.
    /// @tparam S Type of data to write.
    /// @param data The data to write.
    template <typename S>
    void Write(const S &data) noexcept
    {
      _buffer.Write(&data, sizeof(S), _offset);
      _offset += sizeof(S);
    }

    /// @brief Write a list of data to the buffer at the current offset.
    /// @tparam S Type of data to write.
    /// @param data The data to write.
    template <typename S>
    void Write(const List<S> &data) noexcept
    {
      _buffer.Write(data.data(), data.size() * sizeof(S), _offset);
      _offset += data.size() * sizeof(S);
    }

    /// @brief Advance the offset into the buffer by the specified amount.
    void Advance(size_t offset) noexcept
    {
      _offset += offset;
    }

  private:
    T &_buffer;
    size_t _offset;
  };
}