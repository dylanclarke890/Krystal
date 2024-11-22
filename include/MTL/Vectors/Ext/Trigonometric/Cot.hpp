#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Trigonometric/Cot.hpp"
#include "MTL/Vectors/Base.hpp"
#include "MTL/Vectors/Ext/Common/Algorithms.hpp"

namespace Krys::MTL
{
  /// @brief Computes cotangent for each component in `v`.
  /// Each component should be an angle represented in radians.
  /// @tparam TComponent The underlying arithmetic type of the input vector.
  /// @tparam L The length of the input vector.
  /// @param v The input vector.
  /// @returns The converted vector.
  template <IsArithmeticT TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, L> Cot(vector_t<TComponent, L> v) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, T, L>(v, [](T val) -> T { return T(1) / MTL::Tan(val); });
  }
}
