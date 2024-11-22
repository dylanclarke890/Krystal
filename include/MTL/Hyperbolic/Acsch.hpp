#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Hyperbolic/Asinh.hpp"

namespace Krys::MTL
{
  /// @brief Computes the inverse hyperbolic cosecant of `x`.
  /// @tparam TNumber An arithmetic type.
  /// @param x The input value.
  /// @returns The inverse hyperbolic cosecant of `x`.
  template <IsArithmeticT TNumber>
  NO_DISCARD constexpr TNumber Acsch(TNumber x) noexcept
  {
    return MTL::Asinh(TNumber(1) / x);
  }
}
