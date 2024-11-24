#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"

#include <cmath>

namespace Krys::MTL
{
  /// @brief Checks if `x` is infinite.
  /// @tparam TFloat A floating-point type.
  /// @param x The input value.
  /// @return `true` if `x` is infinite.
  template <IsFloatingPointT TFloat>
  NO_DISCARD constexpr bool IsInfinite(TFloat x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
      return x == ((x < 0 ? -1 : 1) * std::numeric_limits<TFloat>::infinity());
    else
      return std::isinf(x);
  }
}
