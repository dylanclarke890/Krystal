#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Hyperbolic/Sinh.hpp"

#include <cmath>

namespace Krys::MTL
{
  /// @brief Computes the hyperbolic cosecant of `x`.
  /// @tparam TNumber An arithmetic type.
  /// @param x The input value.
  /// @returns The hyperbolic cosecant of `x`.
  template <IsArithmeticT TNumber>
  NO_DISCARD constexpr TNumber Csch(TNumber radians) noexcept
  {
    return TNumber(1) / MTL::Sinh(radians);
  }
}
