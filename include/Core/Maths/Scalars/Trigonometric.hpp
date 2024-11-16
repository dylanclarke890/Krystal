#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"

#include <cmath>

namespace Krys::MTL
{
  /// @brief Converts `degrees` to radians.
  /// @tparam TNumber An arithmetic type (floating point types are advised).
  /// @param degrees The input value.
  /// @returns The converted value.
  template <IsArithmeticT TNumber>
  constexpr NO_DISCARD TNumber Radians(TNumber degrees) noexcept
  {
    return degrees * static_cast<TNumber>(0.01745329251994329576923690768489);
  }

  /// @brief Converts `radians` to degrees.
  /// @tparam TNumber An arithmetic type (floating point types are advised).
  /// @param radians The input value.
  /// @returns The converted value.
  template <IsArithmeticT TNumber>
  constexpr NO_DISCARD TNumber Degrees(TNumber radians) noexcept
  {
    return radians * static_cast<TNumber>(57.295779513082320876798154814105);
  }

  /// @brief Computes sine.
  /// @tparam TNumber An arithmetic type (floating point types are advised).
  /// @param radians The input value.
  /// @returns The computed value.
  template <IsArithmeticT TNumber>
  constexpr NO_DISCARD TNumber Sin(TNumber radians) noexcept
  {
    return std::sin(radians);
  }

  /// @brief Computes cosine.
  /// @tparam TNumber An arithmetic type (floating point types are advised).
  /// @param radians The input value.
  /// @returns The computed value.
  template <IsArithmeticT TNumber>
  constexpr NO_DISCARD TNumber Cos(TNumber radians) noexcept
  {
    return std::cos(radians);
  }

  /// @brief Computes tangent.
  /// @tparam TNumber An arithmetic type (floating point types are advised).
  /// @param radians The input value.
  /// @returns The computed value.
  template <IsArithmeticT TNumber>
  constexpr NO_DISCARD TNumber Tan(TNumber radians) noexcept
  {
    return std::tan(radians);
  }

  /// @brief Computes arc sine.
  /// @tparam TNumber An arithmetic type (floating point types are advised).
  /// @param radians The input value.
  /// @returns The computed value.
  template <IsArithmeticT TNumber>
  constexpr NO_DISCARD TNumber Asin(TNumber radians) noexcept
  {
    return std::asin(radians);
  }

  /// @brief Computes arc cosine.
  /// @tparam TNumber An arithmetic type (floating point types are advised).
  /// @param radians The input value.
  /// @returns The computed value.
  template <IsArithmeticT TNumber>
  constexpr NO_DISCARD TNumber Acos(TNumber radians) noexcept
  {
    return std::acos(radians);
  }

  /// @brief Computes arc tangent.
  /// @tparam TNumber An arithmetic type (floating point types are advised).
  /// @param radians The input value.
  /// @returns The computed value.
  template <IsArithmeticT TNumber>
  constexpr NO_DISCARD TNumber Atan(TNumber radians) noexcept
  {
    return std::atan(radians);
  }

  /// @brief Computes arc tangent, using signs to determine quadrants.
  /// @tparam TNumber An arithmetic type (floating point types are advised).
  /// @param radians The input value.
  /// @returns The computed value.
  template <IsArithmeticT TNumber>
  constexpr NO_DISCARD TNumber Atan2(TNumber radians) noexcept
  {
    return std::atan2(radians);
  }
}