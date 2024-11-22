#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Hyperbolic/Tanh.hpp"

namespace Krys::MTL
{
  /// @brief Computes the hyperbolic cotangent of `x`.
  /// @tparam TNumber An arithmetic type.
  /// @param x The input value.
  /// @returns The hyperbolic cotangent of `x`.
  template <IsArithmeticT TNumber>
  NO_DISCARD constexpr TNumber Coth(TNumber radians) noexcept
  {
    return TNumber(1) / MTL::Tanh(radians);
  }
}
