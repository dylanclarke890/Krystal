#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Common/Constants.hpp"
#include "MTL/Trigonometric/Atan.hpp"

#include <cmath>

namespace Krys::MTL
{
  /// @brief Computes arctangent of `y/x`, using signs to determine the correct quadrant.
  /// @tparam TNumber An arithmetic type.
  /// @param y The y-coordinate.
  /// @param x The x-coordinate.
  /// @returns The angle in radians between the positive x-axis and the point (x, y).
  template <IsArithmeticT TNumber>
  constexpr TNumber Atan2(TNumber y, TNumber x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
    {
      constexpr TNumber Pi = MTL::Pi<TNumber>();

      if (x > TNumber(0))
        return MTL::Atan(y / x);
      else if (x < TNumber(0) && y >= TNumber(0))
        return MTL::Atan(y / x) + Pi;
      else if (x < TNumber(0) && y < TNumber(0))
        return MTL::Atan(y / x) - Pi;
      else if (x == TNumber(0) && y > TNumber(0))
        return Pi / 2;
      else if (x == TNumber(0) && y < TNumber(0))
        return -Pi / 2;
      else
        return TNumber(0); // Undefined, return 0 or handle error
    }

    return std::atan2(y, x);
  }
}