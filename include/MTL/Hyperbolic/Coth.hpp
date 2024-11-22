#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Tanh.hpp"

namespace Krys::MTL
{
  /// @brief Computes cotangent.
  /// @tparam TNumber An arithmetic type (floating point types are advised).
  /// @param radians The input value.
  /// @returns The computed value.
  template <IsArithmeticT TNumber>
  constexpr NO_DISCARD TNumber Coth(TNumber radians) noexcept
  {
    return TNumber(1) / MTL::Tanh(radians);
  }
}
