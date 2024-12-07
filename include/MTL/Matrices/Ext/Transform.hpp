#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Matrices/Base.hpp"
#include "MTL/Matrices/Ext/Algorithms.hpp"

namespace Krys::MTL
{
  /// @brief
  /// @tparam TComponent The underlying floating-point type of the matrix.
  /// @param m The input matrix.
  /// @returns
  template <IsFloatingPointT TComponent>
  NO_DISCARD constexpr auto Translate(const matrix_t<TComponent, 4, 4> &m,
                                      const vector_t<TComponent, 3> &v) noexcept
  {
    matrix_t<TComponent, 4, 4> result {m};
    result[3] = m[0] * v[0] + m[1] * v[1] + m[2] * v[2] + m[3];
    return result;
  }

  /// @brief
  /// @tparam TComponent The underlying floating-point type of the matrix.
  /// @tparam RL The row length of the matrix.
  /// @tparam CL The column length of the matrix.
  /// @param m The input matrix.
  /// @returns
  template <IsFloatingPointT TComponent, vec_length_t RL, vec_length_t CL>
  NO_DISCARD constexpr auto Rotate(const matrix_t<TComponent, 4, 4> &m, TComponent angle,
                                   const vector_t<TComponent, 3> &axis) noexcept
  {
  }

  /// @brief
  /// @tparam TComponent The underlying floating-point type of the matrix.
  /// @tparam RL The row length of the matrix.
  /// @tparam CL The column length of the matrix.
  /// @param m The input matrix.
  /// @returns
  template <IsFloatingPointT TComponent, vec_length_t RL, vec_length_t CL>
  NO_DISCARD constexpr auto Scale(const matrix_t<TComponent, 4, 4> &m,
                                  const vector_t<TComponent, 3> &v) noexcept
  {
  }
}