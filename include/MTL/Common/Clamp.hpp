#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Common/MinMax.hpp"

#include <algorithm>

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
    KRYS_IF_COMPILE_CONTEXT
    {
      if constexpr (IsFloatingPointT<TNumber>)
        return MTL::FMin(MTL::FMax(value, min), max);
      else
        return MTL::Min(MTL::Max(value, min), max);
    }

    return std::clamp(value, min, max);
  }
}