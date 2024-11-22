#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Trigonometric/Atan.hpp"

namespace Krys::MTL
{
  /// @brief Computes inverse cotangent.
  /// @tparam TNumber An arithmetic type (floating point types are advised).
  /// @param x The input value.
  /// @returns The computed value.
  template <IsArithmeticT TNumber>
  NO_DISCARD constexpr TNumber Acot(TNumber x) noexcept
  {
    return MTL::Atan(TNumber(1) / x);
  }
}
