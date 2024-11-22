#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"

namespace Krys::MTL
{
  /// @brief Returns the larger of two values.
  /// @tparam TNumber An arithmetic type.
  /// @param a The first value.
  /// @param b The second value.
  /// @returns The larger of `a` and `b`.
  template <IsArithmeticT TNumber>
  NO_DISCARD constexpr TNumber Max(TNumber a, TNumber b) noexcept
  {
    return a > b ? a : b;
  }

  /// @brief Returns the largest of three values.
  /// @tparam TNumber An arithmetic type.
  /// @param a The first value.
  /// @param b The second value.
  /// @param c The third value.
  /// @returns The largest of `a`, `b`, and `c`.
  template <IsArithmeticT TNumber>
  NO_DISCARD constexpr TNumber Max(TNumber a, TNumber b, TNumber c) noexcept
  {
    return MTL::Max(MTL::Max(a, b), c);
  }

  /// @brief Returns the largest of four values.
  /// @tparam TNumber An arithmetic type.
  /// @param a The first value.
  /// @param b The second value.
  /// @param c The third value.
  /// @param d The fourth value.
  /// @returns The largest of `a`, `b`, `c`, and `d`.
  template <IsArithmeticT TNumber>
  NO_DISCARD constexpr TNumber Max(TNumber a, TNumber b, TNumber c, TNumber d) noexcept
  {
    return MTL::Max(MTL::Max(a, b), MTL::Max(c, d));
  }
}