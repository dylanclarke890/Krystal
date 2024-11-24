#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Exponential/Log.hpp"
#include "MTL/Power/Sqrt.hpp"

#include <cmath>

namespace Krys::MTL
{
  /// @brief Computes the inverse hyperbolic cosine of `x`.
  /// @tparam TNumber An arithmetic type.
  /// @param x The input value.
  /// @returns The inverse hyperbolic cosine of `x`.
  template <IsArithmeticT TNumber>
  constexpr TNumber Acosh(TNumber x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
    {
      if (x < TNumber(1))
        return std::numeric_limits<TNumber>::quiet_NaN(); // Undefined for x < 1
      else
        return Log(x + Sqrt(x * x - TNumber(1)));
    }
    else
      return std::acosh(x);
  }
}