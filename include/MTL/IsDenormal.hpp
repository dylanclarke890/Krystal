#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Abs.hpp"
#include "MTL/Classify/IsNaN.hpp"

#include <cmath>

namespace Krys::MTL
{
  /// @brief Checks if the given floating-point number is denormalized (too small to be represented as a
  /// normalized number).
  /// @tparam TFloat A floating-point type.
  /// @param x The input value.
  /// @return `true` if `x` is denormalized, otherwise `false`.
  template <IsFloatingPointT TFloat>
  constexpr NO_DISCARD bool IsDenormal(TFloat x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
    {
      if (MTL::IsNaN(x))
        return false;
      return MTL::Abs(x) < std::numeric_limits<TFloat>::min() && MTL::Abs(x) > 0;
    }

    return std::fpclassify(x) == FP_SUBNORMAL;
  }
}
