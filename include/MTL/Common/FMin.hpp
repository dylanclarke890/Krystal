#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Common/IsNaN.hpp"
#include "MTL/Common/Min.hpp"

namespace Krys::MTL
{
  /// @brief Returns the smaller of two floating-point values, ignoring NaN.
  /// @tparam TFloat A floating-point type.
  /// @param a The first input value.
  /// @param b The second input value.
  /// @returns The smaller of `a` and `b`, or `b` if `a` is NaN.
  template <IsFloatingPointT TFloat>
  NO_DISCARD constexpr TFloat FMin(TFloat a, TFloat b) noexcept
  {
    if (MTL::IsNaN(a))
      return b;
    else
      return MTL::Min(a, b);
  }

  /// @brief Returns the smallest of three floating-point values, ignoring NaN.
  /// @tparam TFloat A floating-point type.
  /// @param a The first input value.
  /// @param b The second input value.
  /// @param c The third input value.
  /// @returns The smallest of `a`, `b`, and `c`, ignoring NaN values.
  template <IsFloatingPointT TFloat>
  NO_DISCARD constexpr TFloat FMin(TFloat a, TFloat b, TFloat c) noexcept
  {
    if (MTL::IsNaN(a))
      return MTL::FMin(b, c);
    else if (MTL::IsNaN(b))
      return MTL::FMin(a, c);
    else if (MTL::IsNaN(c))
      return MTL::Min(a, b);
    else
      return MTL::Min(a, b, c);
  }

  /// @brief Returns the smallest of four floating-point values, ignoring NaN.
  /// @tparam TFloat A floating-point type.
  /// @param a The first input value.
  /// @param b The second input value.
  /// @param c The third input value.
  /// @param d The fourth input value.
  /// @returns The smallest of `a`, `b`, `c`, and `d`, ignoring NaN values.
  template <IsFloatingPointT TFloat>
  NO_DISCARD constexpr TFloat FMin(TFloat a, TFloat b, TFloat c, TFloat d) noexcept
  {
    if (MTL::IsNaN(a))
      return MTL::FMin(b, c, d);
    else if (MTL::IsNaN(b))
      return MTL::Min(a, MTL::FMin(c, d));
    else if (MTL::IsNaN(c))
      return MTL::FMin(MTL::Min(a, b), d);
    else if (MTL::IsNaN(d))
      return MTL::Min(a, b, c);
    else
      return MTL::Min(a, b, c, d);
  }
}