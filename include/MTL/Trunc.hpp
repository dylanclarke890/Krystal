#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"

#include <cmath>

namespace Krys::MTL
{
  /// @brief Computes the nearest integer not greater in magnitude than `x`.
  /// @tparam TNumber A floating point type.
  /// @param x The input value.
  /// @return The nearest integer not greater in magnitude than `x`.
  template <IsFloatingPointT TNumber>
  constexpr NO_DISCARD TNumber Trunc(TNumber x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
      return static_cast<TNumber>(static_cast<long long>(x));

    return std::trunc(x);
  }
}