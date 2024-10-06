#pragma once

#include "Core.h"
#include "IO/IO.h"
#include "DataProcessing/Endian.h"
#include "DataProcessing/Bytes.h"

namespace Krys::IO
{
  template <Endian::Type SourceEndianness = Endian::Type::System, Endian::Type DestinationEndianness = Endian::Type::System>
  class BinaryFileReader
  {
  private:
    stringview Path;
    std::ifstream Stream;

  public:
    BinaryFileReader(const stringview &path) noexcept
        : Path(path)
    {
      KRYS_ASSERT(PathExists(path), "File '%s' does not exist", path.data());
    }

    ~BinaryFileReader() noexcept
    {
      CloseStream();
    }

    bool IsEOF() const noexcept { return Stream.eof(); }

    void OpenStream() noexcept
    {
      if (!Stream.is_open())
        Stream.open(Path.data(), std::ios::binary);

      KRYS_ASSERT(Stream.is_open(), "Unable to open %s.", Path.data());
    }

    void CloseStream() noexcept
    {
      if (Stream.is_open())
        Stream.close();
    }

    List<byte> ReadBytes(size_t numBytes) noexcept
    {
      if (!Stream.is_open() || Stream.eof())
        return {};

      List<byte> buffer(numBytes);
      Stream.read(reinterpret_cast<char *>(buffer.data()), numBytes);

      buffer.resize(Stream.gcount()); // Adjust the buffer size if we read fewer than numBytes
      return buffer;
    }

    template <typename T>
    REQUIRES(std::is_integral_v<T> || std::is_floating_point_v<T>)
    T Read() noexcept
    {
      auto bytes = ReadBytes(sizeof(T));
      return Bytes::AsNumeric<T, SourceEndianness, DestinationEndianness>(bytes);
    }

    template <typename T>
    REQUIRES(std::is_integral_v<T> || std::is_floating_point_v<T>)
    List<T> Read(size_t count) noexcept
    {
      auto bytes = ReadBytes(sizeof(T) * count);
      return Bytes::AsNumericArray<T, SourceEndianness, DestinationEndianness>(bytes);
    }

    string ReadJson(size_t length)
    {
      auto bytes = ReadBytes(length);
      return Bytes::AsString(bytes, length);
    }
  };
}
