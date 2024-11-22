#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"

#include <cmath>

namespace Krys::MTL
{
  /// @brief Computes the smallest integer that isn't smaller than `x`.
  /// @tparam TNumber A floating point type.
  /// @param x The input value.
  /// @return The smallest integer that isn't smaller than `x`.
  template <IsFloatingPointT TNumber>
  constexpr NO_DISCARD TNumber Ceil(TNumber x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
    {
      if (static_cast<long long>(x) == x)
        return x;
      return (x > 0.0) ? static_cast<long long>(x) + 1 : static_cast<long long>(x);
    }

    return std::ceil(x);
  }
}