#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Common/IsDenormal.hpp"
#include "MTL/Common/IsFinite.hpp"

#include <cmath>

namespace Krys::MTL
{
  /// @brief Checks if `x` is normal (neither zero, subnormal, infinite, nor NaN).
  /// @tparam TFloat A floating-point type.
  /// @param x The input value.
  /// @return `true` if `x` is a normal floating-point number.
  template <IsFloatingPointT TFloat>
  NO_DISCARD constexpr bool IsNormal(TFloat x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
      return MTL::IsFinite(x) && !MTL::IsDenormal(x) && x != TFloat(0);
    else
      return std::isnormal(x);
  }
}
