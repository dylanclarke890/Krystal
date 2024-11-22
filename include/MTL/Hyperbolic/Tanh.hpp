#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Hyperbolic/Cosh.hpp"
#include "MTL/Hyperbolic/Sinh.hpp"

#include <cmath>

namespace Krys::MTL
{
  /// @brief Computes the hyperbolic tangent of `x`.
  /// @tparam TNumber An arithmetic type.
  /// @param x The input value.
  /// @returns The hyperbolic tangent of `x`.
  template <IsArithmeticT TNumber>
  constexpr TNumber Tanh(TNumber x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
    {
      TNumber cosh_x = MTL::Cosh(x);
      if (cosh_x == TNumber(0))
        return std::numeric_limits<TNumber>::infinity();
      return MTL::Sinh(x) / cosh_x;
    }

    return std::tanh(x);
  }
}