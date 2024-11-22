#pragma once

#include "Base/Attributes.hpp"
#include "Base/Endian.hpp"
#include "Base/Macros.hpp"
#include "Base/Types.hpp"

namespace Krys::Bytes
{
  typedef Endian::Type Endianness;
  constexpr Endian::Type SystemEndian = Endian::Type::System;

  template <typename T, Endianness TSource = SystemEndian, Endianness TDestination = SystemEndian>
  REQUIRES(std::is_integral_v<T> || std::is_floating_point_v<T>)
  NO_DISCARD constexpr T AsNumeric(const byte *bytes) noexcept
  {
    T value;
    std::memcpy(&value, bytes, sizeof(T));
    return Endian::Convert<T, TSource, TDestination>(value);
  }

  template <typename T, Endianness TSource = SystemEndian, Endianness TDestination = SystemEndian>
  REQUIRES(std::is_integral_v<T> || std::is_floating_point_v<T>)
  NO_DISCARD constexpr T AsNumeric(const List<byte> &bytes) noexcept
  {
    return AsNumeric<T, TSource, TDestination>(bytes.data());
  }

  template <typename T, Endianness TSource = SystemEndian, Endianness TDestination = SystemEndian>
  REQUIRES(std::is_integral_v<T> || std::is_floating_point_v<T>)
  NO_DISCARD constexpr List<T> AsNumericArray(const List<byte> &bytes) noexcept
  {
    KRYS_ASSERT(bytes.size() % sizeof(T) == 0,
                "Unable to convert all bytes to the specified type. Unexpected number of bytes. ", 0);
    size_t elementCount = bytes.size() / sizeof(T);

    List<T> elements;
    elements.resize(elementCount);

    for (size_t i = 0; i < elementCount; i++)
      elements[i] = AsNumeric<T, TSource, TDestination>(&bytes[i * sizeof(T)]);

    return elements;
  }

  NO_DISCARD string AsString(const List<byte> &bytes, const size_t length) noexcept
  {
    return string(reinterpret_cast<const char *>(bytes.data()), length);
  }
}
