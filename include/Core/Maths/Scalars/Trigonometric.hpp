#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"
#include "Core/Maths/Scalars/Exponential.hpp"

#include <cmath>

namespace Krys::Impl
{
  // Helper function for computing the sine using Taylor series expansion
  template <IsArithmeticT TNumber>
  constexpr TNumber _compute_sin(TNumber x, size_t n, TNumber current_power, TNumber current_factorial,
                                 size_t max_terms) noexcept
  {
    if (n >= max_terms)
      return TNumber(0);
    int sign = (n % 2 == 0) ? 1 : -1;
    TNumber current_term = sign * current_power / current_factorial;
    return current_term
           + _compute_sin(x, n + 1, current_power * x * x, current_factorial * (2 * n + 2) * (2 * n + 3),
                          max_terms);
  }

  // Helper function for computing the cosine using Taylor series expansion
  template <IsArithmeticT TNumber>
  constexpr TNumber _compute_cos(TNumber x, size_t n, TNumber current_power, TNumber current_factorial,
                                 size_t max_terms) noexcept
  {
    if (n >= max_terms)
      return TNumber(0);
    int sign = (n % 2 == 0) ? 1 : -1;
    TNumber current_term = sign * current_power / current_factorial;
    return current_term
           + _compute_cos(x, n + 1, current_power * x * x, current_factorial * (2 * n + 1) * (2 * n + 2),
                          max_terms);
  }

  // Helper function for computing the arctangent using Taylor series expansion
  template <IsArithmeticT TNumber>
  constexpr TNumber _compute_atan(TNumber x, size_t n, TNumber current_power, size_t max_terms) noexcept
  {
    if (n >= max_terms)
      return TNumber(0);
    int sign = (n % 2 == 0) ? 1 : -1;
    TNumber current_term = sign * current_power / TNumber(2 * n + 1);
    return current_term + _compute_atan(x, n + 1, current_power * x * x, max_terms);
  }

  // Helper function for computing the arcsine using Taylor series expansion
  template <IsArithmeticT TNumber>
  constexpr TNumber _compute_asin(TNumber x, size_t n, TNumber current_power, TNumber current_factorial,
                                  size_t max_terms) noexcept
  {
    if (n >= max_terms)
      return TNumber(0);

    TNumber numerator = MTL::Factorial(2 * n) * current_power;
    TNumber denominator =
      MTL::Pow(TNumber(4), static_cast<int>(n)) * MTL::Pow(MTL::Factorial(n), 2) * (2 * n + 1);
    TNumber current_term = numerator / denominator;
    return current_term + _compute_asin(x, n + 1, current_power * x * x, current_factorial, max_terms);
  }
}

namespace Krys::MTL
{
  /// @brief Converts `degrees` to radians.
  /// @tparam TNumber An arithmetic type (floating point types are advised).
  /// @param degrees The input value.
  /// @returns The converted value.
  template <IsArithmeticT TNumber>
  constexpr NO_DISCARD TNumber Radians(TNumber degrees) noexcept
  {
    return degrees * static_cast<TNumber>(0.01745329251994329576923690768489);
  }

  /// @brief Converts `radians` to degrees.
  /// @tparam TNumber An arithmetic type (floating point types are advised).
  /// @param radians The input value.
  /// @returns The converted value.
  template <IsArithmeticT TNumber>
  constexpr NO_DISCARD TNumber Degrees(TNumber radians) noexcept
  {
    return radians * static_cast<TNumber>(57.295779513082320876798154814105);
  }

  /// @brief Computes sine of `x` using Taylor series expansion.
  /// @tparam TNumber An arithmetic type.
  /// @param x The input value in radians.
  /// @returns The sine of `x`.
  template <IsArithmeticT TNumber>
  constexpr TNumber Sin(TNumber x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
    {
      constexpr size_t max_terms = 11; // Adjust for desired accuracy
      return Impl::_compute_sin(x, 0, x, TNumber(1), max_terms);
    }

    return std::sin(x);
  }

  /// @brief Computes cosine of `x` using Taylor series expansion.
  /// @tparam TNumber An arithmetic type.
  /// @param x The input value in radians.
  /// @returns The cosine of `x`.
  template <IsArithmeticT TNumber>
  constexpr TNumber Cos(TNumber x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
    {
      constexpr size_t max_terms = 11; // Adjust for desired accuracy
      return Impl::_compute_cos(x, 0, TNumber(1), TNumber(1), max_terms);
    }

    return std::cos(x);
  }

  /// @brief Computes tangent of `x` as Sin(x) / Cos(x).
  /// @tparam TNumber An arithmetic type.
  /// @param x The input value in radians.
  /// @returns The tangent of `x`.
  template <IsArithmeticT TNumber>
  constexpr TNumber Tan(TNumber x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
    {
      TNumber cos_x = Cos(x);
      if (cos_x == TNumber(0))
        return std::numeric_limits<TNumber>::infinity();
      return Sin(x) / cos_x;
    }

    return std::tan(x);
  }

  /// @brief Computes arctangent of `x` using series expansion.
  /// @tparam TNumber An arithmetic type.
  /// @param x The input value.
  /// @returns The arctangent of `x` in radians.
  template <IsArithmeticT TNumber>
  constexpr TNumber Atan(TNumber x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
    {
      constexpr size_t max_terms = 15; // Adjust for desired accuracy
      constexpr TNumber PI = MTL::Pi<TNumber>();

      if (x == TNumber(1))
        return Pi<TNumber>() / TNumber(4);
      if (x == TNumber(-1))
        return -Pi<TNumber>() / TNumber(4);

      if (x < TNumber(-1))
        return -PI / TNumber(2) - Impl::_compute_atan(TNumber(1) / x, 0, TNumber(1) / x, max_terms);
      else if (x > TNumber(1))
        return PI / TNumber(2) - Impl::_compute_atan(TNumber(1) / x, 0, TNumber(1) / x, max_terms);
      else
        return Impl::_compute_atan(x, 0, x, max_terms);
    }

    return std::atan(x);
  }

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
        return Atan(y / x);
      else if (x < TNumber(0) && y >= TNumber(0))
        return Atan(y / x) + Pi;
      else if (x < TNumber(0) && y < TNumber(0))
        return Atan(y / x) - Pi;
      else if (x == TNumber(0) && y > TNumber(0))
        return Pi / 2;
      else if (x == TNumber(0) && y < TNumber(0))
        return -Pi / 2;
      else
        return TNumber(0); // Undefined, return 0 or handle error
    }

    return std::atan2(y, x);
  }

  /// @brief Computes arcsine of `x` using series expansion.
  /// @tparam TNumber An arithmetic type.
  /// @param x The input value (must be in [-1, 1]).
  /// @returns The arcsine of `x` in radians.
  template <IsArithmeticT TNumber>
  constexpr TNumber Asin(TNumber x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
    {
      if (x < TNumber(-1) || x > TNumber(1))
        return std::numeric_limits<TNumber>::quiet_NaN(); // Undefined for |x| > 1

      if (x == TNumber(1))
        return Pi<TNumber>() / TNumber(2);
      if (x == TNumber(-1))
        return -Pi<TNumber>() / TNumber(2);

      constexpr size_t max_terms = 10; // Adjust for desired accuracy
      return Impl::_compute_asin(x, 0, x, TNumber(1), max_terms);
    }

    return std::asin(x);
  }

  /// @brief Computes arccosine of `x` using the identity acos(x) = π/2 - asin(x).
  /// @tparam TNumber An arithmetic type.
  /// @param x The input value (must be in [-1, 1]).
  /// @returns The arccosine of `x` in radians.
  template <IsArithmeticT TNumber>
  constexpr TNumber Acos(TNumber x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
    {
      if (x < TNumber(-1) || x > TNumber(1))
        return std::numeric_limits<TNumber>::quiet_NaN(); // Undefined for |x| > 1

      return MTL::Pi<TNumber>() / 2 - Asin(x);
    }

    return std::acos(x);
  }
}