#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Common/FMax.hpp"
#include "MTL/Matrices/Base.hpp"
#include "MTL/Matrices/Ext/Algorithms.hpp"

namespace Krys::MTL
{
  /// @brief Performs a component-wise maximum operation between two floating point matrices, ignoring NaN.
  /// @tparam TComponent The underlying arithmetic type of the matrices.
  /// @tparam CL The column length of the matrices.
  /// @tparam RL The row length of the matrices.
  /// @param a The first input matrix.
  /// @param b The second input matrix.
  /// @return A matrix where each component is the larger of the corresponding components of `a` and `b`.
  template <IsFloatingPointT TComponent, vec_length_t CL, vec_length_t RL>
  NO_DISCARD constexpr matrix_t<TComponent, CL, RL> FMax(const matrix_t<TComponent, CL, RL> &a,
                                                         const matrix_t<TComponent, CL, RL> &b) noexcept
  {
    return MTL::Zip(a, b, [](TComponent x, TComponent y) -> TComponent { return MTL::FMax(x, y); });
  }

  /// @brief Performs a component-wise maximum operation between three floating point matrices, ignoring NaN.
  /// @tparam TComponent The underlying floating-point type of the matrices.
  /// @tparam CL The column length of the matrices.
  /// @tparam RL The row length of the matrices.
  /// @param a The first input matrix.
  /// @param b The second input matrix.
  /// @param c The third input matrix.
  /// @return A matrix where each component is the largest of the corresponding components of `a`, `b` and
  /// `c`, ignoring NaN.
  template <IsFloatingPointT TComponent, vec_length_t CL, vec_length_t RL>
  NO_DISCARD constexpr matrix_t<TComponent, CL, RL> FMax(const matrix_t<TComponent, CL, RL> &a,
                                                         const matrix_t<TComponent, CL, RL> &b,
                                                         const matrix_t<TComponent, CL, RL> &c) noexcept
  {
    return MTL::Zip(a, b, c, [](TComponent x, TComponent y, TComponent z) -> TComponent
                    { return MTL::FMax(x, y, z); });
  }

  /// @brief Performs a component-wise maximum operation between the matrix `a` and floating point `b`.
  /// @tparam TComponent The underlying floating-point type of the matrices.
  /// @tparam CL The column length of the matrices.
  /// @tparam RL The row length of the matrices.
  /// @param a The input matrix.
  /// @param b The maximum value each component is allowed to be.
  /// @return A matrix where each component is the larger of the corresponding component of `a` and `b`,
  /// ignoring NaN.
  template <IsFloatingPointT TComponent, vec_length_t CL, vec_length_t RL>
  NO_DISCARD constexpr matrix_t<TComponent, CL, RL> FMax(const matrix_t<TComponent, CL, RL> &a,
                                                         TComponent b) noexcept
  {
    return MTL::Zip(a, matrix_t<TComponent, CL, RL>(b),
                    [](TComponent x, TComponent y) -> TComponent { return MTL::FMax(x, y); });
  }
}
