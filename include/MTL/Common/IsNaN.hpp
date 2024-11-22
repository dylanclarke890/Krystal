#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"

#include <cmath>

namespace Krys::MTL
{
  /// @brief Checks if the given floating-point number is NaN (Not a Number).
  /// @tparam TFloat A floating-point type.
  /// @param x The input value.
  /// @return `true` if `x` is NaN, otherwise `false`.
  template <IsFloatingPointT TFloat>
  constexpr NO_DISCARD bool IsNaN(TFloat x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
      return x != x;

    return std::isnan(x);
  }
}
