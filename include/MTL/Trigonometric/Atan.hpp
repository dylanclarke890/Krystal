#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Common/Abs.hpp"
#include "MTL/Common/Constants.hpp"

#include <cmath>

namespace Krys::Impl
{
  /// @brief Helper function for computing the arctangent using Taylor series expansion.
  template <IsArithmeticT TNumber>
  constexpr TNumber ComputeAtan(TNumber x, int n, TNumber power) noexcept
  {
    constexpr int MAX_TERMS = 100;
    if (n >= MAX_TERMS)
      return TNumber(0);

    int sign = (n % 2 == 0) ? 1 : -1;

    TNumber currentTerm = sign * power / TNumber(2 * n + 1);
    if (MTL::Abs(currentTerm) < std::numeric_limits<TNumber>::epsilon())
      return TNumber(0);
    else
      return currentTerm + ComputeAtan(x, n + 1, power * x * x);
  }
}

namespace Krys::MTL
{
  /// @brief Computes arctangent of `x` using series expansion.
  /// @tparam TNumber An arithmetic type.
  /// @param x The input value.
  /// @returns The arctangent of `x` in radians.
  template <IsArithmeticT TNumber>
  constexpr TNumber Atan(TNumber x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
    {
      constexpr TNumber PI = MTL::Pi<TNumber>();
      if (x == TNumber(1))
        return PI / TNumber(4);
      else if (x == TNumber(-1))
        return -PI / TNumber(4);
      else if (x < TNumber(-1))
        return -PI / TNumber(2) - Impl::ComputeAtan(TNumber(1) / x, 0, TNumber(1) / x);
      else if (x > TNumber(1))
        return PI / TNumber(2) - Impl::ComputeAtan(TNumber(1) / x, 0, TNumber(1) / x);
      else
        return Impl::ComputeAtan(x, 0, x);
    }
    else
      return std::atan(x);
  }
}