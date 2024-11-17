#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"

#include <cmath>

namespace Krys::MTL
{
  /// @brief Rounds `x` to the nearest integer. Halfway cases are rounded away from zero.
  /// @tparam TNumber A floating point type.
  /// @param x The input value.
  /// @return `x`, rounded to the nearest integer.
  template <IsFloatingPointT TNumber>
  constexpr NO_DISCARD TNumber Round(TNumber x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
    {
      if (x > 0)
        return static_cast<TNumber>(static_cast<long long>(x + 0.5));
      return static_cast<TNumber>(static_cast<long long>(x - 0.5));
    }

    return std::round(x);
  }

  /// @brief Computes the largest integer that isn't greater than `x`.
  /// @tparam TNumber A floating-point type.
  /// @param x The input value.
  /// @return The largest integer that isn't greater than `x`.
  template <IsFloatingPointT TNumber>
  constexpr NO_DISCARD TNumber Floor(TNumber x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
    {
      if (static_cast<long long>(x) == x)
        return x;
      return (x > 0.0) ? static_cast<long long>(x) : static_cast<long long>(x) - 1;
    }

    return std::floor(x);
  }

  /// @brief Computes the smallest integer that isn't smaller than `x`.
  /// @tparam TNumber A floating point type.
  /// @param x The input value.
  /// @return The smallest integer that isn't smaller than `x`.
  template <IsFloatingPointT TNumber>
  constexpr NO_DISCARD TNumber Ceil(TNumber x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
    {
      if (static_cast<long long>(x) == x)
        return x;
      return (x > 0.0) ? static_cast<long long>(x) + 1 : static_cast<long long>(x);
    }

    return std::ceil(x);
  }

  /// @brief Computes the nearest integer not greater in magnitude than `x`.
  /// @tparam TNumber A floating point type.
  /// @param x The input value.
  /// @return The nearest integer not greater in magnitude than `x`.
  template <IsFloatingPointT TNumber>
  constexpr NO_DISCARD TNumber Trunc(TNumber x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
      return static_cast<TNumber>(static_cast<long long>(x));

    return std::trunc(x);
  }
}