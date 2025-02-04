#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"
#include "Debug/Macros.hpp"
#include "MTL/Common/Clamp.hpp"

namespace Krys::MTL
{
  /// @brief Linearly interpolate between two values based on `t`.
  /// @tparam TNumber An arithmetic type.
  /// @tparam TWeight A floating point type.
  /// @param x Start value.
  /// @param y End value.
  /// @param t Weight between 0 and 1 to control interpolation.
  /// @return The interpolated value.
  template <IsArithmeticT TNumber, IsFloatingPointT TWeight>
  NO_DISCARD constexpr TNumber Lerp(TNumber x, TNumber y, TWeight t) noexcept
  {
    t = Clamp(t, TWeight(0), TWeight(1));
    return TWeight(x) * (TWeight(1) - t) + (TWeight(y) * t);
  }

  /// @brief Creates a cubic interpolation between x and y with ease-in and ease-out effects.
  /// @tparam TNumber An arithmetic type.
  /// @tparam TWeight A floating point type.
  /// @param x Start value.
  /// @param y End value.
  /// @param t Weight between 0 and 1 to control interpolation.
  /// @return The interpolated value.
  template <IsArithmeticT TNumber, IsFloatingPointT TWeight>
  NO_DISCARD constexpr TNumber Smoothstep(TNumber x, TNumber y, TWeight t) noexcept
  {
    t = Clamp((t - static_cast<TWeight>(x)) / static_cast<TWeight>(y - x), TWeight(0), TWeight(1));
    return t * t * (TWeight(3) - TWeight(2) * t);
  }

  /// @brief Sharply interpolates between x and y based on the value of t.
  /// @tparam TNumber An arithmetic type.
  /// @tparam TWeight A floating point type.
  /// @param x Start value.
  /// @param y End value.
  /// @param t Weight between 0 and 1 to control interpolation.
  /// @return The interpolated value. x is returned if t is >= 0.5, y otherwise.
  template <IsArithmeticT TNumber, IsFloatingPointT TWeight>
  NO_DISCARD constexpr TNumber Step(TNumber x, TNumber y, TWeight t) noexcept
  {
    if (t < TWeight(0.5))
      return x;
    return y;
  }

  /// @tparam TNumber An arithmetic type.
  /// @tparam TWeight A floating point type.
  /// @returns 0.0 if x < edge, otherwise it returns 1.0.
  template <IsArithmeticT TNumber, IsArithmeticT TWeight>
  NO_DISCARD constexpr TNumber Step(TNumber edge, TWeight x) noexcept
  {
    if (x < static_cast<TWeight>(edge))
      return TNumber(0.0);
    return TNumber(1.0);
  }
}