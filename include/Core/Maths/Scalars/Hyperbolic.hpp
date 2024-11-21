#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"
#include "Core/Maths/Scalars/Exponential.hpp"

#include <cmath>

namespace Krys::Impl
{
  // Helper function for computing sinh using Taylor series expansion
  template <IsArithmeticT TNumber>
  constexpr TNumber _compute_sinh(TNumber x, size_t n, TNumber current_power, TNumber current_factorial,
                                  size_t max_terms) noexcept
  {
    if (n >= max_terms)
      return TNumber(0);
    TNumber current_term = current_power / current_factorial;
    return current_term
           + _compute_sinh(x, n + 1, current_power * x * x, current_factorial * (2 * n + 2) * (2 * n + 3),
                           max_terms);
  }

  // Helper function for computing cosh using Taylor series expansion
  template <IsArithmeticT TNumber>
  constexpr TNumber _compute_cosh(TNumber x, size_t n, TNumber current_power, TNumber current_factorial,
                                  size_t max_terms) noexcept
  {
    if (n >= max_terms)
      return TNumber(0);
    TNumber current_term = current_power / current_factorial;
    return current_term
           + _compute_cosh(x, n + 1, current_power * x * x, current_factorial * (2 * n + 1) * (2 * n + 2),
                           max_terms);
  }

  // Helper function for computing tanh using Taylor series
  template <IsArithmeticT TNumber>
  constexpr TNumber _compute_tanh(TNumber x, size_t n, TNumber current_power, TNumber x_squared,
                                  size_t max_terms) noexcept
  {
    if (n >= max_terms)
      return TNumber(0);
    TNumber current_term = (n % 2 == 0 ? 1 : -1) * current_power / (2 * n + 1);
    return current_term + _compute_tanh(x, n + 1, current_power * x_squared, x_squared, max_terms);
  }
}

namespace Krys::MTL
{
  /// @brief Computes hyperbolic sine of `x` using Taylor series expansion.
  template <IsArithmeticT TNumber>
  constexpr TNumber Sinh(TNumber x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
    {
      constexpr size_t max_terms = 11; // Adjust for desired accuracy
      return Impl::_compute_sinh(x, 0, x, TNumber(1), max_terms);
    }

    return std::sinh(x);
  }

  /// @brief Computes hyperbolic cosine of `x` using Taylor series expansion.
  template <IsArithmeticT TNumber>
  constexpr TNumber Cosh(TNumber x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
    {
      constexpr size_t max_terms = 11; // Adjust for desired accuracy
      return Impl::_compute_cosh(x, 0, TNumber(1), TNumber(1), max_terms);
    }

    return std::cosh(x);
  }

  /// @brief Computes hyperbolic tangent of `x` using Sinh(x) / Cosh(x).
  template <IsArithmeticT TNumber>
  constexpr TNumber Tanh(TNumber x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
    {
      TNumber cosh_x = Cosh(x);
      if (cosh_x == TNumber(0))
        return std::numeric_limits<TNumber>::infinity();
      return Sinh(x) / cosh_x;
    }

    return std::tanh(x);
  }

  /// @brief Computes inverse hyperbolic sine of `x` using the logarithmic definition.
  template <IsArithmeticT TNumber>
  constexpr TNumber Asinh(TNumber x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
    {
      return MTL::Log(x + MTL::Sqrt(x * x + TNumber(1)));
    }

    return std::asinh(x);
  }

  /// @brief Computes inverse hyperbolic tangent of `x` using series expansion.
  template <IsArithmeticT TNumber>
  constexpr TNumber Atanh(TNumber x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
    {
      if (x <= TNumber(-1) || x >= TNumber(1))
        return std::numeric_limits<TNumber>::quiet_NaN(); // Undefined for |x| >= 1

      return TNumber(0.5) * MTL::Log((TNumber(1) + x) / (TNumber(1) - x));
    }

    return std::atanh(x);
  }

  /// @brief Computes inverse hyperbolic cosine of `x` using the identity acosh(x) = log(x + sqrt(x^2 - 1)).
  template <IsArithmeticT TNumber>
  constexpr TNumber Acosh(TNumber x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
    {
      if (x < TNumber(1))
        return std::numeric_limits<TNumber>::quiet_NaN(); // Undefined for x < 1

      return Log(x + Sqrt(x * x - TNumber(1)));
    }

    return std::acosh(x);
  }
}