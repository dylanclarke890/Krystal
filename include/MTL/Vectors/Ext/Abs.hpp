#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Common/Abs.hpp"
#include "MTL/Vectors/Base.hpp"
#include "MTL/Vectors/Ext/Algorithms.hpp"

namespace Krys::MTL
{
  /// @brief Computes the absolute value of each component in the input vector.
  /// @tparam TComponent A signed arithmetic type.
  /// @tparam L The length of the vector.
  /// @param v The input vector.
  /// @returns A vector where each component is the absolute value of the corresponding input component.
  template <IsSignedT TComponent, vec_length_t L>
  NO_DISCARD constexpr auto Abs(const vector_t<TComponent, L> &v) noexcept
  {
    return MTL::MapEach(v, [](TComponent x) -> TComponent { return MTL::Abs(x); });
  }
}
