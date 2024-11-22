#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Trigonometric/Asin.hpp"

namespace Krys::MTL
{
  /// @brief Computes inverse cosecant.
  /// @tparam TNumber An arithmetic type (floating point types are advised).
  /// @param x The input value.
  /// @returns The computed value.
  template <IsArithmeticT TNumber>
  NO_DISCARD constexpr TNumber Acsc(TNumber x) noexcept
  {
    return MTL::Asin(TNumber(1) / x);
  }
}
