#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Exponential/Exp10.hpp"
#include "MTL/Matrices/Base.hpp"
#include "MTL/Matrices/Ext/Common/Algorithms.hpp"

namespace Krys::MTL
{
  /// @brief Computes `10^x` for each component in the input matrix.
  /// @tparam TComponent The underlying arithmetic type of the matrix.
  /// @tparam CL The column length of the matrix.
  /// @tparam RL The row length of the matrix.
  /// @param v The input matrix.
  /// @returns A matrix where each component is `10^x` for the corresponding input.
  template <IsArithmeticT TComponent, vec_length_t CL, vec_length_t RL>
  NO_DISCARD constexpr matrix_t<TComponent, CL, RL> Exp10(const matrix_t<TComponent, CL, RL> &v) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, T, CL, RL>(v, [](T x) -> T { return MTL::Exp10(x); });
  }
}
