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
      TNumber coshX = MTL::Cosh(x);
      if (coshX == TNumber(0))
        return std::numeric_limits<TNumber>::infinity();
      else
        return MTL::Sinh(x) / coshX;
    }
    else
      return std::tanh(x);
  }
}