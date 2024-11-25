#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Common/Abs.hpp"

#include <cmath>

namespace Krys::MTL
{
  /// @brief Checks if `x` is NaN (Not a Number).
  /// @tparam TFloat A floating-point type.
  /// @param x The input value.
  /// @return `true` if `x` is NaN.
  template <IsFloatingPointT TFloat>
  NO_DISCARD constexpr bool IsNaN(TFloat x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
      return x != x;
    else
      return std::isnan(x);
  }

  /// @brief Checks if `x` is infinite.
  /// @tparam TFloat A floating-point type.
  /// @param x The input value.
  /// @return `true` if `x` is infinite.
  template <IsFloatingPointT TFloat>
  NO_DISCARD constexpr bool IsInfinite(TFloat x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
      return x == ((x < 0 ? -1 : 1) * std::numeric_limits<TFloat>::infinity());
    else
      return std::isinf(x);
  }

  /// @brief Checks if `x` is finite.
  /// @tparam TFloat A floating-point type.
  /// @param x The input value.
  /// @return `true` if `x` is finite (not NaN or infinite).
  template <IsFloatingPointT TFloat>
  NO_DISCARD constexpr bool IsFinite(TFloat x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
      return !MTL::IsNaN(x) && !MTL::IsInfinite(x);
    else
      return std::isfinite(x);
  }

  /// @brief Checks if `x` is denormalized (too small to be represented as a
  /// normalized number).
  /// @tparam TFloat A floating-point type.
  /// @param x The input value.
  /// @return `true` if `x` is denormalized.
  template <IsFloatingPointT TFloat>
  NO_DISCARD constexpr bool IsDenormal(TFloat x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
    {
      if (MTL::IsNaN(x) || x == TFloat(0))
        return false;
      else
        return MTL::Abs(x) < std::numeric_limits<TFloat>::min();
    }
    else
      return std::fpclassify(x) == FP_SUBNORMAL;
  }

  /// @brief Checks if `x` is normal (neither zero, subnormal, infinite, nor NaN).
  /// @tparam TFloat A floating-point type.
  /// @param x The input value.
  /// @return `true` if `x` is a normal floating-point number.
  template <IsFloatingPointT TFloat>
  NO_DISCARD constexpr bool IsNormal(TFloat x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
      return MTL::IsFinite(x) && !MTL::IsDenormal(x) && x != TFloat(0);
    else
      return std::isnormal(x);
  }
}
