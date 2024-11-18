#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"
#include "Core/Maths/Scalars/Constants.hpp"

#include <cmath>

namespace Krys::MTL
{
  // Recursive helper to compute the Taylor series
  template <IsArithmeticT TNumber>
  constexpr TNumber exp_impl(TNumber x, std::size_t term, TNumber current_power, TNumber current_factorial,
                             std::size_t max_terms) noexcept
  {
    // Base case: Stop recursion when the number of terms is reached
    if (term >= max_terms)
      return TNumber(0);
    // Compute the current term
    TNumber current_term = current_power / current_factorial;
    // Recursive step: Add the current term and proceed to the next
    return current_term + exp_impl(x, term + 1, current_power * x, current_factorial * (term + 1), max_terms);
  }

  /// @brief Computes the natural exponential function of `x`, i.e., `e^x`.
  /// @tparam TNumber An arithmetic type.
  /// @param x The input value.
  /// @returns The result of `e` raised to the power of `x`.
  template <IsArithmeticT TNumber>
  constexpr TNumber Exp(TNumber x) noexcept
  {
    // Use the property e^x = 1 / e^-x for negative inputs
    if (x < TNumber(0))
      return TNumber(1) / Exp(-x);

    constexpr std::size_t max_terms = 30; // Maximum number of terms

    // Taylor series expansion for e^x: T(1) + x + x^2/2! + ...
    return TNumber(1) + exp_impl(x, 1, x, TNumber(1), max_terms);
  }

  // Utility function to compute x^n
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

    return std::pow(base, exp);
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

  // /// @brief Computes 10 raised to the power of `x`, i.e., `10^x`.
  // /// @tparam TNumber An arithmetic type.
  // /// @param x The input value.
  // /// @returns The result of `10` raised to the power of `x`.
  // template <IsArithmeticT TNumber>
  // constexpr NO_DISCARD TNumber Exp10(TNumber x) noexcept
  // {
  //   return std::pow(static_cast<TNumber>(10), x);
  // }

  // /// @brief Computes the exponential integral of `x`.
  // /// @tparam TNumber A floating-point type.
  // /// @param x The input value.
  // /// @returns The exponential integral `Ei(x)`.
  // template <IsFloatingPointT TNumber>
  // constexpr NO_DISCARD TNumber ExpIntegral(TNumber x) noexcept
  // {
  //   return std::expint(x);
  // }

  // /// @brief Computes the natural logarithm of `x`, i.e., the value `y` such that `e^y = x`.
  // /// @tparam TNumber An arithmetic type.
  // /// @param x The input value (must be greater than zero).
  // /// @returns The natural logarithm of `x`.
  // template <IsArithmeticT TNumber>
  // constexpr NO_DISCARD TNumber Log(TNumber x) noexcept
  // {
  //   return std::log(x);
  // }

  // /// @brief Computes the base-2 logarithm of `x`, i.e., the value `y` such that `2^y = x`.
  // /// @tparam TNumber An arithmetic type.
  // /// @param x The input value (must be greater than zero).
  // /// @returns The base-2 logarithm of `x`.
  // template <IsArithmeticT TNumber>
  // constexpr NO_DISCARD TNumber Log2(TNumber x) noexcept
  // {
  //   return std::log2(x);
  // }

  // /// @brief Computes the square root of `x`.
  // /// @tparam TNumber An arithmetic type.
  // /// @param x The input value (must be non-negative).
  // /// @returns The square root of `x`.
  // template <IsArithmeticT TNumber>
  // constexpr NO_DISCARD TNumber Sqrt(TNumber x) noexcept
  // {
  //   return std::sqrt(x);
  // }

  // /// @brief Computes the inverse square root of `x`, i.e., `1 / sqrt(x)`.
  // /// @tparam TNumber An arithmetic type.
  // /// @param x The input value (must be greater than zero).
  // /// @returns The inverse square root of `x`.
  // template <IsArithmeticT TNumber>
  // constexpr NO_DISCARD TNumber InverseSqrt(TNumber x) noexcept
  // {
  //   return static_cast<T>(1) / MTL::Sqrt(x);
  // }

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
}