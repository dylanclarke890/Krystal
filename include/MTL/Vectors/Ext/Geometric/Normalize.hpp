#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Power/InverseSqrt.hpp"
#include "MTL/Vectors/Base.hpp"
#include "MTL/Vectors/Ext/Algorithms.hpp"
#include "MTL/Vectors/Ext/Geometric/Dot.hpp"

namespace Krys::MTL
{
  /// @brief Normalizes a vector (scales it to length 1).
  /// @tparam TComponent The underlying floating-point type of the vector.
  /// @tparam L The length of the vector.
  /// @param x The input vector.
  /// @return A normalized version of the vector.
  template <IsFloatingPointT TComponent, vec_length_t L>
  constexpr vector_t<TComponent, L> Normalize(const vector_t<TComponent, L> &x) noexcept
  {
    return x * MTL::InverseSqrt<TComponent>(MTL::Dot<TComponent, L>(x, x));
  }
}
