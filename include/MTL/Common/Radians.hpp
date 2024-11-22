#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"

namespace Krys::MTL
{
  /// @brief Converts `degrees` to radians.
  /// @tparam TNumber An arithmetic type (floating point types are advised).
  /// @param degrees The input value.
  /// @returns The converted value.
  template <IsArithmeticT TNumber>
  NO_DISCARD constexpr TNumber Radians(TNumber degrees) noexcept
  {
    return degrees * static_cast<TNumber>(0.01745329251994329576923690768489);
  }
}