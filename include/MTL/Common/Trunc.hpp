#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"

#include <cmath>

namespace Krys::MTL
{
  /// @brief Computes the nearest integer not greater in magnitude than `x`.
  /// @tparam TFloat A floating point type.
  /// @param x The input value.
  /// @return The nearest integer not greater in magnitude than `x`.
  template <IsFloatingPointT TFloat>
  NO_DISCARD constexpr TFloat Trunc(TFloat x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
      return TFloat(static_cast<long long>(x));
    else
      return std::trunc(x);
  }
}