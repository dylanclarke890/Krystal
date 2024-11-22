#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Common/IsInfinite.hpp"
#include "MTL/Common/IsNaN.hpp"

#include <cmath>

namespace Krys::MTL
{
  /// @brief Checks if `x` is finite.
  /// @tparam TFloat A floating-point type.
  /// @param x The input value.
  /// @return `true` if `x` is finite (not NaN or infinite), otherwise `false`.
  template <IsFloatingPointT TFloat>
  NO_DISCARD constexpr bool IsFinite(TFloat x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
      return !MTL::IsNaN(x) && !MTL::IsInfinite(x);

    return std::isfinite(x);
  }
}
