#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Vectors/Base.hpp"
#include "MTL/Vectors/Ext/Common/Algorithms.hpp"

namespace Krys::MTL
{
  /// @brief Computes the dot product of two vectors.
  /// @tparam TComponent The underlying floating-point type of the vectors.
  /// @tparam L The length of the vectors.
  /// @param a The first vector.
  /// @param b The second vector.
  /// @return The dot product of `a` and `b`.
  template <IsFloatingPointT TComponent, vec_length_t L>
  constexpr TComponent Dot(const vector_t<TComponent, L> &a, const vector_t<TComponent, L> &b) noexcept
  {
    if constexpr (L == 1)
      return a.x * b.x;
    else if constexpr (L == 2)
      return a.x * b.x + a.y * b.y;
    else if constexpr (L == 3)
      return a.x * b.x + a.y * b.y + a.z * b.z;
    else if constexpr (L == 4)
      return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
    else
      static_assert(false, "Unsupported number of components");
  }
}
