#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Common/Max.hpp"
#include "MTL/Common/Min.hpp"

namespace Krys::MTL
{
  /// @brief Clamps a value to lie within the specified range.
  /// @tparam TNumber An arithmetic type.
  /// @param value The input value.
  /// @param min The lower bound of the range.
  /// @param max The upper bound of the range.
  /// @returns The clamped value, such that `min <= result <= max`.
  template <IsArithmeticT TNumber>
  constexpr NO_DISCARD TNumber Clamp(TNumber value, TNumber min, TNumber max) noexcept
  {
    return MTL::Min<TNumber>(MTL::Max<TNumber>(value, min), max);
  }
}