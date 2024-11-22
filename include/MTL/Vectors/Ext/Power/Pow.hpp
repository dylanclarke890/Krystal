#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Power/Pow.hpp"
#include "MTL/Vectors/Base.hpp"
#include "MTL/Vectors/Ext/Common/Algorithms.hpp"

namespace Krys::MTL
{
  /// @brief Performs a component-wise `Pow` operation on `base` and `exponent` vectors.
  /// @tparam TComponent The underlying arithmetic type of the vectors.
  /// @tparam L The length of the vectors.
  /// @param base The base vector.
  /// @param exponent The exponent vector.
  /// @returns A vector where each component is `base[i]` raised to the power of `exponent[i]`.
  template <IsArithmeticT TComponent, vec_length_t L>
  constexpr NO_DISCARD vector_t<TComponent, L> Pow(const vector_t<TComponent, L> &base,
                                                   const vector_t<TComponent, L> &exponent) noexcept
  {
    using T = TComponent;
    return MTL::Zip<T, T, T, L>(base, exponent, [](T b, T e) -> T { return MTL::Pow<T>(b, e); });
  }
}
