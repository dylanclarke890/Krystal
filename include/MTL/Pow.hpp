#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"
#include "MTL/Constants.hpp"

#include <cmath>

namespace Krys::MTL
{
  // TODO: floating point numbers

  /// @brief Computes `x^n`.
  /// @tparam TNumber An arithmetic type.
  /// @param x The input value.
  /// @returns `x^n`.
  template <IsArithmeticT TNumber>
  constexpr TNumber Pow(TNumber base, int exp) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
    {
      if (exp < 0)
        return TNumber(1) / Pow(base, -exp);
      if (exp == 0)
        return 1;

      TNumber result = TNumber(1);
      while (exp > 0)
      {
        result *= base;
        --exp;
      }
      return result;
    }

    return static_cast<TNumber>(std::pow(base, exp));
  }
}