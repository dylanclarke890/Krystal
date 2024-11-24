#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"

#include <cmath>

namespace Krys::MTL
{
  /// @brief Computes the smallest integer that is larger than `x`.
  /// @tparam TFloat A floating point type.
  /// @param x The input value.
  /// @return The smallest integer that is larger than `x`.
  template <IsFloatingPointT TFloat>
  NO_DISCARD constexpr TFloat Ceil(TFloat x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
    {
      if (static_cast<long long>(x) == x)
        return x;

      return static_cast<long long>(x) + ((x < TFloat(0)) ? 0LL : 1LL);
    }
    else
      return std::ceil(x);
  }
}