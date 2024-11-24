#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"

#include <cmath>

namespace Krys::MTL
{
  /// @brief Computes the absolute value of `x`.
  /// @tparam TNumber An arithmetic type.
  /// @param x The input value.
  /// @returns The absolute value of `x`.
  template <IsArithmeticT TNumber>
  NO_DISCARD constexpr TNumber Abs(TNumber x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
    {
      if (IsUnsignedT<TNumber>)
        return x;

      return (x < TNumber(0)) ? -x : x;
    }
    else if constexpr (IsUnsignedT<TNumber>)
      return x;
    else
      return std::abs(x);
  }
}