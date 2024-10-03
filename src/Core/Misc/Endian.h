#pragma once

#include "Core.h"

#include <bit>
#include <type_traits>

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
    // Specialize for integral types using std::byteswap
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
  KRYS_DISABLE_WARNING(4702, "-Wunreachable-code")

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
  template <typename T>
  REQUIRES(std::is_integral_v<T> || std::is_floating_point_v<T>)
  constexpr NO_DISCARD T ToSystemEndian(T value, Type from) noexcept
  {
    if (from == Type::Little)
    {
      if (IsLittleEndian())
        return value;
      else
        return SwapEndian(value);
    }
    else if (from == Type::Big)
    {
      if (IsBigEndian())
        return value;
      else
        return SwapEndian(value);
    }

    return value;
  }

  KRYS_DISABLE_WARNING_POP()

  /// Convert a value from one endian representation to another.
  template <typename T>
  REQUIRES(std::is_integral_v<T> || std::is_floating_point_v<T>)
  constexpr NO_DISCARD T Convert(T value, Type from, Type to) noexcept
  {
    if (from == to)
      return value;

    if (to == Type::System)
      return ToSystemEndian(value, from);

    if (from == Type::System)
    {
      if (to == Type::Little)
        return ToLittleEndian(value);
      else if (to == Type::Big)
        return ToBigEndian(value);
      else
        return value;
    }

    // from == Big && to == Little or vice versa.
    return SwapEndian(value);
  }
}