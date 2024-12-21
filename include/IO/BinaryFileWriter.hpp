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
  class BinaryFileWriter
  {
  public:
    BinaryFileWriter() noexcept
    {
    }

    BinaryFileWriter(const string &path) noexcept : _path(path)
    {
      KRYS_ASSERT(IO::PathExists(_path), "File '%s' does not exist", _path.c_str());
    }

    ~BinaryFileWriter() noexcept
    {
      CloseStream();
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
        _stream.open(_path.c_str(), std::ios::out | std::ios::binary);

      KRYS_ASSERT(_stream.is_open(), "Unable to open %s.", _path.c_str());
    }

    void CloseStream() noexcept
    {
      if (_stream.is_open())
        _stream.close();
    }

    template <IsArithmeticT T>
    NO_DISCARD void Write(T value) noexcept
    {
      KRYS_ASSERT(_stream.is_open(), "Stream was not opened before writing", 0);
      value = Endian::Convert<T, SourceEndianness, DestinationEndianness>(value);
      _stream.write(reinterpret_cast<const char *>(&value), sizeof(T));
    }

    template <IsArithmeticT T>
    NO_DISCARD void Write(const List<T> &array) noexcept
    {
      for (const T &value : array)
        Write(value);
    }

  private:
    string _path;
    std::ofstream _stream;
  };
}