#pragma once

#include "Base/Attributes.hpp"
#include "Base/Macros.hpp"
#include "Base/Types.hpp"
#include "Core/Debug/Macros.hpp"
#include "IO/IO.hpp"
#include "Utils/Bytes.hpp"

#include <fstream>
#include <iostream>

namespace Krys::IO
{
  template <Endian::Type SourceEndianness, Endian::Type DestinationEndianness>
  class BinaryFileReader
  {
  public:
    BinaryFileReader() noexcept
    {
    }

    BinaryFileReader(const string &path) noexcept : _path(path)
    {
      KRYS_ASSERT(IO::PathExists(_path), "File '%s' does not exist", _path.c_str());
    }

    ~BinaryFileReader() noexcept
    {
      CloseStream();
    }

    NO_DISCARD bool IsEOF() const noexcept
    {
      return _stream.eof();
    }

    void SetFilepath(const string &path) noexcept
    {
      CloseStream();
      _path = path;
      KRYS_ASSERT(IO::PathExists(_path), "File '%s' does not exist", _path.c_str());
    }

    void OpenStream() noexcept
    {
      KRYS_ASSERT(!_path.empty(), "No path has been provided.", 0);

      if (!_stream.is_open())
        _stream.open(_path.c_str(), std::ios::in | std::ios::binary);

      KRYS_ASSERT(_stream.is_open(), "Unable to open %s.", _path.c_str());
    }

    void CloseStream() noexcept
    {
      if (_stream.is_open())
        _stream.close();
    }

    NO_DISCARD List<byte> ReadBytes(size_t numBytes) noexcept
    {
      KRYS_ASSERT(_stream.is_open(), "Stream was not opened before reading");
      if (_stream.eof())
        return {};

      auto readPos = _stream.tellg();
      KRYS_LOG("BinaryFileReader: Offset before 'ReadBytes': %lld", static_cast<long long>(readPos));

      List<byte> buffer(numBytes);
      _stream.read(reinterpret_cast<char *>(buffer.data()), numBytes);

      readPos = _stream.tellg();
      KRYS_LOG("BinaryFileReader: Offset after 'ReadBytes': %lld", static_cast<long long>(readPos));

      buffer.resize(_stream.gcount()); // Adjust the buffer size if we read fewer than numBytes
      return buffer;
    }

    NO_DISCARD List<byte> ReadAllBytes() noexcept
    {
      List<byte> buffer;

      while (!_stream.eof())
      {
        auto bytes = ReadBytes(1'024);
        buffer.insert(buffer.end(), bytes.begin(), bytes.end());
      }

      return buffer;
    }

    template <IsArithmeticT T>
    NO_DISCARD T Read() noexcept
    {
      auto bytes = ReadBytes(sizeof(T));
      return Bytes::AsNumeric<T, SourceEndianness, DestinationEndianness>(bytes);
    }

    template <IsArithmeticT T>
    NO_DISCARD List<T> Read(size_t count) noexcept
    {
      auto bytes = ReadBytes(sizeof(T) * count);
      return Bytes::AsNumericArray<T, SourceEndianness, DestinationEndianness>(bytes);
    }

    void SkipBytes(size_t length) noexcept
    {
      _stream.seekg(length, std::ios::cur);
    }

    NO_DISCARD string ReadJson(size_t length)
    {
      auto bytes = ReadBytes(length);
      return Bytes::AsString(bytes, length);
    }

  private:
    string _path;
    std::ifstream _stream;
  };
}
