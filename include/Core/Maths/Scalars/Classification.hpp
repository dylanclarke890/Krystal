#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"

#include <cmath>

namespace Krys::MTL
{
  /// @brief Checks if the given floating-point number is NaN (Not a Number).
  /// @tparam TFloat A floating-point type.
  /// @param x The input value.
  /// @return `true` if `x` is NaN, otherwise `false`.
  template <IsFloatingPointT TFloat>
  constexpr NO_DISCARD bool IsNaN(TFloat x) noexcept
  {
    return std::isnan(x);
  }

  /// @brief Checks if the given floating-point number is finite.
  /// @tparam TFloat A floating-point type.
  /// @param x The input value.
  /// @return `true` if `x` is finite (not NaN or infinite), otherwise `false`.
  template <IsFloatingPointT TFloat>
  constexpr NO_DISCARD bool IsFinite(TFloat x) noexcept
  {
    return std::isfinite(x);
  }

  /// @brief Checks if the given floating-point number is infinite.
  /// @tparam TFloat A floating-point type.
  /// @param x The input value.
  /// @return `true` if `x` is infinite, otherwise `false`.
  template <IsFloatingPointT TFloat>
  constexpr NO_DISCARD bool IsInf(TFloat x) noexcept
  {
    return std::isinf(x);
  }

  /// @brief Checks if the given floating-point number is normal (neither zero, subnormal, infinite, nor NaN).
  /// @tparam TFloat A floating-point type.
  /// @param x The input value.
  /// @return `true` if `x` is a normal floating-point number, otherwise `false`.
  template <IsFloatingPointT TFloat>
  constexpr NO_DISCARD bool IsNormal(TFloat x) noexcept
  {
    return std::isnormal(x);
  }

  /// @brief Checks if the given floating-point number is denormalized (too small to be represented as a
  /// normalized number).
  /// @tparam TFloat A floating-point type.
  /// @param x The input value.
  /// @return `true` if `x` is denormalized, otherwise `false`.
  template <IsFloatingPointT TFloat>
  constexpr NO_DISCARD bool IsDenormal(TFloat x) noexcept
  {
    return std::fpclassify(x) == FP_SUBNORMAL;
  }

  /// @brief Checks if the given number is even.
  /// @tparam TNumber An arithmetic type.
  /// @param x The input value.
  /// @return `true` if `x` is even, otherwise `false`.
  /// @note For floating-point types, this function is undefined and should not be used.
  template <IsArithmeticT TNumber>
  constexpr NO_DISCARD bool IsEven(TNumber x) noexcept
  {
    return x % 2 == 0;
  }

  /// @brief Checks if the given number is odd.
  /// @tparam TNumber An arithmetic type.
  /// @param x The input value.
  /// @return `true` if `x` is odd, otherwise `false`.
  /// @note For floating-point types, this function is undefined and should not be used.
  template <IsArithmeticT TNumber>
  constexpr NO_DISCARD bool IsOdd(TNumber x) noexcept
  {
    return x % 2 != 0;
  }

  /// @brief Checks if the given number is positive.
  /// @tparam TNumber An arithmetic type.
  /// @param x The input value.
  /// @return `true` if `x` is positive, otherwise `false`.
  template <IsArithmeticT TNumber>
  constexpr NO_DISCARD bool IsPositive(TNumber x) noexcept
  {
    return x > 0;
  }

  /// @brief Checks if the given number is negative.
  /// @tparam TNumber An arithmetic type.
  /// @param x The input value.
  /// @return `true` if `x` is negative, otherwise `false`.
  template <IsArithmeticT TNumber>
  constexpr NO_DISCARD bool IsNegative(TNumber x) noexcept
  {
    return x < 0;
  }
}
