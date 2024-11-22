#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Matrices/Base.hpp"
#include "MTL/Matrices/Ext/Common/Algorithms.hpp"
#include "MTL/Power/Pow.hpp"

namespace Krys::MTL
{
  /// @brief Performs a component-wise `Pow` operation on `base` and `exponent` matrices.
  /// @tparam TComponent The underlying arithmetic type of the matrices.
  /// @tparam CL The column length of the matrices.
  /// @tparam RL The row length of the matrices.
  /// @param base The base matrix.
  /// @param exponent The exponent matrix.
  /// @returns A matrix where each component is `base[i][j]` raised to the power of `exponent[i][j]`.
  template <IsArithmeticT TComponent, vec_length_t CL, vec_length_t RL>
  NO_DISCARD constexpr matrix_t<TComponent, CL, RL> Pow(const matrix_t<TComponent, CL, RL> &base,
                                                        const matrix_t<TComponent, CL, RL> &exponent) noexcept
  {
    using T = TComponent;
    return MTL::Zip<T, T, T, CL, RL>(base, exponent, [](T b, T e) -> T { return MTL::Pow(b, e); });
  }
}
