#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"

namespace Krys::MTL
{
  /// @brief Converts `radians` to degrees.
  /// @tparam TFloat A floating point type.
  /// @param radians The input value.
  /// @returns The converted value.
  template <IsFloatingPointT TFloat>
  NO_DISCARD constexpr TFloat Degrees(TFloat radians) noexcept
  {
    return TFloat(static_cast<double>(radians) * 57.295779513082320876798154814105);
  }

  /// @brief Converts `degrees` to radians.
  /// @tparam TFloat A floating point type.
  /// @param degrees The input value.
  /// @returns The converted value.
  template <IsArithmeticT TFloat>
  NO_DISCARD constexpr TFloat Radians(TFloat degrees) noexcept
  {
    return degrees * static_cast<TFloat>(0.01745329251994329576923690768489);
  }

  NO_DISCARD constexpr long double operator""_deg(long double value)
  {
    return MTL::Degrees(value);
  }

  NO_DISCARD constexpr long double operator""_degrees(long double value)
  {
    return MTL::Degrees(value);
  }

  NO_DISCARD constexpr long double operator""_rad(long double value)
  {
    return MTL::Radians(value);
  }

  NO_DISCARD constexpr long double operator""_radians(long double value)
  {
    return MTL::Radians(value);
  }
}
