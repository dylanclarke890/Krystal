#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Exponential/Log2.hpp"
#include "MTL/Vectors/Base.hpp"
#include "MTL/Vectors/Ext/Common/Algorithms.hpp"

namespace Krys::MTL
{
  /// @brief Computes the base-2 logarithm (`log2(x)`) for each component in the input vector.
  /// @tparam TComponent The underlying arithmetic type of the vector.
  /// @tparam L The length of the vector.
  /// @param v The input vector.
  /// @returns A vector where each component is `log2(x)` for the corresponding input.
  template <IsArithmeticT TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, L> Log2(const vector_t<TComponent, L> &v) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, T, L>(v, [](T x) -> T { return MTL::Log2(x); });
  }
}
