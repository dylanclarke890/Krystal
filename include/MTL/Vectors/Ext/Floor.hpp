#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Common/Floor.hpp"
#include "MTL/Vectors/Base.hpp"
#include "MTL/Vectors/Ext/Algorithms.hpp"

namespace Krys::MTL
{
  /// @brief Computes the largest integer not greater than each component of the vector.
  /// @tparam TComponent The underlying floating-point type of the input vector.
  /// @tparam L The length of the input vector.
  /// @param v The input vector.
  /// @returns A vector with each component rounded down to the largest integer.
  template <IsFloatingPointT TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, L> Floor(vector_t<TComponent, L> v) noexcept
  {
    return MTL::MapEach(v, [](TComponent val) -> TComponent { return MTL::Floor(val); });
  }
}