#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Common/Abs.hpp"
#include "MTL/Common/IsNaN.hpp"

#include <cmath>

namespace Krys::MTL
{
  /// @brief Checks if `x` is denormalized (too small to be represented as a
  /// normalized number).
  /// @tparam TFloat A floating-point type.
  /// @param x The input value.
  /// @return `true` if `x` is denormalized, otherwise `false`.
  template <IsFloatingPointT TFloat>
  NO_DISCARD constexpr bool IsDenormal(TFloat x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
    {
      if (MTL::IsNaN(x) || x == TFloat(0))
        return false;
      return MTL::Abs(x) < std::numeric_limits<TFloat>::min();
    }

    return std::fpclassify(x) == FP_SUBNORMAL;
  }
}
