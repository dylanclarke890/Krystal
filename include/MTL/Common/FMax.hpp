#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"
#include "MTL/Common/IsNaN.hpp"
#include "MTL/Common/Max.hpp"

namespace Krys::MTL
{
  /// @brief Returns the larger of two floating-point values, ignoring NaN.
  /// @tparam TFloat A floating-point type.
  /// @param a The first value.
  /// @param b The second value.
  /// @returns The larger of `a` and `b`, or `b` if `a` is NaN.
  template <IsFloatingPointT TFloat>
  constexpr NO_DISCARD TFloat FMax(TFloat a, TFloat b) noexcept
  {
    if (MTL::IsNaN(a))
      return b;
    return MTL::Max(a, b);
  }

  /// @brief Returns the largest of three floating-point values, ignoring NaN.
  /// @tparam TNumber A floating-point type.
  /// @param a The first value.
  /// @param b The second value.
  /// @param c The third value.
  /// @returns The largest of `a`, `b`, and `c`, ignoring NaN values.
  template <IsFloatingPointT TNumber>
  constexpr NO_DISCARD TNumber FMax(TNumber a, TNumber b, TNumber c) noexcept
  {
    if (MTL::IsNaN(a))
      return MTL::FMax(b, c);
    if (MTL::IsNaN(b))
      return MTL::FMax(a, c);
    if (MTL::IsNaN(c))
      return MTL::Max(a, b);
    return MTL::Max(a, b, c);
  }

  /// @brief Returns the largest of four floating-point values, ignoring NaN.
  /// @tparam TNumber A floating-point type.
  /// @param a The first value.
  /// @param b The second value.
  /// @param c The third value.
  /// @param d The fourth value.
  /// @returns The largest of `a`, `b`, `c`, and `d`, ignoring NaN values.
  template <IsFloatingPointT TNumber>
  constexpr NO_DISCARD TNumber FMax(TNumber a, TNumber b, TNumber c, TNumber d) noexcept
  {
    if (MTL::IsNaN(a))
      return MTL::FMax(b, c, d);
    if (MTL::IsNaN(b))
      return MTL::Max(a, MTL::FMax(c, d));
    if (MTL::IsNaN(c))
      return MTL::FMax(MTL::Max(a, b), d);
    if (MTL::IsNaN(d))
      return MTL::Max(a, b, c);
    return MTL::Max(a, b, c, d);
  }
}