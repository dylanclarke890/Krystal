#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Endian.hpp"
#include "Base/Macros.hpp"
#include "Base/Pointers.hpp"
#include "Base/Types.hpp"
#include "Utils/Bytes.hpp"

namespace Krys::IO
{
  template <Endian::Type TSource, Endian::Type TDestination>
  class MemoryReader
  {
  public:
    explicit constexpr MemoryReader(const List<byte> &data) noexcept : _buffer(data), _readIndex(0)
    {
    }

    explicit constexpr MemoryReader(const string &data) noexcept : _readIndex(0)
    {
      _buffer.reserve(data.size());
      for (auto c : data)
        _buffer.push_back(static_cast<byte>(c));
    }

    ~MemoryReader() noexcept = default;
    constexpr MemoryReader(const MemoryReader &) = delete;
    constexpr MemoryReader &operator=(const MemoryReader &) = delete;

    constexpr MemoryReader(MemoryReader &&other) noexcept
        : _buffer(std::move(other._buffer)), _readIndex(other._readIndex)
    {
    }

    constexpr MemoryReader &operator=(MemoryReader &&other) noexcept
    {
      if (this != &other)
      {
        _buffer = std::move(other._buffer);
        _readIndex = other._readIndex;
      }
      return *this;
    }

    constexpr void Open() noexcept
    {
    }

    constexpr void Close() noexcept
    {
    }

    NO_DISCARD constexpr bool IsEOS() const noexcept
    {
      return _readIndex >= _buffer.size();
    }

    NO_DISCARD constexpr uintmax_t GetSize() const noexcept
    {
      return _buffer.size();
    }

    template <IsArithmeticT T>
    NO_DISCARD constexpr T Read() noexcept
    {
      auto bytes = ReadBytes(sizeof(T));
      return Bytes::AsNumeric<T, TSource, TDestination>(bytes);
    }

    template <IsArithmeticT T>
    NO_DISCARD constexpr List<T> Read(size_t count) noexcept
    {
      auto bytes = ReadBytes(sizeof(T) * count);
      return Bytes::AsNumericArray<T, TSource, TDestination>(bytes);
    }

    NO_DISCARD constexpr List<byte> ReadBytes(size_t count) noexcept
    {
      if (_readIndex + count > _buffer.size())
        count = _buffer.size() - _readIndex;

      if (count == 0)
        return {};

      List<byte> result(count);
      std::copy(_buffer.data() + _readIndex, _buffer.data() + _readIndex + count, result.begin());
      _readIndex += count;

      return result;
    }

    template <IsArithmeticT T>
    constexpr void Skip(size_t count) noexcept
    {
      _readIndex += sizeof(T) * count;
    }

    constexpr void Reset() noexcept
    {
      _readIndex = 0;
    }

  private:
    List<byte> _buffer;
    size_t _readIndex;
  };
}