#pragma once

#include "Core.h"
#include "Types.h"
#include "DataProcessing/Endian.h"

namespace Krys::Bytes
{
  template <typename T, Endian::Type SourceEndianness = Endian::Type::System, Endian::Type DestinationEndianness = Endian::Type::System>
  REQUIRES(std::is_integral_v<T> || std::is_floating_point_v<T>)
  constexpr T AsNumeric(const byte *bytes) noexcept
  {
    T value;
    std::memcpy(&value, bytes, sizeof(T));
    return Endian::Convert<T, SourceEndianness, DestinationEndianness>(value);
  }

  template <typename T, Endian::Type SourceEndianness = Endian::Type::System, Endian::Type DestinationEndianness = Endian::Type::System>
  REQUIRES(std::is_integral_v<T> || std::is_floating_point_v<T>)
  constexpr T AsNumeric(const List<byte> &bytes) noexcept
  {
    return AsNumeric<T, SourceEndianness, DestinationEndianness>(bytes.data());
  }

  template <typename T, Endian::Type SourceEndianness = Endian::Type::System, Endian::Type DestinationEndianness = Endian::Type::System>
  REQUIRES(std::is_integral_v<T> || std::is_floating_point_v<T>)
  constexpr List<T> AsNumericArray(const List<byte> &bytes) noexcept
  {
    KRYS_ASSERT(bytes.size() % sizeof(T) == 0, "Unable to convert all bytes to the specified type. Unexpected number of bytes. ", 0);
    size_t elementCount = bytes.size() / sizeof(T);

    List<T> elements;
    elements.resize(elementCount);

    for (size_t i = 0; i < elementCount; i++)
      elements[i] = AsNumeric<T, SourceEndianness, DestinationEndianness>(&bytes[i * sizeof(T)]);

    return elements;
  }

  constexpr string AsString(const List<byte> &bytes, size_t length) noexcept
  {
    return string(reinterpret_cast<const char *>(bytes.data()), length);
  }
}
