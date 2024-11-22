#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"
#include "MTL/Common/IsNaN.hpp"

#include <bit>
#include <cmath>

namespace Krys::MTL
{
  /// @brief Determines if `x` is negative.
  /// @tparam TSigned A signed type.
  /// @param x The input value.
  /// @return `true` if `x` is negative.
  template <IsSignedT TSigned>
  NO_DISCARD constexpr bool Signbit(TSigned x) noexcept
  {
    if constexpr (IsIntegralT<TSigned>)
    {
      return (x < TSigned(0));
    }
    else if constexpr (IsFloatingPointT<TSigned>)
    {
      if (MTL::IsNaN(x))
        return false; // NaN values do not have a meaningful sign bit.

      using as_uint_t = std::conditional_t<std::is_same_v<TSigned, float>, uint32, uint64>;
      as_uint_t bits = std::bit_cast<as_uint_t>(x);

      // Check the most significant bit (MSB), which represents the sign bit.
      return (bits & (as_uint_t(1) << (sizeof(as_uint_t) * 8 - 1))) != 0;
    }
    else
    {
      static_assert(false, "Unsupported type for Signbit");
    }
  }
}
