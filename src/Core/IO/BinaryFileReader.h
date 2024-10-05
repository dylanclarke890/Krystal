#pragma once

#include "Core.h"
#include "IO/IO.h"
#include "Misc/Endian.h"

namespace Krys::IO
{
  class BinaryFileReader
  {
  private:
    stringview Path;
    std::ifstream Stream;
    Endian::Type Endianness;

  public:
    BinaryFileReader(const stringview &path, Endian::Type endianness = Endian::Type::Little) noexcept
        : Path(path), Endianness(endianness)
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

    KRYS_DISABLE_WARNING_PUSH()
    KRYS_DISABLE_WARNING(4702, "-Wunreachable-code")
    
    /// @brief Reads a value of type T from the byte stream, optionally converting the endianness.
    /// @tparam T The type of value to read from the byte stream. Must be an integral or floating-point type.
    /// @tparam ConvertToSystemEndian If true, converts the value from the current byte stream's endianness
    ///         to the system's native endianness. Defaults to true.
    /// @return Returns the value read from the byte stream, converted to system endianness if specified.
    template <typename T, bool ConvertToSystemEndian = true>
    REQUIRES(std::is_integral_v<T> || std::is_floating_point_v<T>)
    T Read() noexcept
    {
      auto bytes = ReadBytes(sizeof(T));
      KRYS_ASSERT(bytes.size() == sizeof(T), "BinaryFileReader did not read the expected amount of bytes.", 0);

      const T value = std::bit_cast<T>(*reinterpret_cast<const T *>(&bytes[0]));

      if constexpr (!ConvertToSystemEndian)
        return value;

      return Endian::ToSystemEndian<T>(value, Endianness);
    }

    KRYS_DISABLE_WARNING_POP()

    string ReadJson(size_t length)
    {
      auto bytes = ReadBytes(length);
      KRYS_ASSERT(bytes.size() == length, "Read less bytes than expected", 0);

      return string(reinterpret_cast<const char *>(bytes.data()), length);
    }
  };
}
