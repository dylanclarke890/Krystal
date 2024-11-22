#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Common/Constants.hpp"

#include <cmath>

namespace Krys::MTL
{
  /// @brief Computes the natural logarithm of `x`, i.e., ln(x).
  /// @tparam TNumber An arithmetic type.
  /// @param x The input value.
  /// @returns The result of ln(x).
  template <typename TNumber>
  constexpr TNumber Log(TNumber x) noexcept
  {
    KRYS_IF_COMPILE_CONTEXT
    {
      if (x <= TNumber(0)) // Log undefined for x <= 0
        return -std::numeric_limits<TNumber>::infinity();
      if (x == TNumber(1)) // ln(1) = 0
        return TNumber(0);

      // Range reduction: x = r * 2^k, where 1 <= r < 2
      int k = 0;
      while (x >= TNumber(2))
      {
        x /= TNumber(2);
        ++k;
      }
      while (x < TNumber(1))
      {
        x *= TNumber(2);
        --k;
      }

      // Reduced input r = x (now 1 <= x < 2)
      TNumber r = x - TNumber(1); // Use ln(1 + y) = y - y^2/2 + y^3/3 - ...

      // Compute ln(r) using a series expansion
      TNumber result = TNumber(0);
      TNumber term = r; // First term: y
      for (size_t n = 1; n <= 40; ++n)
      {                                                     // Use 40 terms for higher accuracy
        result += (n % 2 == 1 ? term : -term) / TNumber(n); // Alternating series
        term *= r;                                          // Compute y^n
      }

      // Combine results: ln(x) = k * ln(2) + ln(r)
      return TNumber(k) * MTL::LnTwo<TNumber>() + result;
    }

    return std::log(x);
  }
}