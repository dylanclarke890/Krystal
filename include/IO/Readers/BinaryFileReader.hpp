#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Endian.hpp"
#include "Base/Macros.hpp"
#include "Base/Types.hpp"
#include "Debug/Macros.hpp"
#include "IO/IO.hpp"
#include "Utils/Bytes.hpp"

#include <fstream>
#include <iostream>

#ifdef KRYS_ENABLE_FILE_OFFSET_LOGGING
  #define KRYS_LOG_FILE_OFFSET(message, offset) KRYS_LOG(message, offset)
#else
  #define KRYS_LOG_FILE_OFFSET(message, offset)
#endif

namespace Krys::IO
{
  template <Endian::Type TSource, Endian::Type TDestination>
  class BinaryFileReader
  {
  public:
    explicit constexpr BinaryFileReader(const string &path) noexcept : _path(path)
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
      KRYS_ASSERT(IO::PathExists(_path), "IO: File '{0}' does not exist", _path);
      _stream.open(_path.c_str(), std::ios::in | std::ios::binary);
      KRYS_ASSERT(_stream.is_open(), "IO: Unable to open '{0}'.", _path);
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
      KRYS_LOG_FILE_OFFSET("BinaryFileReader: Offset before 'ReadBytes': %lld",
                           static_cast<long long>(readPos));

      List<byte> buffer(count);
      _stream.read(reinterpret_cast<char *>(buffer.data()), count);

      readPos = _stream.tellg();
      KRYS_LOG_FILE_OFFSET("BinaryFileReader: Offset after 'ReadBytes': %lld",
                           static_cast<long long>(readPos));

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