#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"

#include <cmath>

namespace Krys::MTL
{
  /// @brief Rounds `x` to the nearest integer. Halfway cases are rounded away from zero.
  /// @tparam TNumber A floating point type.
  /// @param x The input value.
  /// @return `x`, rounded to the nearest integer.
  template <IsFloatingPointT TNumber>
  constexpr NO_DISCARD TNumber Round(TNumber x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
    {
      if (x > 0)
        return static_cast<TNumber>(static_cast<long long>(x + 0.5));
      return static_cast<TNumber>(static_cast<long long>(x - 0.5));
    }

    return std::round(x);
  }
}