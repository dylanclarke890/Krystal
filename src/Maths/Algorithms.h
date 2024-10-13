#pragma once

#include "Core.h"

namespace Krys::Maths
{
  template <typename T>
  REQUIRES(std::is_integral_v<T> || std::is_floating_point_v<T>)
  constexpr T Max(const T &a, const T &b) noexcept
  {
    return a > b ? a : b;
  }

  template <typename T>
  REQUIRES(std::is_integral_v<T> || std::is_floating_point_v<T>)
  constexpr T Min(const T &a, const T &b) noexcept
  {
    return a < b ? a : b;
  }

  template <typename T>
  REQUIRES(std::is_integral_v<T> || std::is_floating_point_v<T>)
  constexpr T Clamp(const T &value, const T &min, const T &max) noexcept
  {
    return Min<T>(Max<T>(value, min), max);
  }
}