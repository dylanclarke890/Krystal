#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Exponential/Exp.hpp"
#include "MTL/Power/Sqrt.hpp"
#include "MTL/Vectors/Vec2.hpp"

namespace Krys::MTL
{
  template <typename T>
  NO_DISCARD constexpr T Gauss(T x, T expected, T stdDeviation) noexcept
  {
    return Exp(-((x - expected) * (x - expected)) / (T(2) * stdDeviation * stdDeviation))
           / (stdDeviation * Sqrt(T(6.28318530717958647692528676655900576)));
  }

  template <typename T>
  NO_DISCARD constexpr T Gauss(const vec2_t<T> &coord, const vec2_t<T> &expected,
                               const vec2_t<T> &stdDeviation) noexcept
  {
    const vec2_t<T> squared =
      ((coord - expected) * (coord - expected)) / (T(2) * stdDeviation * stdDeviation);
    return Exp(-(squared.x + squared.y));
  }
}