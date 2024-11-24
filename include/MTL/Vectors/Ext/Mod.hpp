#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Common/Mod.hpp"
#include "MTL/Vectors/Base.hpp"
#include "MTL/Vectors/Ext/Algorithms.hpp"

namespace Krys::MTL
{
  /// @brief Computes the modulus of each component in the input vector.
  /// @tparam TComponent An arithmetic type.
  /// @tparam L The length of the vector.
  /// @param v The input vector.
  /// @returns A vector where each component is the modulus of the corresponding input component.
  template <IsArithmeticT TComponent, vec_length_t L>
  NO_DISCARD constexpr auto Mod(const vector_t<TComponent, L> &a, const vector_t<TComponent, L> &b) noexcept
  {
    return MTL::Zip(a, b, [](TComponent x, TComponent y) -> TComponent { return MTL::Mod(x, y); });
  }
}
