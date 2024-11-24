#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Power/Sqrt.hpp"

#include <cmath>

namespace Krys::MTL
{
  /// @brief Computes the inverse square root of `x`, i.e., `1 / sqrt(x)`.
  /// @tparam TNumber An arithmetic type.
  /// @param x The input value (must be greater than zero).
  /// @returns The inverse square root of `x`.
  template <IsArithmeticT TNumber>
  NO_DISCARD constexpr TNumber InverseSqrt(TNumber x) noexcept
  {
    if (x <= TNumber(0))
      return -1; // Indicate an error for non-positive inputs
    else
      return TNumber(1) / Sqrt(x);
  }
}