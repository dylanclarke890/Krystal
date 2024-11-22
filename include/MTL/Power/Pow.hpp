#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"
#include "MTL/Exponential/Exp.hpp"
#include "MTL/Exponential/Log.hpp"

#include <cmath>

namespace Krys::MTL
{
  /// @brief Computes `x^n` for integer exponents.
  /// @tparam TBase The base type.
  /// @tparam TExp The exponent type (must be an integer).
  /// @param base The base value.
  /// @param exp The exponent value.
  /// @returns `base^exp`.
  template <IsArithmeticT TBase, IsIntegralT TExp>
  constexpr TBase Pow(TBase base, TExp exp) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
    {
      if (exp < 0)
        return TBase(1) / Pow(base, -exp);
      if (exp == 0)
        return TBase(1);

      TBase result = TBase(1);
      while (exp > 0)
      {
        result *= base;
        --exp;
      }
      return result;
    }

    return static_cast<TBase>(std::pow(base, exp));
  }

  /// @brief Computes `x^n` for floating-point exponents.
  /// @tparam TBase A floating-point type.
  /// @param base The base value.
  /// @param exp The exponent value.
  /// @returns `base^exp`.
  template <IsFloatingPointT TBase>
  constexpr TBase Pow(TBase base, TBase exp) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
    {
      if (base == TBase(0))
        return TBase(0); // 0^n = 0 for n > 0
      if (exp == TBase(0))
        return TBase(1); // x^0 = 1

      // Use e^(exp * log(base)) for floating-point exponents
      return MTL::Exp(exp * MTL::Log(base));
    }

    return std::pow(base, exp);
  }
}
