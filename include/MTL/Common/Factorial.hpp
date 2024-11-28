#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"

namespace Krys::MTL
{
  /// @brief Computes the factorial of `x`.
  /// @tparam TNumber An unsigned integer type.
  /// @param n The input value.
  /// @returns The factorial of `x` (`x!`). Returns `1` when `x = 0`.
  template <IsUnsignedT TUnsignedInteger>
  NO_DISCARD constexpr TUnsignedInteger Factorial(TUnsignedInteger x) noexcept
  {
    TUnsignedInteger result = TUnsignedInteger(1);
    for (TUnsignedInteger i = 1; i <= x; i++)
      result *= i;
    return result;
  }
}