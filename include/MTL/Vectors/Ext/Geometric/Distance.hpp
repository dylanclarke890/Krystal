#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Vectors/Base.hpp"
#include "MTL/Vectors/Ext/Geometric/Length.hpp"

namespace Krys::MTL
{
  /// @brief Computes the distance between two vectors.
  /// @tparam TComponent The underlying floating-point type of the vectors.
  /// @tparam L The length of the vectors.
  /// @param a The first vector.
  /// @param b The second vector.
  /// @return The distance between `a` and `b`.
  template <IsFloatingPointT TComponent, vec_length_t L>
  constexpr TComponent Distance(const vector_t<TComponent, L> &a, const vector_t<TComponent, L> &b) noexcept
  {
    return MTL::Length<TComponent, L>(a - b);
  }
}
