#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Trigonometric/Sin.hpp"

namespace Krys::MTL
{
  /// @brief Computes cosecant.
  /// @tparam TNumber An arithmetic type (floating point types are advised).
  /// @param radians The input value.
  /// @returns The computed value.
  template <IsArithmeticT TNumber>
  NO_DISCARD constexpr TNumber Csc(TNumber radians) noexcept
  {
    return TNumber(1) / MTL::Sin(radians);
  }
}
