#pragma once

#include "Base/Attributes.hpp"
#include "Base/Macros.hpp"
#include "Base/Types.hpp"
#include "Core/IO/IO.hpp"
#include "Utils/Bytes.hpp"

#include <fstream>
#include <iostream>

namespace Krys::IO
{
  template <Endian::Type SourceEndianness = Endian::Type::System,
            Endian::Type DestinationEndianness = Endian::Type::System>
  class BinaryFileReader
  {
  private:
    stringview _path;
    std::ifstream _stream;

  public:
    BinaryFileReader(const stringview &path) noexcept : _path(path)
    {
      KRYS_ASSERT(PathExists(_path), "File '%s' does not exist", _path.data());
    }

    ~BinaryFileReader() noexcept
    {
      CloseStream();
    }

    NO_DISCARD bool IsEOF() const noexcept
    {
      return _stream.eof();
    }

    void OpenStream() noexcept
    {
      if (!_stream.is_open())
        _stream.open(_path.data(), std::ios::binary);

      KRYS_ASSERT(_stream.is_open(), "Unable to open %s.", _path.data());
    }

    void CloseStream() noexcept
    {
      if (_stream.is_open())
        _stream.close();
    }

    NO_DISCARD List<byte> ReadBytes(size_t numBytes) noexcept
    {
      if (!_stream.is_open() || _stream.eof())
        return {};

      List<byte> buffer(numBytes);
      _stream.read(reinterpret_cast<char *>(buffer.data()), numBytes);

      buffer.resize(_stream.gcount()); // Adjust the buffer size if we read fewer than numBytes
      return buffer;
    }

    template <typename T>
    REQUIRES(std::is_integral_v<T> || std::is_floating_point_v<T>)
    NO_DISCARD T Read() noexcept
    {
      auto bytes = ReadBytes(sizeof(T));
      return Bytes::AsNumeric<T, SourceEndianness, DestinationEndianness>(bytes);
    }

    template <typename T>
    REQUIRES(std::is_integral_v<T> || std::is_floating_point_v<T>)
    NO_DISCARD List<T> Read(size_t count) noexcept
    {
      auto bytes = ReadBytes(sizeof(T) * count);
      return Bytes::AsNumericArray<T, SourceEndianness, DestinationEndianness>(bytes);
    }

    NO_DISCARD string ReadJson(size_t length)
    {
      auto bytes = ReadBytes(length);
      return Bytes::AsString(bytes, length);
    }
  };
}
