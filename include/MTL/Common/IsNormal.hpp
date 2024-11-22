#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Common/IsDenormal.hpp"
#include "MTL/Common/IsFinite.hpp"

#include <cmath>

namespace Krys::MTL
{
  /// @brief Checks if the given floating-point number is normal (neither zero, subnormal, infinite, nor NaN).
  /// @tparam TFloat A floating-point type.
  /// @param x The input value.
  /// @return `true` if `x` is a normal floating-point number, otherwise `false`.
  template <IsFloatingPointT TFloat>
  constexpr NO_DISCARD bool IsNormal(TFloat x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
      return MTL::IsFinite(x) && !MTL::IsDenormal(x) && x != static_cast<TFloat>(0);

    return std::isnormal(x);
  }
}
