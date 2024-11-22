#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"

#include <cmath>

namespace Krys::MTL
{
  /// @brief Computes the square root of `x`.
  /// @tparam TFloat A floating-point type.
  /// @param x The input value (must be non-negative).
  /// @returns The square root of `x`.
  template <IsFloatingPointT TFloat>
  constexpr TFloat Sqrt(TFloat x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
    {
      if (x < TFloat(0))
        return -1; // Indicate an error for negative inputs
      if (x == TFloat(0) || x == TFloat(1))
        return x; // Sqrt(0) = 0, Sqrt(1) = 1

      TFloat guess = x / 2;                    // Initial guess
      constexpr TFloat epsilon = TFloat(1e-6); // Precision tolerance

      while (true)
      {
        TFloat next_guess = (guess + x / guess) / 2;
        TFloat diff = next_guess - guess;
        diff = diff < 0 ? -diff : diff;
        if (diff < epsilon)
          return next_guess;
        guess = next_guess;
      }
    }

    return std::sqrt(x);
  }
}