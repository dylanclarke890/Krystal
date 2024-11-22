#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Power/Pow.hpp"


namespace Krys::MTL
{
  /// @brief Computes 10 raised to the power of `x`, i.e., `10^x`.
  /// @tparam TNumber An arithmetic type.
  /// @param x The input value.
  /// @returns The result of `10` raised to the power of `x`.
  template <IsArithmeticT TNumber>
  constexpr NO_DISCARD TNumber Exp10(TNumber x) noexcept
  {
    return MTL::Pow(static_cast<TNumber>(10), x);
  }
}