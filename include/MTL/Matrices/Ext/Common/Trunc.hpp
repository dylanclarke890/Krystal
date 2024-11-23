#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Common/Trunc.hpp"
#include "MTL/Matrices/Base.hpp"
#include "MTL/Matrices/Ext/Algorithms.hpp"

namespace Krys::MTL
{
  /// @brief Computes the nearest integer not greater in magnitude than each component of the matrix.
  /// @tparam TComponent The underlying floating-point type of the matrix.
  /// @tparam CL The column length of the matrix.
  /// @tparam RL The row length of the matrix.
  /// @param m The input matrix.
  /// @returns A matrix with each component truncated to the nearest integer not greater in magnitude.
  template <IsFloatingPointT TComponent, vec_length_t CL, vec_length_t RL>
  NO_DISCARD constexpr matrix_t<TComponent, CL, RL> Trunc(const matrix_t<TComponent, CL, RL> &m) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, T, CL, RL>(m, [](T val) -> T { return MTL::Trunc<T>(val); });
  }
}
