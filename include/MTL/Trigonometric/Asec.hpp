#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Trigonometric/Acos.hpp"

namespace Krys::MTL
{
  /// @brief Computes inverse secant.
  /// @tparam TNumber An arithmetic type (floating point types are advised).
  /// @param x The input value.
  /// @returns The computed value.
  template <IsArithmeticT TNumber>
  NO_DISCARD constexpr TNumber Asec(TNumber x) noexcept
  {
    return MTL::Acos(TNumber(1) / x);
  }
}
