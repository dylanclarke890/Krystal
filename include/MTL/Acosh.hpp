#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Log.hpp"
#include "MTL/Sqrt.hpp"

#include <cmath>

namespace Krys::MTL
{
  /// @brief Computes inverse hyperbolic cosine of `x` using the identity acosh(x) = log(x + sqrt(x^2 - 1)).
  template <IsArithmeticT TNumber>
  constexpr TNumber Acosh(TNumber x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
    {
      if (x < TNumber(1))
        return std::numeric_limits<TNumber>::quiet_NaN(); // Undefined for x < 1

      return Log(x + Sqrt(x * x - TNumber(1)));
    }

    return std::acosh(x);
  }
}