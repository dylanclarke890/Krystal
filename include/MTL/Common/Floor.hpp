#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"

#include <cmath>

namespace Krys::MTL
{
  /// @brief Computes the largest integer that is smaller than `x`.
  /// @tparam TFloat A floating-point type.
  /// @param x The input value.
  /// @return The largest integer that is smaller than `x`.
  template <IsFloatingPointT TFloat>
  NO_DISCARD constexpr TFloat Floor(TFloat x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
    {
      if (static_cast<long long>(x) == x)
        return x;
      else
        return static_cast<long long>(x) - ((x < TFloat(0)) ? 1LL : 0LL);
    }
    else
      return std::floor(x);
  }
}