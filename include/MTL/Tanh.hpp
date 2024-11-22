#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"
#include "MTL/Cosh.hpp"
#include "MTL/Sinh.hpp"

#include <cmath>

namespace Krys::MTL
{
  /// @brief Computes hyperbolic tangent of `x`.
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