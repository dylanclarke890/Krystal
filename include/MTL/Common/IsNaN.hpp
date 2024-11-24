#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"

#include <cmath>

namespace Krys::MTL
{
  /// @brief Checks if `x` is NaN (Not a Number).
  /// @tparam TFloat A floating-point type.
  /// @param x The input value.
  /// @return `true` if `x` is NaN.
  template <IsFloatingPointT TFloat>
  NO_DISCARD constexpr bool IsNaN(TFloat x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
      return x != x;
    else
      return std::isnan(x);
  }
}
