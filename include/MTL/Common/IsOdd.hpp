#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"

namespace Krys::MTL
{
  /// @brief Checks if the given number is odd.
  /// @tparam TNumber An arithmetic type.
  /// @param x The input value.
  /// @return `true` if `x` is odd, otherwise `false`.
  /// @note For floating-point types, this function is undefined and should not be used.
  template <IsIntegralT TNumber>
  constexpr NO_DISCARD bool IsOdd(TNumber x) noexcept
  {
    return x % 2 != 0;
  }
}
