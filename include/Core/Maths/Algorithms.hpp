#pragma once

#include "Base/Attributes.hpp"
#include "Base/Types.hpp"

namespace Krys::Maths
{
  template <ArithmeticType T>
  NO_DISCARD constexpr T Max(const T &a, const T &b) noexcept
  {
    return a > b ? a : b;
  }

  template <ArithmeticType T>
  NO_DISCARD constexpr T Min(const T &a, const T &b) noexcept
  {
    return a < b ? a : b;
  }

  template <ArithmeticType T>
  NO_DISCARD constexpr T Clamp(const T &value, const T &min, const T &max) noexcept
  {
    return Min<T>(Max<T>(value, min), max);
  }

  // constexpr Vec3 Lerp(const Vec3 &a, const Vec3 &b, float weight) noexcept
  // {
  //   return ((1.0f - weight) * a) + (weight * b);
  // }
}