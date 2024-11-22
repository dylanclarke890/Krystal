#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Exponential/Log.hpp"
#include "MTL/Power/Sqrt.hpp"

#include <cmath>

namespace Krys::MTL
{
  /// @brief Computes the inverse hyperbolic sine of `x`.
  /// @tparam TNumber An arithmetic type.
  /// @param x The input value.
  /// @returns The inverse hyperbolic sine of `x`.
  template <IsArithmeticT TNumber>
  constexpr TNumber Asinh(TNumber x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
      return MTL::Log(x + MTL::Sqrt(x * x + TNumber(1)));

    return std::asinh(x);
  }
}