#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Common/Constants.hpp"
#include "MTL/Trigonometric/Asin.hpp"

#include <cmath>

namespace Krys::MTL
{
  /// @brief Computes arccosine of `x` using the identity acos(x) = π/2 - asin(x).
  /// @tparam TNumber An arithmetic type.
  /// @param x The input value (must be in [-1, 1]).
  /// @returns The arccosine of `x` in radians.
  template <IsArithmeticT TNumber>
  constexpr TNumber Acos(TNumber x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
    {
      if (x < TNumber(-1) || x > TNumber(1))
        return std::numeric_limits<TNumber>::quiet_NaN(); // Undefined for |x| > 1

      return MTL::Pi<TNumber>() / 2 - MTL::Asin(x);
    }

    return std::acos(x);
  }
}