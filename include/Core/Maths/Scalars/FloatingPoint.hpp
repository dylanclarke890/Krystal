#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"

#include <cmath>

namespace Krys::MTL
{
  template <IsFloatingPointT TFloat>
  constexpr NO_DISCARD bool IsNaN(TFloat a) noexcept
  {
    return std::isnan(a);
  }

  template <IsFloatingPointT TFloat>
  constexpr NO_DISCARD bool IsFinite(TFloat a) noexcept
  {
    return std::isfinite(a);
  }

  template <IsFloatingPointT TFloat>
  constexpr NO_DISCARD bool IsInf(TFloat a) noexcept
  {
    return std::isinf(a);
  }

  template <IsFloatingPointT TFloat>
  constexpr NO_DISCARD bool IsNormal(TFloat a) noexcept
  {
    return std::isnormal(a);
  }

  template <IsFloatingPointT TFloat>
  constexpr NO_DISCARD bool IsDenormal(TFloat a) noexcept
  {
    return std::fpclassify(x) == FP_SUBNORMAL;
  }
}