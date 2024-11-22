#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Matrices/Base.hpp"
#include "MTL/Matrices/Ext/Common/Algorithms.hpp"
#include "MTL/Trigonometric/Asec.hpp"

namespace Krys::MTL
{
  /// @brief Computes inverse secant for each component in `v`.
  /// Each component should be a value for which the arc secant is defined.
  /// @tparam TComponent The underlying arithmetic type of the input matrix.
  /// @tparam CL The column length of the input matrix.
  /// @tparam RL The row length of the input matrix.
  /// @param v The input matrix.
  /// @returns The converted matrix.
  template <IsArithmeticT TComponent, vec_length_t CL, vec_length_t RL>
  NO_DISCARD constexpr matrix_t<TComponent, CL, RL> Asec(matrix_t<TComponent, CL, RL> v) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, T, CL, RL>(v, [](T val) -> T { return MTL::Asec(val); });
  }
}
