#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/IsNaN.hpp"
#include "MTL/Min.hpp"

namespace Krys::MTL
{
  /// @brief Returns the smaller of two floating-point values, ignoring NaN.
  /// @tparam TFloat A floating-point type.
  /// @param a The first value.
  /// @param b The second value.
  /// @returns The smaller of `a` and `b`, or `b` if `a` is NaN.
  template <IsFloatingPointT TFloat>
  constexpr NO_DISCARD TFloat FMin(TFloat a, TFloat b) noexcept
  {
    if (MTL::IsNaN(a))
      return b;
    return MTL::Min(a, b);
  }

  /// @brief Returns the smallest of three floating-point values, ignoring NaN.
  /// @tparam TNumber A floating-point type.
  /// @param a The first value.
  /// @param b The second value.
  /// @param c The third value.
  /// @returns The smallest of `a`, `b`, and `c`, ignoring NaN values.
  template <IsFloatingPointT TNumber>
  constexpr NO_DISCARD TNumber FMin(TNumber a, TNumber b, TNumber c) noexcept
  {
    if (MTL::IsNaN(a))
      return MTL::FMin(b, c);
    if (MTL::IsNaN(b))
      return MTL::FMin(a, c);
    if (MTL::IsNaN(c))
      return MTL::Min(a, b);
    return MTL::Min(a, b, c);
  }

  /// @brief Returns the smallest of four floating-point values, ignoring NaN.
  /// @tparam TNumber A floating-point type.
  /// @param a The first value.
  /// @param b The second value.
  /// @param c The third value.
  /// @param d The fourth value.
  /// @returns The smallest of `a`, `b`, `c`, and `d`, ignoring NaN values.
  template <IsFloatingPointT TNumber>
  constexpr NO_DISCARD TNumber FMin(TNumber a, TNumber b, TNumber c, TNumber d) noexcept
  {
    if (MTL::IsNaN(a))
      return MTL::FMin(b, c, d);
    if (MTL::IsNaN(b))
      return MTL::Min(a, MTL::FMin(c, d));
    if (MTL::IsNaN(c))
      return MTL::FMin(MTL::Min(a, b), d);
    if (MTL::IsNaN(d))
      return MTL::Min(a, b, c);
    return MTL::Min(a, b, c, d);
  }
}