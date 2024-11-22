#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"

#include <cmath>

namespace Krys::MTL
{
  /// @brief Computes the absolute value of a signed number.
  /// @tparam TNumber A signed arithmetic type.
  /// @param x The input value.
  /// @returns The absolute value of `x`.
  template <IsSignedT TNumber>
  constexpr NO_DISCARD TNumber Abs(TNumber x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
      return (x < static_cast<TNumber>(0)) ? -x : x;

    return std::abs(x);
  }
}