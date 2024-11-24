#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"
#include "MTL/Common/Constants.hpp"
#include "MTL/Common/Factorial.hpp"
#include "MTL/Power/Pow.hpp"

#include <cmath>

namespace Krys::Impl
{
  /// @brief Helper function for computing the arcsine using Taylor series expansion.
  template <IsArithmeticT TNumber>
  constexpr TNumber ComputeAsin(TNumber x, size_t n, TNumber power, TNumber factorial) noexcept
  {
    constexpr size_t max_terms = 10; // Adjust for desired accuracy
    if (n >= max_terms)
      return TNumber(0);

    TNumber numerator = MTL::Factorial(2 * n) * power;
    TNumber denominator = MTL::Pow(TNumber(4), static_cast<int>(n))
                          * MTL::Pow(MTL::Factorial(n), static_cast<size_t>(2)) * (2 * n + 1);
    TNumber currentTerm = numerator / denominator;
    return currentTerm + ComputeAsin(x, n + 1, power * x * x, factorial);
  }
}

namespace Krys::MTL
{
  /// @brief Computes arcsine of `x` using series expansion.
  /// @tparam TNumber An arithmetic type.
  /// @param x The input value (must be in [-1, 1]).
  /// @returns The arcsine of `x` in radians.
  template <IsArithmeticT TNumber>
  constexpr TNumber Asin(TNumber x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
    {
      if (x < TNumber(-1) || x > TNumber(1))
        return std::numeric_limits<TNumber>::quiet_NaN(); // Undefined for |x| > 1
      else if (x == TNumber(1))
        return MTL::Pi<TNumber>() / TNumber(2);
      else if (x == TNumber(-1))
        return -MTL::Pi<TNumber>() / TNumber(2);
      else
        return Impl::ComputeAsin(x, 0, x, TNumber(1));
    }
    else
      return std::asin(x);
  }
}