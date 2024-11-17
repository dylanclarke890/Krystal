#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"
#include "Core/Maths/Scalars/Hyperbolic.hpp"

#include <cmath>

namespace Krys::MTL
{
  /// @brief Computes cosecant.
  /// @tparam TNumber An arithmetic type (floating point types are advised).
  /// @param radians The input value.
  /// @returns The computed value.
  template <IsArithmeticT TNumber>
  constexpr NO_DISCARD TNumber Csch(TNumber radians) noexcept
  {
    return TNumber(1) / MTL::Sinh(radians);
  }

  /// @brief Computes secant.
  /// @tparam TNumber An arithmetic type (floating point types are advised).
  /// @param radians The input value.
  /// @returns The computed value.
  template <IsArithmeticT TNumber>
  constexpr NO_DISCARD TNumber Sech(TNumber radians) noexcept
  {
    return TNumber(1) / MTL::Cosh(radians);
  }

  /// @brief Computes cotangent.
  /// @tparam TNumber An arithmetic type (floating point types are advised).
  /// @param radians The input value.
  /// @returns The computed value.
  template <IsArithmeticT TNumber>
  constexpr NO_DISCARD TNumber Coth(TNumber radians) noexcept
  {
    return TNumber(1) / MTL::Tanh(radians);
  }

  /// @brief Computes inverse cosecant.
  /// @tparam TNumber An arithmetic type (floating point types are advised).
  /// @param x The input value.
  /// @returns The computed value.
  template <IsArithmeticT TNumber>
  constexpr NO_DISCARD TNumber Acsch(TNumber x) noexcept
  {
    return MTL::Asinh(TNumber(1) / x);
  }

  /// @brief Computes inverse secant.
  /// @tparam TNumber An arithmetic type (floating point types are advised).
  /// @param x The input value.
  /// @returns The computed value.
  template <IsArithmeticT TNumber>
  constexpr NO_DISCARD TNumber Asech(TNumber x) noexcept
  {
    return MTL::Acosh(TNumber(1) / x);
  }

  /// @brief Computes inverse cotangent.
  /// @tparam TNumber An arithmetic type (floating point types are advised).
  /// @param x The input value.
  /// @returns The computed value.
  template <IsArithmeticT TNumber>
  constexpr NO_DISCARD TNumber Acoth(TNumber x) noexcept
  {
    return MTL::Atanh(TNumber(1) / x);
  }
}
