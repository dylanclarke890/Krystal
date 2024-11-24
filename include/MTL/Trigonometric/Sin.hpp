#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Common/Abs.hpp"

#include <cmath>

namespace Krys::Impl
{
  /// @brief Helper function for computing the sine using Taylor series expansion.
  template <IsArithmeticT TNumber>
  constexpr TNumber ComputeSin(TNumber x, int n, TNumber power, TNumber factorial) noexcept
  {
    constexpr int MAX_TERMS = 100;
    if (n >= MAX_TERMS)
      return TNumber(0);

    int sign = (n % 2 == 0) ? 1 : -1;
    TNumber currentTerm = sign * power / factorial;
    if (MTL::Abs(currentTerm) < std::numeric_limits<TNumber>::epsilon())
      return TNumber(0);
    else
      return currentTerm + ComputeSin(x, n + 1, power * x * x, factorial * (2 * n + 2) * (2 * n + 3));
  }
}

namespace Krys::MTL
{
  /// @brief Computes sine of `x` using Taylor series expansion.
  /// @tparam TNumber An arithmetic type.
  /// @param x The input value in radians.
  /// @returns The sine of `x`.
  template <IsArithmeticT TNumber>
  constexpr TNumber Sin(TNumber x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
      return Impl::ComputeSin(x, 0, x, TNumber(1));
    else
      return std::sin(x);
  }
}