#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"

#include <cmath>

namespace Krys::Impl
{
  // Recursive helper to compute the Taylor series
  template <IsArithmeticT TNumber>
  constexpr TNumber _compute_exp(TNumber x, size_t term, TNumber current_power, TNumber current_factorial,
                                 size_t max_terms) noexcept
  {
    if (term >= max_terms)
      return TNumber(0);

    TNumber current_term = current_power / current_factorial;
    return current_term
           + _compute_exp(x, term + 1, current_power * x, current_factorial * (term + 1), max_terms);
  }
}

namespace Krys::MTL
{
  /// @brief Computes the natural exponential function of `x`, i.e., `e^x`.
  /// @tparam TNumber An arithmetic type.
  /// @param x The input value.
  /// @returns The result of `e` raised to the power of `x`.
  template <IsArithmeticT TNumber>
  constexpr TNumber Exp(TNumber x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
    {
      // Use the property e^x = 1 / e^-x for negative inputs
      if (x < TNumber(0))
        return TNumber(1) / Exp(-x);

      // Taylor series expansion for e^x: T(1) + x + x^2/2! + ...
      constexpr size_t max_terms = 30;
      return TNumber(1) + _compute_exp(x, 1, x, TNumber(1), max_terms);
    }

    return std::exp(x);
  }
}