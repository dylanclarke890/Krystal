#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"

#include <cmath>

namespace Krys::MTL
{
  /// @brief Rounds `x` to the nearest integer. Halfway cases are rounded away from zero.
  /// @tparam TFloat A floating point type.
  /// @param x The input value.
  /// @return `x`, rounded to the nearest integer.
  template <IsFloatingPointT TFloat>
  NO_DISCARD constexpr TFloat Round(TFloat x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
      return TFloat(static_cast<long long>(x + (x > TFloat(0) ? TFloat(0.5) : TFloat(-0.5))));
    else
      return std::round(x);
  }
}