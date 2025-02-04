#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Endian.hpp"
#include "Base/Types.hpp"
#include "Debug/Macros.hpp"

#include <bitset>

namespace Krys::IO
{
  class BitWriter
  {
    static constexpr size_t BitsetSize = 8 * sizeof(byte);

  public:
    BitWriter(List<byte> *buffer) noexcept
        : _bitset(0), _bitIndex(static_cast<int>(BitsetSize) - 1), _buffer(buffer)
    {
      KRYS_ASSERT(buffer != nullptr, "Buffer cannot be null.");
    }

    ~BitWriter() noexcept
    {
      Flush();
    }

    void Write(bool bit) noexcept
    {
      _bitset.set(_bitIndex, bit);
      if (--_bitIndex < 0)
        Flush();
    }

    void Write(IsIntegralT auto value, uint length) noexcept
    {
      KRYS_ASSERT(length <= BitsetSize, "Length must be less than or equal to {0}.", BitsetSize);
      KRYS_ASSERT(length > 0, "Length must be greater than 0.");
      KRYS_ASSERT(length <= sizeof(value) * 8, "Length must be less than or equal to {0}.",
                  sizeof(value) * 8);

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
      if (_bitIndex == static_cast<int>(BitsetSize) - 1)
        return;

      KRYS_ASSERT(_buffer != nullptr, "Buffer cannot be null.");
      _buffer->push_back(static_cast<byte>(_bitset.to_ullong()));

      _bitset.reset();
      _bitIndex = static_cast<int>(BitsetSize) - 1;
    }

    void SetBuffer(List<byte> *buffer) noexcept
    {
      KRYS_ASSERT(buffer != nullptr, "Buffer cannot be null.");
      _buffer = buffer;
    }

  private:
    std::bitset<BitsetSize> _bitset;
    int _bitIndex;
    List<byte> *_buffer;
  };
}