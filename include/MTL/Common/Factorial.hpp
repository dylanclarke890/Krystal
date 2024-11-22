#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"

namespace Krys::MTL
{
  /// @brief Computes the factorial of `n`.
  /// @tparam TNumber An unsigned integer type.
  /// @param n The input value.
  /// @returns The factorial of `n`, i.e., `n! = n * (n-1) * ... * 1`. For `n = 0`, returns `1`.
  template <IsUnsignedT TUnsignedInteger>
  constexpr TUnsignedInteger Factorial(TUnsignedInteger n) noexcept
  {
    TUnsignedInteger result = TUnsignedInteger(1);
    for (TUnsignedInteger i = 1; i <= n; i++)
      result *= i;
    return result;
  }
}