#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Hyperbolic/Acosh.hpp"

namespace Krys::MTL
{
  /// @brief Computes the inverse hyperbolic secant of `x`.
  /// @tparam TNumber An arithmetic type.
  /// @param x The input value.
  /// @returns The inverse hyperbolic secant of `x`.
  template <IsArithmeticT TNumber>
  NO_DISCARD constexpr TNumber Asech(TNumber x) noexcept
  {
    return MTL::Acosh(TNumber(1) / x);
  }
}
