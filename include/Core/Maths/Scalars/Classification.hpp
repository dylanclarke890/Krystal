#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"
#include "Core/Maths/Scalars/Arithmetic.hpp"

#include <bit>
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
    KRYS_IF_COMPILE_CONTEXT
      return x != x;

    return std::isnan(x);
  }

  /// @brief Checks if the given floating-point number is infinite.
  /// @tparam TFloat A floating-point type.
  /// @param x The input value.
  /// @return `true` if `x` is infinite, otherwise `false`.
  template <IsFloatingPointT TFloat>
  constexpr NO_DISCARD bool IsInf(TFloat x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
      return x == ((x < 0 ? -1 : 1) * std::numeric_limits<TFloat>::infinity());

    return std::isinf(x);
  }

  /// @brief Checks if the given floating-point number is finite.
  /// @tparam TFloat A floating-point type.
  /// @param x The input value.
  /// @return `true` if `x` is finite (not NaN or infinite), otherwise `false`.
  template <IsFloatingPointT TFloat>
  constexpr NO_DISCARD bool IsFinite(TFloat x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
      return !MTL::IsNaN(x) && !MTL::IsInf(x);

    return std::isfinite(x);
  }

  /// @brief Checks if the given floating-point number is denormalized (too small to be represented as a
  /// normalized number).
  /// @tparam TFloat A floating-point type.
  /// @param x The input value.
  /// @return `true` if `x` is denormalized, otherwise `false`.
  template <IsFloatingPointT TFloat>
  constexpr NO_DISCARD bool IsDenormal(TFloat x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
    {
      if (MTL::IsNaN(x))
        return false;
      return MTL::Abs(x) < std::numeric_limits<TFloat>::min() && MTL::Abs(x) > 0;
    }

    return std::fpclassify(x) == FP_SUBNORMAL;
  }

  /// @brief Checks if the given floating-point number is normal (neither zero, subnormal, infinite, nor NaN).
  /// @tparam TFloat A floating-point type.
  /// @param x The input value.
  /// @return `true` if `x` is a normal floating-point number, otherwise `false`.
  template <IsFloatingPointT TFloat>
  constexpr NO_DISCARD bool IsNormal(TFloat x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
      return MTL::IsFinite(x) && !MTL::IsDenormal(x) && x != static_cast<TFloat>(0);

    return std::isnormal(x);
  }

  /// @brief Determines if the given number is negative.
  /// @tparam TNumber A signed type (floating-point or integral).
  /// @param x The input value.
  /// @return `true` if `x` is negative.
  template <IsSignedT TNumber>
  constexpr NO_DISCARD bool Signbit(TNumber x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
    {
      constexpr TNumber ZERO = 0;
      if (IsIntegralT<TNumber>)
        return (x < ZERO);

      if (x == ZERO || MTL::IsNaN(x))
      {
        // Cast to it's bit representation.
        using as_uint_t = std::conditional_t<std::is_same_v<TNumber, float>, uint32, uint64>;
        as_uint_t bits = std::bit_cast<as_uint_t>(x);
        // Check MSB (sign bit).
        return (bits & (as_uint_t(1) << (sizeof(as_uint_t) * 8 - 1))) != as_uint_t(0);
      }

      return (x < ZERO);
    }

    return std::signbit(x);
  }

  /// @brief Checks if the given number is even.
  /// @tparam TNumber An arithmetic type.
  /// @param x The input value.
  /// @return `true` if `x` is even, otherwise `false`.
  /// @note For floating-point types, this function is undefined and should not be used.
  template <IsIntegralT TNumber>
  constexpr NO_DISCARD bool IsEven(TNumber x) noexcept
  {
    return x % 2 == 0;
  }

  /// @brief Checks if the given number is odd.
  /// @tparam TNumber An arithmetic type.
  /// @param x The input value.
  /// @return `true` if `x` is odd, otherwise `false`.
  /// @note For floating-point types, this function is undefined and should not be used.
  template <IsIntegralT TNumber>
  constexpr NO_DISCARD bool IsOdd(TNumber x) noexcept
  {
    return x % 2 != 0;
  }
}
