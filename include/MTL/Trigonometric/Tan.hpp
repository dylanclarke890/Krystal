#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Trigonometric/Cos.hpp"
#include "MTL/Trigonometric/Sin.hpp"

#include <cmath>

namespace Krys::MTL
{
  /// @brief Computes tangent of `x` as Sin(x) / Cos(x).
  /// @tparam TNumber An arithmetic type.
  /// @param x The input value in radians.
  /// @returns The tangent of `x`.
  template <IsArithmeticT TNumber>
  constexpr TNumber Tan(TNumber x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
    {
      TNumber cos_x = Cos(x);
      if (cos_x == TNumber(0))
        return std::numeric_limits<TNumber>::infinity();
      else
        return Sin(x) / cos_x;
    }
    else
      return std::tan(x);
  }
}