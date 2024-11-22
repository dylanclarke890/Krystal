#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Hyperbolic/Acosh.hpp"

namespace Krys::MTL
{
  /// @brief Computes inverse secant.
  /// @tparam TNumber An arithmetic type (floating point types are advised).
  /// @param x The input value.
  /// @returns The computed value.
  template <IsArithmeticT TNumber>
  constexpr NO_DISCARD TNumber Asech(TNumber x) noexcept
  {
    return MTL::Acosh(TNumber(1) / x);
  }
}
