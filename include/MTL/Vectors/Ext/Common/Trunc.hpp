#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Common/Trunc.hpp"
#include "MTL/Vectors/Base.hpp"
#include "MTL/Vectors/Ext/Common/Algorithms.hpp"

namespace Krys::MTL
{
  /// @brief Computes the nearest integer not greater in magnitude than each component of the vector.
  /// @tparam TComponent The underlying floating-point type of the input vector.
  /// @tparam L The length of the input vector.
  /// @param v The input vector.
  /// @returns A vector with each component truncated to the nearest integer not greater in magnitude.
  template <IsFloatingPointT TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, L> Trunc(vector_t<TComponent, L> v) noexcept
  {
    return MTL::MapEach(v, [](TComponent val) -> TComponent { return MTL::Trunc(val); });
  }
}
