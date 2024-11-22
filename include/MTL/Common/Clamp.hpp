#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Common/FMax.hpp"
#include "MTL/Common/FMin.hpp"
#include "MTL/Common/Max.hpp"
#include "MTL/Common/Min.hpp"

namespace Krys::MTL
{
  /// @brief Clamps `value` to lie within the specified range.
  /// @tparam TNumber An arithmetic type.
  /// @param value The input value.
  /// @param min The lower bound of the range.
  /// @param max The upper bound of the range.
  /// @returns The clamped value, such that `min <= result <= max`.
  template <IsArithmeticT TNumber>
  NO_DISCARD constexpr TNumber Clamp(TNumber value, TNumber min, TNumber max) noexcept
  {
    if constexpr (IsFloatingPointT<TNumber>)
      return MTL::FMin<TNumber>(MTL::FMax<TNumber>(value, min), max);
    else
      return MTL::Min<TNumber>(MTL::Max<TNumber>(value, min), max);
  }
}