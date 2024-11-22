#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"

namespace Krys::MTL
{
  /// @brief Converts `radians` to degrees.
  /// @tparam TNumber An arithmetic type (floating point types are advised).
  /// @param radians The input value.
  /// @returns The converted value.
  template <IsArithmeticT TNumber>
  NO_DISCARD constexpr TNumber Degrees(TNumber radians) noexcept
  {
    return radians * TNumber(57.295779513082320876798154814105);
  }
}
