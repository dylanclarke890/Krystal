#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Constants.hpp"
#include "MTL/Exp.hpp"

#include <cmath>

namespace Krys::MTL
{
  /// @brief Computes 2 raised to the power of `x`, i.e., `2^x`.
  /// @tparam TNumber An arithmetic type.
  /// @param x The input value.
  /// @returns The result of `2` raised to the power of `x`.
  template <IsArithmeticT TNumber>
  constexpr NO_DISCARD TNumber Exp2(TNumber x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
      return MTL::Exp(x * MTL::LnTwo<TNumber>());

    return std::exp2(x);
  }
}