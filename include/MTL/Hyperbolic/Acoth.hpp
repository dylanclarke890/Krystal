#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Hyperbolic/Atanh.hpp"

namespace Krys::MTL
{
  /// @brief Computes inverse cotangent.
  /// @tparam TNumber An arithmetic type (floating point types are advised).
  /// @param x The input value.
  /// @returns The computed value.
  template <IsArithmeticT TNumber>
  constexpr NO_DISCARD TNumber Acoth(TNumber x) noexcept
  {
    return MTL::Atanh(TNumber(1) / x);
  }
}
