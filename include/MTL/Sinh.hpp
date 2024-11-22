#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"

#include <cmath>

namespace Krys::Impl
{
  // Helper function for computing sinh using Taylor series expansion
  template <IsArithmeticT TNumber>
  constexpr TNumber _compute_sinh(TNumber x, size_t n, TNumber current_power, TNumber current_factorial,
                                  size_t max_terms) noexcept
  {
    if (n >= max_terms)
      return TNumber(0);
    TNumber current_term = current_power / current_factorial;
    return current_term
           + _compute_sinh(x, n + 1, current_power * x * x, current_factorial * (2 * n + 2) * (2 * n + 3),
                           max_terms);
  }
}

namespace Krys::MTL
{
  /// @brief Computes hyperbolic sine of `x`.
  template <IsArithmeticT TNumber>
  constexpr TNumber Sinh(TNumber x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
    {
      constexpr size_t max_terms = 11; // Adjust for desired accuracy
      return Impl::_compute_sinh(x, 0, x, TNumber(1), max_terms);
    }

    return std::sinh(x);
  }
}