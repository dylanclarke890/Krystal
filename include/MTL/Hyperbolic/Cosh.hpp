#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Common/Abs.hpp"

#include <cmath>

namespace Krys::Impl
{
  /// @brief Helper function for computing cosh using Taylor series expansion.
  template <IsArithmeticT TNumber>
  constexpr TNumber ComputeCosh(TNumber x, int n, TNumber power, TNumber factorial) noexcept
  {
    constexpr int MAX_TERMS = 100;
    if (n >= MAX_TERMS)
      return TNumber(0);

    TNumber currentTerm = power / factorial;
    if (MTL::Abs(currentTerm) < std::numeric_limits<TNumber>::epsilon())
      return TNumber(0);
    else
      return currentTerm + ComputeCosh(x, n + 1, power * x * x, factorial * (2 * n + 1) * (2 * n + 2));
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
      return Impl::ComputeCosh(x, 0, TNumber(1), TNumber(1));
    else
      return std::cosh(x);
  }
}