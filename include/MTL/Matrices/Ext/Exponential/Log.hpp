#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Exponential/Log.hpp"
#include "MTL/Matrices/Base.hpp"
#include "MTL/Matrices/Ext/Common/Algorithms.hpp"

namespace Krys::MTL
{
  /// @brief Computes the natural logarithm (`ln(x)`) for each component in the input matrix.
  /// @tparam TComponent The underlying arithmetic type of the matrix.
  /// @tparam CL The column length of the matrix.
  /// @tparam RL The row length of the matrix.
  /// @param v The input matrix.
  /// @returns A matrix where each component is `ln(x)` for the corresponding input.
  template <IsArithmeticT TComponent, vec_length_t CL, vec_length_t RL>
  constexpr NO_DISCARD matrix_t<TComponent, CL, RL> Log(const matrix_t<TComponent, CL, RL> &v) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, T, CL, RL>(v, [](T x) -> T { return MTL::Log(x); });
  }
}
