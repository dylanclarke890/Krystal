#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"

#include <cmath>

namespace Krys::Impl
{
  // Helper function for computing cosh using Taylor series expansion.
  template <IsArithmeticT TNumber>
  constexpr TNumber _compute_cosh(TNumber x, size_t n, TNumber current_power, TNumber current_factorial,
                                  size_t max_terms) noexcept
  {
    if (n >= max_terms)
      return TNumber(0);
    TNumber current_term = current_power / current_factorial;
    return current_term
           + _compute_cosh(x, n + 1, current_power * x * x, current_factorial * (2 * n + 1) * (2 * n + 2),
                           max_terms);
  }
}

namespace Krys::MTL
{
  /// @brief Computes the hyperbolic cosine of `x`.
  /// @tparam TNumber An arithmetic type.
  /// @param x The input value.
  /// @returns The hyperbolic cosine of `x`.
  template <IsArithmeticT TNumber>
  constexpr TNumber Cosh(TNumber x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
    {
      constexpr size_t max_terms = 11; // Adjust for desired accuracy
      return Impl::_compute_cosh(x, 0, TNumber(1), TNumber(1), max_terms);
    }

    return std::cosh(x);
  }
}