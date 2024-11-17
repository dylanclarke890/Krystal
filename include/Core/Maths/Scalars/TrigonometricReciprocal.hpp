#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"
#include "Core/Maths/Scalars/Trigonometric.hpp"

#include <cmath>

namespace Krys::MTL
{
  /// @brief Computes cosecant.
  /// @tparam TNumber An arithmetic type (floating point types are advised).
  /// @param radians The input value.
  /// @returns The computed value.
  template <IsArithmeticT TNumber>
  constexpr NO_DISCARD TNumber Csc(TNumber radians) noexcept
  {
    return TNumber(1) / MTL::Sin(radians);
  }

  /// @brief Computes secant.
  /// @tparam TNumber An arithmetic type (floating point types are advised).
  /// @param radians The input value.
  /// @returns The computed value.
  template <IsArithmeticT TNumber>
  constexpr NO_DISCARD TNumber Sec(TNumber radians) noexcept
  {
    return TNumber(1) / MTL::Cos(radians);
  }

  /// @brief Computes cotangent.
  /// @tparam TNumber An arithmetic type (floating point types are advised).
  /// @param radians The input value.
  /// @returns The computed value.
  template <IsArithmeticT TNumber>
  constexpr NO_DISCARD TNumber Cot(TNumber radians) noexcept
  {
    return TNumber(1) / MTL::Tan(radians);
  }

  /// @brief Computes inverse cosecant.
  /// @tparam TNumber An arithmetic type (floating point types are advised).
  /// @param x The input value.
  /// @returns The computed value.
  template <IsArithmeticT TNumber>
  constexpr NO_DISCARD TNumber Acsc(TNumber x) noexcept
  {
    return MTL::Asin(TNumber(1) / x);
  }

  /// @brief Computes inverse secant.
  /// @tparam TNumber An arithmetic type (floating point types are advised).
  /// @param x The input value.
  /// @returns The computed value.
  template <IsArithmeticT TNumber>
  constexpr NO_DISCARD TNumber Asec(TNumber x) noexcept
  {
    return MTL::Acos(TNumber(1) / x);
  }

  /// @brief Computes inverse cotangent.
  /// @tparam TNumber An arithmetic type (floating point types are advised).
  /// @param x The input value.
  /// @returns The computed value.
  template <IsArithmeticT TNumber>
  constexpr NO_DISCARD TNumber Acot(TNumber x) noexcept
  {
    return MTL::Atan(TNumber(1) / x);
  }

  /// @brief Computes secant, using signs to determine quadrants.
  /// @tparam TNumber An arithmetic type (floating point types are advised).
  /// @param y The opposite value.
  /// @param x The adjacent value.
  /// @returns The computed value.
  template <IsArithmeticT TNumber>
  constexpr NO_DISCARD TNumber SecAtan2(TNumber y, TNumber x) noexcept
  {
    return TNumber(1) / MTL::Atan2(y, x);
  }
}
