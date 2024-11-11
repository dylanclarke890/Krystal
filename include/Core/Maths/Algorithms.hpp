#pragma once

#include "Base/Attributes.hpp"
#include "Base/Types.hpp"

namespace Krys::Maths
{
  template <IsArithmeticT TNumber>
  NO_DISCARD constexpr TNumber Max(TNumber a, TNumber b) noexcept
  {
    return a > b ? a : b;
  }

  template <IsArithmeticT TNumber>
  NO_DISCARD constexpr TNumber Min(TNumber a, TNumber b) noexcept
  {
    return a < b ? a : b;
  }

  template <IsArithmeticT TNumber>
  NO_DISCARD constexpr TNumber Clamp(TNumber value, TNumber min, TNumber max) noexcept
  {
    return Min<TNumber>(Max<TNumber>(value, min), max);
  }
}