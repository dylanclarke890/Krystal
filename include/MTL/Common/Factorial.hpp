#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"

namespace Krys::MTL
{
  /// @brief Computes the factorial of `n`.
  /// @tparam TNumber An unsigned integer type.
  /// @param n The input value.
  /// @returns The factorial of `n`, i.e., `n! = n * (n-1) * ... * 1`. For `n = 0`, returns `1`.
  template <IsArithmeticT TNumber>
  constexpr TNumber Factorial(TNumber n) noexcept
  {
    TNumber result = TNumber(1);
    for (TNumber i = 1; i <= n; i++)
      result *= i;
    return result;
  }
}