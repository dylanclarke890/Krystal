#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Common/Clamp.hpp"
#include "MTL/Matrices/Base.hpp"
#include "MTL/Matrices/Ext/Algorithms.hpp"

namespace Krys::MTL
{
  /// @brief Clamps each component of the matrix between the corresponding components of the `min` and `max`
  /// matrices.
  /// @tparam TComponent The underlying arithmetic type of the matrices.
  /// @tparam CL The column length of the matrices.
  /// @tparam RL The row length of the matrices.
  /// @param value The input matrix to clamp.
  /// @param min The matrix containing the minimum values.
  /// @param max The matrix containing the maximum values.
  /// @return A matrix where each component is clamped between the corresponding components of `min` and
  /// `max`.
  template <IsArithmeticT TComponent, vec_length_t CL, vec_length_t RL>
  NO_DISCARD constexpr matrix_t<TComponent, CL, RL> Clamp(const matrix_t<TComponent, CL, RL> &value,
                                                          const matrix_t<TComponent, CL, RL> &min,
                                                          const matrix_t<TComponent, CL, RL> &max) noexcept
  {
    return MTL::Zip(value, min, max, [](TComponent v, TComponent lo, TComponent hi) -> TComponent
                    { return MTL::Clamp(v, lo, hi); });
  }

  /// @brief Clamps each component of the matrix between the scalar values `min` and `max`.
  /// @tparam TComponent The underlying arithmetic type of the matrix.
  /// @tparam CL The column length of the matrix.
  /// @tparam RL The row length of the matrix.
  /// @param value The input matrix to clamp.
  /// @param min The minimum scalar value for clamping.
  /// @param max The maximum scalar value for clamping.
  /// @return A matrix where each component is clamped between `min` and `max`.
  template <IsArithmeticT TComponent, vec_length_t CL, vec_length_t RL>
  NO_DISCARD constexpr matrix_t<TComponent, CL, RL> Clamp(const matrix_t<TComponent, CL, RL> &value,
                                                          TComponent min, TComponent max) noexcept
  {
    using mat_col_t = matrix_t<TComponent, CL, RL>::column_t;
    if constexpr (CL == 2 && RL == 2)
      return Clamp(value, matrix_t<TComponent, CL, RL>(mat_col_t(min), mat_col_t(min)),
                   matrix_t<TComponent, CL, RL>(mat_col_t(max), mat_col_t(max)));
    else if constexpr (CL == 3 && RL == 3)
      return Clamp(value, matrix_t<TComponent, CL, RL>(mat_col_t(min), mat_col_t(min), mat_col_t(min)),
                   matrix_t<TComponent, CL, RL>(mat_col_t(max), mat_col_t(max), mat_col_t(max)));
    else if constexpr (CL == 4 && RL == 4)
      return Clamp(
        value, matrix_t<TComponent, CL, RL>(mat_col_t(min), mat_col_t(min), mat_col_t(min), mat_col_t(min)),
        matrix_t<TComponent, CL, RL>(mat_col_t(max), mat_col_t(max), mat_col_t(max), mat_col_t(max)));
    else
      static_assert(false, "Unsupported number of cols/rows.");
  }
}
