#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Common/Round.hpp"
#include "MTL/Vectors/Base.hpp"
#include "MTL/Vectors/Ext/Algorithms.hpp"

namespace Krys::MTL
{
  /// @brief Rounds each component of the vector to the nearest integer. Halfway cases are rounded away from
  /// zero.
  /// @tparam TComponent The underlying floating-point type of the input vector.
  /// @tparam L The length of the input vector.
  /// @param v The input vector.
  /// @returns A vector with each component rounded to the nearest integer.
  template <IsFloatingPointT TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, L> Round(vector_t<TComponent, L> v) noexcept
  {
    return MTL::MapEach(v, [](TComponent val) -> TComponent { return MTL::Round(val); });
  }
}