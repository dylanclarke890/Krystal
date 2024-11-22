#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"

namespace Krys::MTL
{
  /// @brief Returns the smaller of two values.
  /// @tparam TNumber An arithmetic type.
  /// @param a The first value.
  /// @param b The second value.
  /// @returns The smaller of `a` and `b`.
  template <IsArithmeticT TNumber>
  NO_DISCARD constexpr TNumber Min(TNumber a, TNumber b) noexcept
  {
    return a < b ? a : b;
  }

  /// @brief Returns the smallest of three values.
  /// @tparam TNumber An arithmetic type.
  /// @param a The first value.
  /// @param b The second value.
  /// @param c The third value.
  /// @returns The smallest of `a`, `b`, and `c`.
  template <IsArithmeticT TNumber>
  NO_DISCARD constexpr TNumber Min(TNumber a, TNumber b, TNumber c) noexcept
  {
    return MTL::Min(MTL::Min(a, b), c);
  }

  /// @brief Returns the smallest of four values.
  /// @tparam TNumber An arithmetic type.
  /// @param a The first value.
  /// @param b The second value.
  /// @param c The third value.
  /// @param d The fourth value.
  /// @returns The smallest of `a`, `b`, `c`, and `d`.
  template <IsArithmeticT TNumber>
  NO_DISCARD constexpr TNumber Min(TNumber a, TNumber b, TNumber c, TNumber d) noexcept
  {
    return MTL::Min(MTL::Min(a, b), MTL::Min(c, d));
  }
}