#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"
#include "MTL/IsNaN.hpp"

#include <bit>
#include <cmath>

namespace Krys::MTL
{
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
}
