#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Vectors/Base.hpp"
#include "MTL/Vectors/Ext/Common/Algorithms.hpp"

namespace Krys::MTL
{
  /// @brief Computes the cross product of two 3D vectors.
  /// @tparam TComponent The underlying floating-point type of the vectors.
  /// @param a The first vector.
  /// @param b The second vector.
  /// @return The cross product of `a` and `b`.
  template <IsFloatingPointT TComponent>
  constexpr vector_t<TComponent, 3> Cross(const vector_t<TComponent, 3> &a,
                                          const vector_t<TComponent, 3> &b) noexcept
  {
    return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
  }
}
