#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Hyperbolic/Cosh.hpp"

namespace Krys::MTL
{
  /// @brief Computes the hyperbolic secant of `x`.
  /// @tparam TNumber An arithmetic type.
  /// @param x The input value.
  /// @returns The hyperbolic secant of `x`.
  template <IsArithmeticT TNumber>
  NO_DISCARD constexpr TNumber Sech(TNumber radians) noexcept
  {
    return TNumber(1) / MTL::Cosh(radians);
  }
}
