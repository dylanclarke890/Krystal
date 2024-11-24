#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Common/Abs.hpp"

#include <cmath>

namespace Krys::Impl
{
  /// @brief Recursive helper to compute the Taylor series.
  template <IsArithmeticT TNumber>
  constexpr TNumber ComputeExp(TNumber x, int term, TNumber power, TNumber factorial) noexcept
  {
    constexpr int MAX_TERMS = 100;
    if (term >= MAX_TERMS)
      return TNumber(0);
    term++;

    // Taylor series expansion for e^x: T(1) + x + x^2/2! + ...
    TNumber currentTerm = power / factorial;
    if (MTL::Abs(currentTerm) < std::numeric_limits<TNumber>::epsilon())
      return TNumber(0);
    else
      return currentTerm + Impl::ComputeExp(x, term, power * x, factorial * term);
  }
}

namespace Krys::MTL
{
  /// @brief Computes the natural exponential function of `x` (`e^x`).
  /// @tparam TNumber An arithmetic type.
  /// @param x The input value.
  /// @returns The result of `e` raised to the power of `x`.
  template <IsArithmeticT TNumber>
  constexpr TNumber Exp(TNumber x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
    {
      // Use the reciprocal e^x = 1 / e^-x for negative inputs
      if (x < TNumber(0))
        return TNumber(1) / MTL::Exp(-x);
      else
        return TNumber(1) + Impl::ComputeExp(x, 1, x, TNumber(1));
    }
    else
      return std::exp(x);
  }
}