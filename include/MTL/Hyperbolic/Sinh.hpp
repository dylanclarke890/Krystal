#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Common/Abs.hpp"

#include <cmath>

namespace Krys::Impl
{
  /// @brief Helper function for computing sinh using Taylor series expansion.
  template <IsArithmeticT TNumber>
  constexpr TNumber ComputeSinh(TNumber x, int n, TNumber power, TNumber factorial) noexcept
  {
    constexpr int MAX_TERMS = 100;
    if (n >= MAX_TERMS)
      return TNumber(0);

    TNumber currentTerm = power / factorial;
    if (MTL::Abs(currentTerm) < std::numeric_limits<TNumber>::epsilon())
      return TNumber(0);
    else
      return currentTerm + ComputeSinh(x, n + 1, power * x * x, factorial * (2 * n + 2) * (2 * n + 3));
  }
}

namespace Krys::MTL
{
  /// @brief Computes the hyperbolic sine of `x`.
  /// @tparam TNumber An arithmetic type.
  /// @param x The input value.
  /// @returns The hyperbolic sine of `x`.
  template <IsArithmeticT TNumber>
  constexpr TNumber Sinh(TNumber x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
      return Impl::ComputeSinh(x, 0, x, TNumber(1));
    else
      return std::sinh(x);
  }
}