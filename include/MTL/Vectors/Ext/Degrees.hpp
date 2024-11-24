#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Common/Degrees.hpp"
#include "MTL/Vectors/Base.hpp"
#include "MTL/Vectors/Ext/Algorithms.hpp"

namespace Krys::MTL
{
  /// @brief Converts each component in `v` to degrees.
  /// @tparam TComponent The underlying arithmetic type of the input vector.
  /// @tparam L The length of the input vector.
  /// @param v The input vector.
  /// @returns The converted vector.
  template <IsArithmeticT TComponent, vec_length_t L>
  NO_DISCARD constexpr auto Degrees(vector_t<TComponent, L> v) noexcept
  {
    return MTL::MapEach(v, [](TComponent val) -> TComponent { return MTL::Degrees(val); });
  }
}
