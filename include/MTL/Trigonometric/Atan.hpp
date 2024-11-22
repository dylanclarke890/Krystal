#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"
#include "MTL/Common/Constants.hpp"

#include <cmath>

namespace Krys::Impl
{
  // Helper function for computing the arctangent using Taylor series expansion
  template <IsArithmeticT TNumber>
  constexpr TNumber _compute_atan(TNumber x, size_t n, TNumber current_power, size_t max_terms) noexcept
  {
    if (n >= max_terms)
      return TNumber(0);
    int sign = (n % 2 == 0) ? 1 : -1;
    TNumber current_term = sign * current_power / TNumber(2 * n + 1);
    return current_term + _compute_atan(x, n + 1, current_power * x * x, max_terms);
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
      constexpr size_t max_terms = 15; // Adjust for desired accuracy
      constexpr TNumber PI = MTL::Pi<TNumber>();

      if (x == TNumber(1))
        return Pi<TNumber>() / TNumber(4);
      if (x == TNumber(-1))
        return -Pi<TNumber>() / TNumber(4);

      if (x < TNumber(-1))
        return -PI / TNumber(2) - Impl::_compute_atan(TNumber(1) / x, 0, TNumber(1) / x, max_terms);
      else if (x > TNumber(1))
        return PI / TNumber(2) - Impl::_compute_atan(TNumber(1) / x, 0, TNumber(1) / x, max_terms);
      else
        return Impl::_compute_atan(x, 0, x, max_terms);
    }

    return std::atan(x);
  }
}