#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Trunc.hpp"

namespace Krys::MTL
{
  /// @brief Computes the modulus of `a` and `b`.
  /// @tparam TNumber An arithmetic type.
  /// @param a Left operand.
  /// @param b Right operand.
  /// @returns The modulus of `a` and `b`.
  template <IsArithmeticT TNumber>
  constexpr NO_DISCARD TNumber Mod(TNumber a, TNumber b) noexcept
  {
    if constexpr (IsFloatingPointT<TNumber>())
      return static_cast<TNumber>(x - (MTL::Trunc<TNumber>(x / y) * y));

    return a % b;
  }
}