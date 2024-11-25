#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Common/Rounding.hpp"

namespace Krys::MTL
{
  /// @brief Computes the modulus of `a` and `b`.
  /// @tparam TNumber An arithmetic type.
  /// @param a Left operand.
  /// @param b Right operand.
  /// @returns The modulus of `a` and `b`.
  template <IsArithmeticT TNumber>
  NO_DISCARD constexpr TNumber Mod(TNumber a, TNumber b) noexcept
  {
    if constexpr (IsFloatingPointT<TNumber>)
      return TNumber(a - (MTL::Trunc(a / b) * b));
    else
      return a % b;
  }
}