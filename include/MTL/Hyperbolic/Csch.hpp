#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Sinh.hpp"

#include <cmath>

namespace Krys::MTL
{
  /// @brief Computes cosecant.
  /// @tparam TNumber An arithmetic type (floating point types are advised).
  /// @param radians The input value.
  /// @returns The computed value.
  template <IsArithmeticT TNumber>
  constexpr NO_DISCARD TNumber Csch(TNumber radians) noexcept
  {
    return TNumber(1) / MTL::Sinh(radians);
  }
}
