#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Vectors/Base.hpp"
#include "MTL/Vectors/Ext/Algorithms.hpp"
#include "MTL/Vectors/Ext/Geometric/Dot.hpp"

namespace Krys::MTL
{
  /// @brief Projects vector `a` onto vector `b`.
  /// @tparam TComponent The underlying floating-point type of the vectors.
  /// @tparam L The length of the vectors.
  /// @param a The vector to project.
  /// @param b The vector to project onto.
  /// @return The projection of `a` onto `b`.
  template <IsFloatingPointT TComponent, vec_length_t L>
  constexpr vector_t<TComponent, L> Project(const vector_t<TComponent, L> &a,
                                            const vector_t<TComponent, L> &b) noexcept
  {
    return b * (MTL::Dot<TComponent, L>(a, b) / MTL::Dot<TComponent, L>(b, b));
  }
}
