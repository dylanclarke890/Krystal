#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Vectors/Base.hpp"
#include "MTL/Vectors/Ext/Algorithms.hpp"
#include "MTL/Vectors/Ext/Geometric/Dot.hpp"

namespace Krys::MTL
{
  /// @brief Reflects vector `v` across the normal `n`.
  /// @tparam TComponent The underlying floating-point type of the vectors.
  /// @tparam L The length of the vectors.
  /// @param v The input vector to reflect.
  /// @param n The normal vector to reflect across (should be normalized).
  /// @return The reflected vector.
  template <IsFloatingPointT TComponent, vec_length_t L>
  constexpr vector_t<TComponent, L> Reflect(const vector_t<TComponent, L> &v,
                                            const vector_t<TComponent, L> &n) noexcept
  {
    return v - TComponent(2) * MTL::Dot<TComponent, L>(v, n) * n;
  }
}
