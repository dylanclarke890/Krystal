#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"

namespace Krys::MTL
{
  /// @brief Converts `degrees` to radians.
  /// @tparam TFloat A floating point type.
  /// @param degrees The input value.
  /// @returns The converted value.
  template <IsArithmeticT TFloat>
  NO_DISCARD constexpr TFloat Radians(TFloat degrees) noexcept
  {
    return degrees * static_cast<TFloat>(0.01745329251994329576923690768489);
  }

  constexpr NO_DISCARD long double operator""_rad(long double value)
  {
    return MTL::Radians(value);
  }

  constexpr NO_DISCARD long double operator""_radians(long double value)
  {
    return MTL::Radians(value);
  }
}