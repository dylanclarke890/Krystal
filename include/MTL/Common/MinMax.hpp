#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Common/FpClassify.hpp"

namespace Krys::MTL
{
#pragma region Min

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

#pragma endregion Min

#pragma region FMin

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

#pragma endregion FMin

#pragma region Max

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

#pragma endregion Max

#pragma region FMax

  /// @brief Returns the larger of two floating-point values, ignoring NaN.
  /// @tparam TFloat A floating-point type.
  /// @param a The first input value.
  /// @param b The second input value.
  /// @returns The larger of `a` and `b`, or `b` if `a` is NaN.
  template <IsFloatingPointT TFloat>
  NO_DISCARD constexpr TFloat FMax(TFloat a, TFloat b) noexcept
  {
    if (MTL::IsNaN(a))
      return b;
    else
      return MTL::Max(a, b);
  }

  /// @brief Returns the largest of three floating-point values, ignoring NaN.
  /// @tparam TFloat A floating-point type.
  /// @param a The first input value.
  /// @param b The second input value.
  /// @param c The third input value.
  /// @returns The largest of `a`, `b`, and `c`, ignoring NaN values.
  template <IsFloatingPointT TFloat>
  NO_DISCARD constexpr TFloat FMax(TFloat a, TFloat b, TFloat c) noexcept
  {
    if (MTL::IsNaN(a))
      return MTL::FMax(b, c);
    else if (MTL::IsNaN(b))
      return MTL::FMax(a, c);
    else if (MTL::IsNaN(c))
      return MTL::Max(a, b);
    else
      return MTL::Max(a, b, c);
  }

  /// @brief Returns the largest of four floating-point values, ignoring NaN.
  /// @tparam TFloat A floating-point type.
  /// @param a The first input value.
  /// @param b The second input value.
  /// @param c The third input value.
  /// @param d The fourth input value.
  /// @returns The largest of `a`, `b`, `c`, and `d`, ignoring NaN values.
  template <IsFloatingPointT TFloat>
  NO_DISCARD constexpr TFloat FMax(TFloat a, TFloat b, TFloat c, TFloat d) noexcept
  {
    if (MTL::IsNaN(a))
      return MTL::FMax(b, c, d);
    else if (MTL::IsNaN(b))
      return MTL::Max(a, MTL::FMax(c, d));
    else if (MTL::IsNaN(c))
      return MTL::FMax(MTL::Max(a, b), d);
    else if (MTL::IsNaN(d))
      return MTL::Max(a, b, c);
    else
      return MTL::Max(a, b, c, d);
  }

#pragma endregion FMax
}