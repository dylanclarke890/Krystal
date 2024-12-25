#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Endian.hpp"
#include "Base/Macros.hpp"
#include "Base/Types.hpp"
#include "Core/Debug/Macros.hpp"
#include "IO/IO.hpp"

#include <bit>
#include <fstream>
#include <iostream>

namespace Krys::IO
{
  template <Endian::Type TSource, Endian::Type TDestination>
  class BinaryFileWriter
  {
  public:
    explicit BinaryFileWriter(const string &path) noexcept : _path(path)
    {
    }

    ~BinaryFileWriter() noexcept
    {
      Close();
    }

    void Open() noexcept
    {
      KRYS_ASSERT(!_path.empty(), "No path has been provided.", 0);

      if (!_stream.is_open())
        _stream.open(_path.c_str(), std::ios::out | std::ios::binary);

      KRYS_ASSERT(_stream.is_open(), "Unable to open %s.", _path.c_str());
    }

    void Close() noexcept
    {
      if (_stream.is_open())
        _stream.close();
    }

    template <IsArithmeticT T>
    void Write(T value) noexcept
    {
      KRYS_ASSERT(_stream.is_open(), "Stream was not opened before writing", 0);
      value = Endian::Convert<T, TSource, TDestination>(value);
      auto bytes = std::bit_cast<Array<char, sizeof(T)>>(value);
      _stream.write(bytes.data(), bytes.size());
    }

    template <typename T>
    void Write(const List<T> &values) noexcept
    {
      KRYS_ASSERT(_stream.is_open(), "Stream was not opened before writing", 0);
      if constexpr (std::is_same_v<T, byte>)
      {
        WriteBytes(values);
      }
      else if constexpr (IsArithmeticT<T>)
      {
        for (const auto &value : values)
          Write(value);
      }
    }

    void WriteBytes(const List<byte> &bytes) noexcept
    {
      KRYS_ASSERT(_stream.is_open(), "Stream was not opened before writing", 0);
      _stream.write(reinterpret_cast<const char *>(bytes.data()), bytes.size());
    }

  private:
    string _path;
    std::ofstream _stream;
  };
}