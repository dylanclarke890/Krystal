#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"
#include "Core/Maths/Scalars/Constants.hpp"

#include <cmath>

namespace Krys::MTL
{
  // Recursive helper to compute the Taylor series
  // TODO: move this inside `Exp` to avoid polluting this namespace
  template <IsArithmeticT TNumber>
  constexpr TNumber _compute_exp(TNumber x, size_t term, TNumber current_power, TNumber current_factorial,
                                 size_t max_terms) noexcept
  {
    // Base case: Stop recursion when the number of terms is reached
    if (term >= max_terms)
      return TNumber(0);
    // Compute the current term
    TNumber current_term = current_power / current_factorial;
    // Recursive step: Add the current term and proceed to the next
    return current_term
           + _compute_exp(x, term + 1, current_power * x, current_factorial * (term + 1), max_terms);
  }

  /// @brief Computes the natural exponential function of `x`, i.e., `e^x`.
  /// @tparam TNumber An arithmetic type.
  /// @param x The input value.
  /// @returns The result of `e` raised to the power of `x`.
  template <IsArithmeticT TNumber>
  constexpr TNumber Exp(TNumber x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
    {
      // Use the property e^x = 1 / e^-x for negative inputs
      if (x < TNumber(0))
        return TNumber(1) / Exp(-x);

      constexpr size_t max_terms = 30;
      // Taylor series expansion for e^x: T(1) + x + x^2/2! + ...
      return TNumber(1) + _compute_exp(x, 1, x, TNumber(1), max_terms);
    }

    return std::exp(x);
  }

  /// @brief Computes the factorial of `n`.
  /// @tparam TNumber An unsigned integer type.
  /// @param n The input value.
  /// @returns The factorial of `n`, i.e., `n! = n * (n-1) * ... * 1`. For `n = 0`, returns `1`.
  template <IsArithmeticT TNumber>
  constexpr TNumber Factorial(TNumber n) noexcept
  {
    TNumber result = TNumber(1);
    for (TNumber i = 1; i <= n; i++)
      result *= i;
    return result;
  }

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

  /// @brief Computes 2 raised to the power of `x`, i.e., `2^x`.
  /// @tparam TNumber An arithmetic type.
  /// @param x The input value.
  /// @returns The result of `2` raised to the power of `x`.
  template <IsArithmeticT TNumber>
  constexpr NO_DISCARD TNumber Exp2(TNumber x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
      return MTL::Exp(x * MTL::LnTwo<TNumber>());

    return std::exp2(x);
  }

  /// @brief Computes 10 raised to the power of `x`, i.e., `10^x`.
  /// @tparam TNumber An arithmetic type.
  /// @param x The input value.
  /// @returns The result of `10` raised to the power of `x`.
  template <IsArithmeticT TNumber>
  constexpr NO_DISCARD TNumber Exp10(TNumber x) noexcept
  {
    return MTL::Pow(static_cast<TNumber>(10), x);
  }

  /// @brief Computes the natural logarithm of `x`, i.e., ln(x).
  /// @tparam TNumber An arithmetic type.
  /// @param x The input value.
  /// @returns The result of ln(x).
  template <typename TNumber>
  constexpr TNumber Log(TNumber x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
    {
      if (x <= TNumber(0)) // Log undefined for x <= 0
        return -std::numeric_limits<TNumber>::infinity();
      if (x == TNumber(1)) // ln(1) = 0
        return TNumber(0);

      // Range reduction: x = r * 2^k, where 1 <= r < 2
      int k = 0;
      while (x >= TNumber(2))
      {
        x /= TNumber(2);
        ++k;
      }
      while (x < TNumber(1))
      {
        x *= TNumber(2);
        --k;
      }

      // Reduced input r = x (now 1 <= x < 2)
      TNumber r = x - TNumber(1); // Use ln(1 + y) = y - y^2/2 + y^3/3 - ...

      // Compute ln(r) using a series expansion
      TNumber result = TNumber(0);
      TNumber term = r; // First term: y
      for (size_t n = 1; n <= 40; ++n)
      {                                                     // Use 40 terms for higher accuracy
        result += (n % 2 == 1 ? term : -term) / TNumber(n); // Alternating series
        term *= r;                                          // Compute y^n
      }

      // Combine results: ln(x) = k * ln(2) + ln(r)
      return TNumber(k) * MTL::LnTwo<TNumber>() + result;
    }

    return std::log(x);
  }

  /// @brief Computes the base-2 logarithm of `x`, i.e., the value `y` such that `2^y = x`.
  /// @tparam TNumber An arithmetic type.
  /// @param x The input value (must be greater than zero).
  /// @returns The base-2 logarithm of `x`.
  template <IsArithmeticT TNumber>
  constexpr NO_DISCARD TNumber Log2(TNumber x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
    {
      if (x <= TNumber(0))
        return -std::numeric_limits<TNumber>::infinity(); // Log2 undefined for x <= 0
      if (x == TNumber(1))
        return TNumber(0); // log2(1) = 0
      return MTL::Log(x) / MTL::LnTwo<TNumber>();
    }

    return std::log2(x);
  }

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

  /// @brief Computes the inverse square root of `x`, i.e., `1 / sqrt(x)`.
  /// @tparam TNumber An arithmetic type.
  /// @param x The input value (must be greater than zero).
  /// @returns The inverse square root of `x`.
  template <IsArithmeticT TNumber>
  constexpr NO_DISCARD TNumber InverseSqrt(TNumber x) noexcept
  {
    // TODO: revisit this for speed.
    if (x <= TNumber(0))
      return -1; // Indicate an error for non-positive inputs

    return TNumber(1) / Sqrt(x);
  }
}