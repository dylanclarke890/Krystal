#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"

#include <cmath>

namespace Krys::MTL
{
  /// @brief Computes the absolute value of a signed number.
  /// @tparam TNumber A signed arithmetic type.
  /// @param x The input value.
  /// @returns The absolute value of `x`.
  template <IsSignedT TNumber>
  constexpr NO_DISCARD TNumber Abs(TNumber x) noexcept
  {
    return std::abs(x);
  }

  /// @brief Computes the modulus of `x`.
  /// @tparam TNumber An arithmetic type.
  /// @param x The input value.
  /// @returns The modulus of `x` (remainder after division).
  template <IsArithmeticT TNumber>
  constexpr NO_DISCARD TNumber Mod(TNumber x) noexcept
  {
    return std::mod(x);
  }
}