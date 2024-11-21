#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"
#include "Core/Maths/Scalars/Rounding.hpp"

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