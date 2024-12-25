#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Endian.hpp"
#include "Base/Macros.hpp"
#include "Base/Types.hpp"
#include "Core/Debug/Macros.hpp"
#include "IO/IO.hpp"
#include "Utils/Bytes.hpp"

#include <fstream>
#include <iostream>

namespace Krys::IO
{
  template <Endian::Type TSource, Endian::Type TDestination>
  class BinaryFileReader
  {
  public:
    explicit BinaryFileReader(const string &path) noexcept : _path(path)
    {
    }

    ~BinaryFileReader() noexcept
    {
      Close();
    }

    constexpr BinaryFileReader(const BinaryFileReader &) = delete;
    constexpr BinaryFileReader &operator=(const BinaryFileReader &) = delete;

    constexpr BinaryFileReader(BinaryFileReader &&other) noexcept
        : _path(std::move(other._path)), _stream(std::move(other._stream))
    {
    }

    constexpr BinaryFileReader &operator=(BinaryFileReader &&other) noexcept
    {
      if (this != &other)
      {
        _path = std::move(other._path);
        _stream = std::move(other._stream);
      }
      return *this;
    }

    void Open() noexcept
    {
      KRYS_ASSERT(IO::PathExists(_path), "File '%s' does not exist", _path.c_str());
      _stream.open(_path.c_str(), std::ios::in | std::ios::binary);
      KRYS_ASSERT(_stream.is_open(), "Unable to open %s.", _path.c_str());
    }

    void Close() noexcept
    {
      if (_stream.is_open())
        _stream.close();
    }

    NO_DISCARD bool IsEOS() const noexcept
    {
      return _stream.eof();
    }

    NO_DISCARD uintmax_t GetSize() noexcept
    {
      const auto pos = _stream.tellg();
      _stream.seekg(0, std::ios::end);
      auto size = _stream.tellg();
      _stream.seekg(pos);
      return size;
    }

    template <IsArithmeticT T>
    NO_DISCARD T Read() noexcept
    {
      auto bytes = ReadBytes(sizeof(T));
      return Bytes::AsNumeric<T, TSource, TDestination>(bytes);
    }

    template <IsArithmeticT T>
    NO_DISCARD List<T> Read(size_t count) noexcept
    {
      auto bytes = ReadBytes(sizeof(T) * count);
      return Bytes::AsNumericArray<T, TSource, TDestination>(bytes);
    }

    NO_DISCARD List<byte> ReadBytes(size_t count) noexcept
    {
      if (_stream.eof())
        return {};

      auto readPos = _stream.tellg();
      KRYS_LOG("FileDataSource: Offset before 'ReadBytes': %lld", static_cast<long long>(readPos));

      List<byte> buffer(count);
      _stream.read(reinterpret_cast<char *>(buffer.data()), count);

      readPos = _stream.tellg();
      KRYS_LOG("FileDataSource: Offset after 'ReadBytes': %lld", static_cast<long long>(readPos));

      buffer.resize(_stream.gcount()); // Adjust the buffer size if we read fewer than count
      return buffer;
    }

    template <IsArithmeticT T>
    void Skip(size_t count) noexcept
    {
      _stream.seekg(sizeof(T) * count, std::ios::cur);
    }

    void Reset() noexcept
    {
      _stream.clear();
      _stream.seekg(0);
    }

  private:
    string _path;
    std::ifstream _stream;
  };
}