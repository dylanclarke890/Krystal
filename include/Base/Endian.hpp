#pragma once

#include <bit>
#include <type_traits>

#include "Base/Attributes.hpp"
#include "Base/Defines.hpp"
#include "Base/Macros.hpp"
#include "Base/Types.hpp"

namespace Krys::Endian
{
  enum class Type
  {
    Little,
    Big,
    System
  };

  constexpr NO_DISCARD bool IsBigEndian() noexcept
  {
    return std::endian::native == std::endian::big;
  }

  constexpr NO_DISCARD bool IsLittleEndian() noexcept
  {
    return std::endian::native == std::endian::little;
  }

  template <typename T>
  REQUIRES(std::is_integral_v<T> || std::is_floating_point_v<T>)
  constexpr NO_DISCARD T SwapEndian(T value)
  {
    if constexpr (std::is_integral_v<T>)
    {
      return std::byteswap(value);
    }
    // For floating-point types, use std::bit_cast to swap bytes
    else if constexpr (std::is_floating_point_v<T>)
    {
      using UnsignedT = std::conditional_t<sizeof(T) == 4, uint32, uint64>;
      UnsignedT temp = std::bit_cast<UnsignedT>(value);
      temp = std::byteswap(temp);
      return std::bit_cast<T>(temp);
    }
  }

  KRYS_DISABLE_WARNING_PUSH()
  KRYS_DISABLE_WARNING(4'702, "-Wunreachable-code")

  /// @brief Converts a value to big endian. If the underlying system is big endian,
  /// the value is assumed to already be represented as big endian and is returned unchanged.
  template <typename T>
  REQUIRES(std::is_integral_v<T> || std::is_floating_point_v<T>)
  constexpr NO_DISCARD T ToBigEndian(T value) noexcept
  {
    if constexpr (IsBigEndian())
      return value;

    return SwapEndian(value);
  }

  /// @brief Converts a value to little endian. If the underlying system is little endian,
  /// the value is assumed to already be represented as little endian and is returned unchanged.
  template <typename T>
  REQUIRES(std::is_integral_v<T> || std::is_floating_point_v<T>)
  constexpr NO_DISCARD T ToLittleEndian(T value) noexcept
  {
    if constexpr (IsLittleEndian())
      return value;

    return SwapEndian(value);
  }

  /// @brief Converts a value to the system's native endian.
  /// @tparam T The type of the value to be converted (integral or floating-point).
  /// @param value The value to convert.
  /// @param from The endian type the value is currently in (either Little or Big).
  /// @return The value converted to the system's native endianness.
  template <typename T, Endian::Type SourceEndianness>
  REQUIRES(std::is_integral_v<T> || std::is_floating_point_v<T>)
  constexpr NO_DISCARD T ToSystemEndian(T value) noexcept
  {
    if constexpr (SourceEndianness == Type::Little)
    {
      return IsLittleEndian() ? value : SwapEndian(value);
    }
    else if constexpr (SourceEndianness == Type::Big)
    {
      return IsBigEndian() ? value : SwapEndian(value);
    }

    return value;
  }

  /// Convert a value from one endian representation to another.
  template <typename T, Endian::Type SourceEndianness, Endian::Type DestinationEndianness>
  REQUIRES(std::is_integral_v<T> || std::is_floating_point_v<T>)
  constexpr NO_DISCARD T Convert(T value) noexcept
  {
    if constexpr (SourceEndianness == DestinationEndianness)
      return value;

    if constexpr (DestinationEndianness == Type::System)
      return ToSystemEndian<T, SourceEndianness>(value);

    if constexpr (SourceEndianness == Type::System)
    {
      if constexpr (DestinationEndianness == Type::Little)
        return ToLittleEndian(value);
      else if constexpr (DestinationEndianness == Type::Big)
        return ToBigEndian(value);
      else
        return value;
    }

    // from == Big && to == Little or vice versa.
    return SwapEndian(value);
  }

  KRYS_DISABLE_WARNING_POP()
}