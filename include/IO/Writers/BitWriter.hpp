#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Endian.hpp"
#include "Base/Types.hpp"
#include "Core/Debug/Macros.hpp"

#include <bitset>

namespace Krys::IO
{
  // TODO: customize for different padding requirements for partial bitset writes
  // Do we pad them to the left or right?
  // Do we pad them with 1s or 0s?
  // Right now, we're just going to cast the bitset as-is.
  class BitWriter
  {
    static constexpr size_t BitsetSize = 8 * sizeof(byte);

  public:
    BitWriter(List<byte> *buffer) noexcept : _bitset(0), _bitIndex(0), _buffer(buffer)
    {
      KRYS_ASSERT(buffer != nullptr, "Buffer cannot be null.", 0);
    }

    ~BitWriter() noexcept
    {
      Flush();
    }

    void Write(bool bit) noexcept
    {
      _bitset.set(_bitIndex, bit);
      _bitIndex++;

      if (_bitIndex == BitsetSize)
        Flush();
    }

    void Write(IsIntegralT auto value, uint length) noexcept
    {
      KRYS_ASSERT(length <= BitsetSize, "Length must be less than or equal to %zu.", BitsetSize);
      KRYS_ASSERT(length > 0, "Length must be greater than 0.", 0);

      for (int i = length - 1; i >= 0; i--)
      {
        bool bit = ((value >> i) & 1) != 0;
        Write(bit);
      }
    }

    void Write(byte value) noexcept
    {
      Write(static_cast<uint8>(value), 8);
    }

    void Flush() noexcept
    {
      if (_bitIndex == 0)
        return;

      KRYS_ASSERT(_buffer != nullptr, "Buffer cannot be null.", 0);
      _buffer->push_back(static_cast<byte>(_bitset.to_ullong()));

      _bitset.reset();
      _bitIndex = 0;
    }

    void SetBuffer(List<byte> *buffer) noexcept
    {
      KRYS_ASSERT(buffer != nullptr, "Buffer cannot be null.", 0);
      _buffer = buffer;
    }

  private:
    std::bitset<BitsetSize> _bitset;
    size_t _bitIndex;
    List<byte> *_buffer;
  };
}