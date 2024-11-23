#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Power/Sqrt.hpp"
#include "MTL/Vectors/Base.hpp"
#include "MTL/Vectors/Ext/Common/Algorithms.hpp"

namespace Krys::MTL
{
  /// @brief Computes the square root of each component in the input vector.
  /// @tparam TComponent The underlying arithmetic type of the vector.
  /// @tparam L The length of the vector.
  /// @param v The input vector.
  /// @returns A vector where each component is the square root of the corresponding input.
  template <IsArithmeticT TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, L> Sqrt(const vector_t<TComponent, L> &v) noexcept
  {
    return MTL::Map(v, [](TComponent x) -> TComponent { return MTL::Sqrt(x); });
  }
}
