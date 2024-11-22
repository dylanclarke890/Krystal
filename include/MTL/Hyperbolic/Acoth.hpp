#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Hyperbolic/Atanh.hpp"

namespace Krys::MTL
{
  /// @brief Computes the inverse hyperbolic cotangent of `x`.
  /// @tparam TNumber An arithmetic type.
  /// @param x The input value.
  /// @returns The inverse hyperbolic cotangent of `x`.
  template <IsArithmeticT TNumber>
  NO_DISCARD constexpr TNumber Acoth(TNumber x) noexcept
  {
    return MTL::Atanh(TNumber(1) / x);
  }
}
