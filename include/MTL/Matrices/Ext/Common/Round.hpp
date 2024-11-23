#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Common/Round.hpp"
#include "MTL/Matrices/Base.hpp"
#include "MTL/Matrices/Ext/Algorithms.hpp"

namespace Krys::MTL
{
  /// @brief Rounds each component of the matrix to the nearest integer. Halfway cases are rounded away from
  /// zero.
  /// @tparam TComponent The underlying floating-point type of the matrix.
  /// @tparam CL The column length of the matrix.
  /// @tparam RL The row length of the matrix.
  /// @param m The input matrix.
  /// @returns A matrix with each component rounded to the nearest integer.
  template <IsFloatingPointT TComponent, vec_length_t CL, vec_length_t RL>
  NO_DISCARD constexpr matrix_t<TComponent, CL, RL> Round(const matrix_t<TComponent, CL, RL> &m) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, T, CL, RL>(m, [](T val) -> T { return MTL::Round<T>(val); });
  }
}
