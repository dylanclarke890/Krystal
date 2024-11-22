#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Common/Floor.hpp"
#include "MTL/Matrices/Base.hpp"
#include "MTL/Matrices/Ext/Common/Algorithms.hpp"

namespace Krys::MTL
{
  /// @brief Computes the largest integer not greater than each component of the matrix.
  /// @tparam TComponent The underlying floating-point type of the matrix.
  /// @tparam CL The column length of the matrix.
  /// @tparam RL The row length of the matrix.
  /// @param m The input matrix.
  /// @returns A matrix with each component rounded down to the largest integer.
  template <IsFloatingPointT TComponent, vec_length_t CL, vec_length_t RL>
  NO_DISCARD constexpr matrix_t<TComponent, CL, RL> Floor(const matrix_t<TComponent, CL, RL> &m) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, T, CL, RL>(m, [](T val) -> T { return MTL::Floor<T>(val); });
  }
}
