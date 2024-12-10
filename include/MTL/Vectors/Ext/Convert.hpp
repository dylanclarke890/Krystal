#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Common/Convert.hpp"
#include "MTL/Vectors/Base.hpp"
#include "MTL/Vectors/Ext/Algorithms.hpp"

namespace Krys::MTL
{
  /// @brief Converts each component in `v` to degrees.
  /// @tparam TComponent The underlying arithmetic type of the input vector.
  /// @tparam L The length of the input vector.
  /// @param v The input vector.
  /// @returns The converted vector.
  template <IsArithmeticT TComponent, vec_length_t L>
  NO_DISCARD constexpr auto Degrees(vector_t<TComponent, L> v) noexcept
  {
    return MTL::MapEach(v, [](TComponent val) -> TComponent { return MTL::Degrees(val); });
  }

  /// @brief Converts each component in `x` to radians.
  /// @tparam TComponent The underlying arithmetic type of the input vector.
  /// @tparam L The length of the input vector.
  /// @param x The input vector.
  /// @returns The converted vector.
  template <IsArithmeticT TComponent, vec_length_t L>
  NO_DISCARD constexpr auto Radians(const vector_t<TComponent, L> &x) noexcept
  {
    return MTL::MapEach(x, [](TComponent v) -> TComponent { return MTL::Radians(v); });
  }
}
