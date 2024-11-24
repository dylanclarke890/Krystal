#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Common/Abs.hpp"

#include <cmath>

namespace Krys::Impl
{
  /// @brief Helper function for computing the cosine using Taylor series expansion.
  template <IsArithmeticT TNumber>
  constexpr TNumber ComputeCos(TNumber x, int n, TNumber power, TNumber factorial) noexcept
  {
    constexpr int MAX_TERMS = 100;
    if (n >= MAX_TERMS)
      return TNumber(0);

    int sign = (n % 2 == 0) ? 1 : -1;

    TNumber currentTerm = sign * power / factorial;
    if (MTL::Abs(currentTerm) < std::numeric_limits<TNumber>::epsilon())
      return TNumber(0);
    else
      return currentTerm + ComputeCos(x, n + 1, power * x * x, factorial * (2 * n + 1) * (2 * n + 2));
  }
}

namespace Krys::MTL
{
  /// @brief Computes cosine of `x` using Taylor series expansion.
  /// @tparam TNumber An arithmetic type.
  /// @param x The input value in radians.
  /// @returns The cosine of `x`.
  template <IsArithmeticT TNumber>
  constexpr TNumber Cos(TNumber x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
      return Impl::ComputeCos(x, 0, TNumber(1), TNumber(1));
    else
      return std::cos(x);
  }
}