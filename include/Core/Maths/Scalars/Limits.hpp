#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"

namespace Krys::MTL
{
#pragma region Min

  /// @brief Returns the smaller of two values.
  /// @tparam TNumber An arithmetic type.
  /// @param a The first value.
  /// @param b The second value.
  /// @returns The smaller of `a` and `b`.
  template <IsArithmeticT TNumber>
  constexpr NO_DISCARD TNumber Min(TNumber a, TNumber b) noexcept
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
  constexpr NO_DISCARD TNumber Min(TNumber a, TNumber b, TNumber c) noexcept
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
  constexpr NO_DISCARD TNumber Min(TNumber a, TNumber b, TNumber c, TNumber d) noexcept
  {
    return MTL::Min(MTL::Min(a, b), MTL::Min(c, d));
  }

#pragma endregion Min

#pragma region FMin

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

#pragma endregion FMin

#pragma region Max

  /// @brief Returns the larger of two values.
  /// @tparam TNumber An arithmetic type.
  /// @param a The first value.
  /// @param b The second value.
  /// @returns The larger of `a` and `b`.
  template <IsArithmeticT TNumber>
  constexpr NO_DISCARD TNumber Max(TNumber a, TNumber b) noexcept
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
  constexpr NO_DISCARD TNumber Max(TNumber a, TNumber b, TNumber c) noexcept
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
  constexpr NO_DISCARD TNumber Max(TNumber a, TNumber b, TNumber c, TNumber d) noexcept
  {
    return MTL::Max(MTL::Max(a, b), MTL::Max(c, d));
  }

#pragma endregion Max

#pragma region FMax

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

#pragma endregion FMax

  /// @brief Clamps a value to lie within the specified range.
  /// @tparam TNumber An arithmetic type.
  /// @param value The input value.
  /// @param min The lower bound of the range.
  /// @param max The upper bound of the range.
  /// @returns The clamped value, such that `min <= result <= max`.
  template <IsArithmeticT TNumber>
  constexpr NO_DISCARD TNumber Clamp(TNumber value, TNumber min, TNumber max) noexcept
  {
    return MTL::Min<TNumber>(MTL::Max<TNumber>(value, min), max);
  }
}