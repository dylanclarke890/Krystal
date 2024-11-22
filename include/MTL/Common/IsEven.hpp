#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"

namespace Krys::MTL
{
  /// @brief Checks if `x` is even.
  /// @tparam TInteger An integer type.
  /// @param x The input value.
  /// @return `true` if `x` is even, otherwise `false`.
  template <IsIntegralT TInteger>
  NO_DISCARD constexpr bool IsEven(TInteger x) noexcept
  {
    return x % 2 == 0;
  }
}
