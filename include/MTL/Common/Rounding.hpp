#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"

#include <cmath>

namespace Krys::MTL
{
  /// @brief Computes the smallest integer that is larger than `x`.
  /// @tparam TFloat A floating point type.
  /// @param x The input value.
  /// @return The smallest integer that is larger than `x`.
  template <IsFloatingPointT TFloat>
  NO_DISCARD constexpr TFloat Ceil(TFloat x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
    {
      if (static_cast<long long>(x) == x)
        return x;

      return static_cast<long long>(x) + ((x < TFloat(0)) ? 0LL : 1LL);
    }
    else
      return std::ceil(x);
  }

  /// @brief Computes the largest integer that is smaller than `x`.
  /// @tparam TFloat A floating-point type.
  /// @param x The input value.
  /// @return The largest integer that is smaller than `x`.
  template <IsFloatingPointT TFloat>
  NO_DISCARD constexpr TFloat Floor(TFloat x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
    {
      if (static_cast<long long>(x) == x)
        return x;
      else
        return static_cast<TFloat>(static_cast<long long>(x) - ((x < TFloat(0)) ? 1LL : 0LL));
    }
    else
      return std::floor(x);
  }

  /// @brief Rounds `x` to the nearest integer. Halfway cases are rounded away from zero.
  /// @tparam TFloat A floating point type.
  /// @param x The input value.
  /// @return `x`, rounded to the nearest integer.
  template <IsFloatingPointT TFloat>
  NO_DISCARD constexpr TFloat Round(TFloat x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
      return TFloat(static_cast<long long>(x + (x > TFloat(0) ? TFloat(0.5) : TFloat(-0.5))));
    else
      return std::round(x);
  }

  /// @brief Computes the nearest integer not greater in magnitude than `x`.
  /// @tparam TFloat A floating point type.
  /// @param x The input value.
  /// @return The nearest integer not greater in magnitude than `x`.
  template <IsFloatingPointT TFloat>
  NO_DISCARD constexpr TFloat Trunc(TFloat x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
      return TFloat(static_cast<long long>(x));
    else
      return std::trunc(x);
  }
}