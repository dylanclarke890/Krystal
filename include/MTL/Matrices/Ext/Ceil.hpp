#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Common/Ceil.hpp"
#include "MTL/Matrices/Base.hpp"
#include "MTL/Matrices/Ext/Algorithms.hpp"

namespace Krys::MTL
{
  /// @brief Computes the smallest integer not smaller than each component of the matrix.
  /// @tparam TComponent The underlying floating-point type of the matrix.
  /// @tparam CL The column length of the matrix.
  /// @tparam RL The row length of the matrix.
  /// @param m The input matrix.
  /// @returns A matrix with each component rounded up to the smallest integer.
  template <IsFloatingPointT TComponent, vec_length_t CL, vec_length_t RL>
  NO_DISCARD constexpr matrix_t<TComponent, CL, RL> Ceil(const matrix_t<TComponent, CL, RL> &m) noexcept
  {
    return MTL::MapEach(m, [](TComponent x) -> TComponent { return MTL::Ceil(x); });
  }
}
