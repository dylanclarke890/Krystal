#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Endian.hpp"
#include "Base/Types.hpp"
#include "Core/Debug/Macros.hpp"
#include "Utils/Bytes.hpp"

#include <bitset>

namespace Krys::IO
{
  template <Endian::Type TSource, Endian::Type TDestination>
  class BitReader
  {
    static constexpr size_t BitsetSize = 8 * sizeof(byte);

  public:
    BitReader(const List<byte> *buffer) noexcept
        : _buffer(buffer), _bitIndex(0), _byteIndex(0), _currentByte(0)
    {
      KRYS_ASSERT(buffer != nullptr, "Buffer cannot be null.");
    }

    ~BitReader() noexcept = default;

    NO_DISCARD bool ReadBit() noexcept
    {
      if (_bitIndex == 0)
        _currentByte = static_cast<uint8>(_buffer->at(_byteIndex++));

      // Extract the current bit (MSB first)
      bool bit = (_currentByte >> (7 - _bitIndex)) & 1;
      _bitIndex = (_bitIndex + 1) % 8;

      return bit;
    }

    NO_DISCARD byte ReadBits(uint length) noexcept
    {
      KRYS_ASSERT(length <= BitsetSize, "Length must be less than or equal to %zu.", BitsetSize);
      KRYS_ASSERT(length > 0, "Length must be greater than 0.");

      byte value {};
      for (uint i = 0; i < length; i++)
      {
        bool bit = ReadBit();
        value |= static_cast<byte>(bit) << (length - i - 1);
      }

      return value;
    }

    NO_DISCARD List<byte> ReadBytes(size_t count) noexcept
    {
      List<byte> bytes(count);
      for (size_t i = 0; i < count; i++)
        bytes[i] = ReadBits(8);
      return bytes;
    }

    template <IsArithmeticT T>
    NO_DISCARD T Read() noexcept
    {
      auto bytes = ReadBytes(sizeof(T));
      return Bytes::AsNumeric<T, TSource, TDestination>(bytes);
    }

    void NextByte() noexcept
    {
      _bitIndex = 0; // will fetch the next byte on the next call to Read
    }

  private:
    const List<byte> *_buffer;
    uint8 _currentByte;
    size_t _bitIndex;
    size_t _byteIndex;
  };
}
