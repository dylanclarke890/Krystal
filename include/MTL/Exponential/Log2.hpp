#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Common/Constants.hpp"
#include "MTL/Exponential/Log.hpp"

#include <cmath>

namespace Krys::MTL
{
  /// @brief Computes the base-2 logarithm of `x` (`2^y = x`).
  /// @tparam TNumber An arithmetic type.
  /// @param x The input value (must be greater than zero).
  /// @returns The base-2 logarithm of `x`.
  template <IsArithmeticT TNumber>
  NO_DISCARD constexpr TNumber Log2(TNumber x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
    {
      if (x <= TNumber(0))
        return -std::numeric_limits<TNumber>::infinity(); // Log2 undefined for x <= 0
      else if (x == TNumber(1))
        return TNumber(0); // log2(1) = 0
      else
        return MTL::Log(x) / MTL::LnTwo<TNumber>();
    }
    else
      return std::log2(x);
  }
}