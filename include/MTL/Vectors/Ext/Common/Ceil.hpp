#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Common/Ceil.hpp"
#include "MTL/Vectors/Base.hpp"
#include "MTL/Vectors/Ext/Common/Algorithms.hpp"

namespace Krys::MTL
{
  /// @brief Computes the smallest integer not smaller than each component of the vector.
  /// @tparam TComponent The underlying floating-point type of the input vector.
  /// @tparam L The length of the input vector.
  /// @param v The input vector.
  /// @returns A vector with each component rounded up to the smallest integer.
  template <IsFloatingPointT TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, L> Ceil(vector_t<TComponent, L> v) noexcept
  {
    return MTL::MapEach(v, [](TComponent x) -> TComponent { return MTL::Ceil(x); });
  }
}
