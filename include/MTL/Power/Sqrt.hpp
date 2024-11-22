#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"

#include <cmath>

namespace Krys::MTL
{
  /// @brief Computes the square root of `x` using Newton's method.
  /// @tparam TNumber A floating-point type.
  /// @param x The input value (must be non-negative).
  /// @returns The square root of `x`.
  template <typename TNumber>
  constexpr TNumber Sqrt(TNumber x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
    {
      if (x < TNumber(0))
        return -1; // Indicate an error for negative inputs
      if (x == TNumber(0) || x == TNumber(1))
        return x; // Sqrt(0) = 0, Sqrt(1) = 1

      TNumber guess = x / 2;                     // Initial guess
      constexpr TNumber epsilon = TNumber(1e-6); // Precision tolerance

      while (true)
      {
        TNumber next_guess = (guess + x / guess) / 2;
        TNumber diff = next_guess - guess;
        diff = diff < 0 ? -diff : diff;
        if (diff < epsilon)
          return next_guess;
        guess = next_guess;
      }
    }

    return std::sqrt(x);
  }
}