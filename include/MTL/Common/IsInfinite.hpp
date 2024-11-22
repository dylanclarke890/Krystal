#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"

#include <cmath>

namespace Krys::MTL
{
  /// @brief Checks if the given floating-point number is infinite.
  /// @tparam TFloat A floating-point type.
  /// @param x The input value.
  /// @return `true` if `x` is infinite, otherwise `false`.
  template <IsFloatingPointT TFloat>
  constexpr NO_DISCARD bool IsInfinite(TFloat x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
      return x == ((x < 0 ? -1 : 1) * std::numeric_limits<TFloat>::infinity());

    return std::isinf(x);
  }
}
