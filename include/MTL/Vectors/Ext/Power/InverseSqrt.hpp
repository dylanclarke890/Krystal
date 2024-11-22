#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Power/InverseSqrt.hpp"
#include "MTL/Vectors/Base.hpp"
#include "MTL/Vectors/Ext/Common/Algorithms.hpp"

namespace Krys::MTL
{
  /// @brief Computes the inverse square root (`1 / sqrt(x)`) of each component in the input vector.
  /// @tparam TComponent The underlying arithmetic type of the vector.
  /// @tparam L The length of the vector.
  /// @param v The input vector.
  /// @returns A vector where each component is `1 / sqrt(x)` for the corresponding input.
  template <IsArithmeticT TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, L> InverseSqrt(const vector_t<TComponent, L> &v) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, T, L>(v, [](T x) -> T { return MTL::InverseSqrt<T>(x); });
  }
}
