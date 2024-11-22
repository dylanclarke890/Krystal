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
  // Helper function for computing the arcsine using Taylor series expansion
  template <IsArithmeticT TNumber>
  constexpr TNumber _compute_asin(TNumber x, size_t n, TNumber current_power, TNumber current_factorial,
                                  size_t max_terms) noexcept
  {
    if (n >= max_terms)
      return TNumber(0);

    TNumber numerator = MTL::Factorial(2 * n) * current_power;
    TNumber denominator =
      MTL::Pow(TNumber(4), static_cast<int>(n)) * MTL::Pow(MTL::Factorial(n), 2) * (2 * n + 1);
    TNumber current_term = numerator / denominator;
    return current_term + _compute_asin(x, n + 1, current_power * x * x, current_factorial, max_terms);
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

      if (x == TNumber(1))
        return MTL::Pi<TNumber>() / TNumber(2);
      if (x == TNumber(-1))
        return -MTL::Pi<TNumber>() / TNumber(2);

      constexpr size_t max_terms = 10; // Adjust for desired accuracy
      return Impl::_compute_asin(x, 0, x, TNumber(1), max_terms);
    }

    return std::asin(x);
  }
}