#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Common/Radians.hpp"
#include "MTL/Matrices/Base.hpp"
#include "MTL/Matrices/Ext/Algorithms.hpp"

namespace Krys::MTL
{
  /// @brief Converts each component in `v` to radians.
  /// @tparam TComponent The underlying arithmetic type of the input matrix.
  /// @tparam CL The column length of the input matrix.
  /// @tparam RL The row length of the input matrix.
  /// @param v The input matrix.
  /// @returns The converted matrix.
  template <IsArithmeticT TComponent, vec_length_t CL, vec_length_t RL>
  NO_DISCARD constexpr matrix_t<TComponent, CL, RL> Radians(const matrix_t<TComponent, CL, RL>& m) noexcept
  {
    return MTL::MapEach(m, [](TComponent x) -> TComponent { return MTL::Radians(x); });
  }
}