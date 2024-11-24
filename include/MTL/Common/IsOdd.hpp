#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"

namespace Krys::MTL
{
  /// @brief Checks if `x` is odd.
  /// @tparam TInteger An integer type.
  /// @param x The input value.
  /// @return `true` if `x` is odd.
  template <IsIntegralT TInteger>
  NO_DISCARD constexpr bool IsOdd(TInteger x) noexcept
  {
    return x % 2 != 0;
  }
}
