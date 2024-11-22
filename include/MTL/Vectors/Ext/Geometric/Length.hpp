#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Power/Sqrt.hpp"
#include "MTL/Vectors/Base.hpp"
#include "MTL/Vectors/Ext/Geometric/Dot.hpp"

namespace Krys::MTL
{
  /// @brief Computes the length (magnitude) of a vector.
  /// @tparam TComponent The underlying floating-point type of the vector.
  /// @tparam L The length of the vector.
  /// @param x The input vector.
  /// @return The length of the vector.
  template <IsFloatingPointT TComponent, vec_length_t L>
  constexpr TComponent Length(const vector_t<TComponent, L> &x) noexcept
  {
    return MTL::Sqrt<TComponent>(MTL::Dot<TComponent, L>(x, x));
  }
}
