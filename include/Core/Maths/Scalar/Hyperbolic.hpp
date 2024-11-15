#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"

#include <cmath>

namespace Krys::MTL
{
  /// @brief Computes hyperbolic sine.
  /// @tparam TNumber An arithmetic type (floating point types are advised).
  /// @param num
  /// @returns The computed value.
  template <IsArithmeticT TNumber>
  constexpr NO_DISCARD TNumber Sinh(TNumber num) noexcept
  {
    return std::sinh(num);
  }

  /// @brief Computes hyperbolic cosine.
  /// @tparam TNumber An arithmetic type (floating point types are advised).
  /// @param num
  /// @returns The computed value.
  template <IsArithmeticT TNumber>
  constexpr NO_DISCARD TNumber Cosh(TNumber num) noexcept
  {
    return std::cosh(num);
  }

  /// @brief Computes hyperbolic tangent.
  /// @tparam TNumber An arithmetic type (floating point types are advised).
  /// @param num
  /// @returns The computed value.
  template <IsArithmeticT TNumber>
  constexpr NO_DISCARD TNumber Tanh(TNumber num) noexcept
  {
    return std::tanh(num);
  }

  /// @brief Computes the inverse hyperbolic sine.
  /// @tparam TNumber An arithmetic type (floating point types are advised).
  /// @param num
  /// @returns The computed value.
  template <IsArithmeticT TNumber>
  constexpr NO_DISCARD TNumber Asinh(TNumber num) noexcept
  {
    return std::asinh(num);
  }

  /// @brief Computes the inverse hyperbolic cosine.
  /// @tparam TNumber An arithmetic type (floating point types are advised).
  /// @param num
  /// @returns The computed value.
  template <IsArithmeticT TNumber>
  constexpr NO_DISCARD TNumber Acosh(TNumber num) noexcept
  {
    return std::acosh(num);
  }

  /// @brief Computes the inverse hyperbolic tangent.
  /// @tparam TNumber An arithmetic type (floating point types are advised).
  /// @param num
  /// @returns The computed value.
  template <IsArithmeticT TNumber>
  constexpr NO_DISCARD TNumber Atanh(TNumber num) noexcept
  {
    return std::atanh(num);
  }
}