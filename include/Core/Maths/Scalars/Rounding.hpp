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
    return std::round(x);
  }

  /// @brief Computes the largest integer that isn't greater than `x`.
  /// @tparam TNumber A floating point type.
  /// @param x The input value.
  /// @return The largest integer that isn't greater than `x`.
  template <IsFloatingPointT TNumber>
  constexpr NO_DISCARD TNumber Floor(TNumber x) noexcept
  {
    return std::floor(x);
  }

  /// @brief Computes the smallest integer that isn't smaller than `x`.
  /// @tparam TNumber A floating point type.
  /// @param x The input value.
  /// @return The smallest integer that isn't smaller than `x`.
  template <IsFloatingPointT TNumber>
  constexpr NO_DISCARD TNumber Ceil(TNumber x) noexcept
  {
    return std::ceil(x);
  }

  /// @brief Computes the nearest integer not greater in magnitude than `x`.
  /// @tparam TNumber A floating point type.
  /// @param x The input value.
  /// @return The nearest integer not greater in magnitude than `x`.
  template <IsFloatingPointT TNumber>
  constexpr NO_DISCARD TNumber Trunc(TNumber x) noexcept
  {
    return std::trunc(x);
  }
}