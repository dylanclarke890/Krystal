#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"
#include "MTL/Vectors/Base.hpp"
#include "MTL/Vectors/Ext/Common/Algorithms.hpp"
#include "MTL/Vectors/Ext/Common/Mod.hpp"

namespace Krys::MTL
{
  /// @brief Computes the modulus of each component in the input vector.
  /// @tparam TComponent An arithmetic type.
  /// @tparam L The length of the vector.
  /// @param v The input vector.
  /// @returns A vector where each component is the modulus of the corresponding input component.
  template <IsArithmeticT TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, L> Mod(const vector_t<TComponent, L> &v) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, T, L>(v, [](T x) -> T { return MTL::Mod(x); });
  }
}
