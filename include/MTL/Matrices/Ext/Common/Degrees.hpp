#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Common/Degrees.hpp"
#include "MTL/Matrices/Base.hpp"
#include "MTL/Matrices/Ext/Common/Algorithms.hpp"

namespace Krys::MTL
{
  /// @brief Converts each component in `v` to degrees.
  /// @tparam TComponent The underlying arithmetic type of the input matrix.
  /// @tparam CL The column length of the input matrix.
  /// @tparam RL The row length of the input matrix.
  /// @param v The input matrix.
  /// @returns The converted matrix.
  template <IsArithmeticT TComponent, vec_length_t CL, vec_length_t RL>
  constexpr NO_DISCARD matrix_t<TComponent, CL, RL> Degrees(matrix_t<TComponent, CL, RL> v) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, T, CL, RL>(v, [](T val) -> T { return MTL::Degrees<T>(val); });
  }
}
