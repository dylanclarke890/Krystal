#pragma once

#include <bit>
#include <type_traits>

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
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

  NO_DISCARD constexpr bool IsBigEndian() noexcept
  {
    return std::endian::native == std::endian::big;
  }

  NO_DISCARD constexpr bool IsLittleEndian() noexcept
  {
    return std::endian::native == std::endian::little;
  }

  template <IsArithmeticT T>
  NO_DISCARD constexpr T SwapEndian(T value)
  {
    if constexpr (std::is_integral_v<T>)
      return std::byteswap(value);
    // For floating-point types, use std::bit_cast to swap bytes
    else if constexpr (std::is_floating_point_v<T>)
    {
      using as_uint_t = std::conditional_t<sizeof(T) == 4, uint32, uint64>;
      as_uint_t temp = std::bit_cast<as_uint_t>(value);
      temp = std::byteswap(temp);
      return std::bit_cast<T>(temp);
    }
  }

  /// @brief Converts a value to big endian. If the underlying system is big endian,
  /// the value is assumed to already be represented as big endian and is returned unchanged.
  template <IsArithmeticT T>
  NO_DISCARD constexpr T ToBigEndian(T value) noexcept
  {
    if constexpr (IsBigEndian())
      return value;
    else
      return SwapEndian(value);
  }

  /// @brief Converts a value to little endian. If the underlying system is little endian,
  /// the value is assumed to already be represented as little endian and is returned unchanged.
  template <IsArithmeticT T>
  NO_DISCARD constexpr T ToLittleEndian(T value) noexcept
  {
    if constexpr (IsLittleEndian())
      return value;
    else
      return SwapEndian(value);
  }

  /// @brief Converts a value to the system's native endian.
  /// @tparam T The type of the value to be converted (integral or floating-point).
  /// @param value The value to convert.
  /// @param from The endian type the value is currently in (either Little or Big).
  /// @return The value converted to the system's native endianness.
  template <IsArithmeticT T, Endian::Type SourceEndianness>
  NO_DISCARD constexpr T ToSystemEndian(T value) noexcept
  {
    if constexpr (SourceEndianness == Type::Little)
      return IsLittleEndian() ? value : SwapEndian(value);
    else if constexpr (SourceEndianness == Type::Big)
      return IsBigEndian() ? value : SwapEndian(value);
    else
      return value;
  }

  /// @brief Convert a value from one endian representation to another.
  template <IsArithmeticT T, Endian::Type SourceEndianness, Endian::Type DestinationEndianness>
  NO_DISCARD constexpr T Convert(T value) noexcept
  {
    if constexpr (SourceEndianness == DestinationEndianness)
      return value;
    else if constexpr (DestinationEndianness == Type::System)
      return ToSystemEndian<T, SourceEndianness>(value);
    else if constexpr (SourceEndianness == Type::System)
    {
      if constexpr (DestinationEndianness == Type::Little)
        return ToLittleEndian(value);
      else if constexpr (DestinationEndianness == Type::Big)
        return ToBigEndian(value);
      else
        return value;
    }
    else
      // from == Big && to == Little or vice versa.
      return SwapEndian(value);
  }
}