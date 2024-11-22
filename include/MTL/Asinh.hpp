#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Log.hpp"
#include "MTL/Sqrt.hpp"

#include <cmath>

namespace Krys::MTL
{
  /// @brief Computes inverse hyperbolic sine of `x`.
  template <IsArithmeticT TNumber>
  constexpr TNumber Asinh(TNumber x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
      return MTL::Log(x + MTL::Sqrt(x * x + TNumber(1)));

    return std::asinh(x);
  }
}