#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"

#include <cmath>

namespace Krys::MTL
{
  /// @brief Computes the largest integer that isn't greater than `x`.
  /// @tparam TNumber A floating-point type.
  /// @param x The input value.
  /// @return The largest integer that isn't greater than `x`.
  template <IsFloatingPointT TNumber>
  constexpr NO_DISCARD TNumber Floor(TNumber x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
    {
      if (static_cast<long long>(x) == x)
        return x;
      return (x > 0.0) ? static_cast<long long>(x) : static_cast<long long>(x) - 1;
    }

    return std::floor(x);
  }
}