#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"

#include <cmath>

namespace Krys::MTL
{
  /// @brief Raises `base` to the power of `exponent`.
  /// @tparam TNumber An arithmetic type.
  /// @param base The base value.
  /// @param exponent The exponent to raise the base to.
  /// @returns The result of `base` raised to the power of `exponent`.
  template <IsArithmeticT TNumber>
  constexpr NO_DISCARD TNumber Pow(TNumber base, TNumber exponent) noexcept
  {
    return std::pow(base, exponent);
  }

  /// @brief Computes the natural exponential function of `x`, i.e., `e^x`.
  /// @tparam TNumber An arithmetic type.
  /// @param x The input value.
  /// @returns The result of `e` raised to the power of `x`.
  template <IsArithmeticT TNumber>
  constexpr NO_DISCARD TNumber Exp(TNumber x) noexcept
  {
    return std::exp(x);
  }

  /// @brief Computes 2 raised to the power of `x`, i.e., `2^x`.
  /// @tparam TNumber An arithmetic type.
  /// @param x The input value.
  /// @returns The result of `2` raised to the power of `x`.
  template <IsArithmeticT TNumber>
  constexpr NO_DISCARD TNumber Exp2(TNumber x) noexcept
  {
    return std::exp2(x);
  }

  /// @brief Computes 10 raised to the power of `x`, i.e., `10^x`.
  /// @tparam TNumber An arithmetic type.
  /// @param x The input value.
  /// @returns The result of `10` raised to the power of `x`.
  template <IsArithmeticT TNumber>
  constexpr NO_DISCARD TNumber Exp10(TNumber x) noexcept
  {
    return std::pow(static_cast<TNumber>(10), x);
  }

  /// @brief Computes the exponential integral of `x`.
  /// @tparam TNumber A floating-point type.
  /// @param x The input value.
  /// @returns The exponential integral `Ei(x)`.
  template <IsFloatingPointT TNumber>
  constexpr NO_DISCARD TNumber ExpIntegral(TNumber x) noexcept
  {
    return std::expint(x);
  }

  /// @brief Computes the natural logarithm of `x`, i.e., the value `y` such that `e^y = x`.
  /// @tparam TNumber An arithmetic type.
  /// @param x The input value (must be greater than zero).
  /// @returns The natural logarithm of `x`.
  template <IsArithmeticT TNumber>
  constexpr NO_DISCARD TNumber Log(TNumber x) noexcept
  {
    return std::log(x);
  }

  /// @brief Computes the base-2 logarithm of `x`, i.e., the value `y` such that `2^y = x`.
  /// @tparam TNumber An arithmetic type.
  /// @param x The input value (must be greater than zero).
  /// @returns The base-2 logarithm of `x`.
  template <IsArithmeticT TNumber>
  constexpr NO_DISCARD TNumber Log2(TNumber x) noexcept
  {
    return std::log2(x);
  }

  /// @brief Computes the square root of `x`.
  /// @tparam TNumber An arithmetic type.
  /// @param x The input value (must be non-negative).
  /// @returns The square root of `x`.
  template <IsArithmeticT TNumber>
  constexpr NO_DISCARD TNumber Sqrt(TNumber x) noexcept
  {
    return std::sqrt(x);
  }

  /// @brief Computes the inverse square root of `x`, i.e., `1 / sqrt(x)`.
  /// @tparam TNumber An arithmetic type.
  /// @param x The input value (must be greater than zero).
  /// @returns The inverse square root of `x`.
  template <IsArithmeticT TNumber>
  constexpr NO_DISCARD TNumber InverseSqrt(TNumber x) noexcept
  {
    return static_cast<T>(1) / MTL::Sqrt(x);
  }

  /// @brief Computes the factorial of `n`.
  /// @tparam TNumber An unsigned integer type.
  /// @param n The input value.
  /// @returns The factorial of `n`, i.e., `n! = n * (n-1) * ... * 1`. For `n = 0`, returns `1`.
  template <IsUnsignedT TNumber>
  constexpr NO_DISCARD TNumber Factorial(TNumber n) noexcept
  {
    TNumber result = 1;
    for (TNumber i = 1; i <= n; i++)
      result *= i;
    return result;
  }
}