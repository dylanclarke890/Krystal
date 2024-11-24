#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"
#include "MTL/Exponential/Log.hpp"

#include <cmath>

namespace Krys::MTL
{
  /// @brief Computes the inverse hyperbolic tangent of `x`.
  /// @tparam TNumber An arithmetic type.
  /// @param x The input value.
  /// @returns The inverse hyperbolic tangent of `x`.
  template <IsArithmeticT TNumber>
  constexpr TNumber Atanh(TNumber x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
    {
      if (x <= TNumber(-1) || x >= TNumber(1))
        return std::numeric_limits<TNumber>::quiet_NaN(); // Undefined for |x| >= 1
      else
        return TNumber(0.5) * MTL::Log((TNumber(1) + x) / (TNumber(1) - x));
    }
    else
      return std::atanh(x);
  }
}