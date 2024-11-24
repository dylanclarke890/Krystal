#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Common/Min.hpp"
#include "MTL/Matrices/Base.hpp"
#include "MTL/Matrices/Ext/Algorithms.hpp"

namespace Krys::MTL
{
  /// @brief Performs a component-wise minimum operation between two matrices.
  /// @tparam TComponent The underlying arithmetic type of the matrices.
  /// @tparam CL The column length of the matrices.
  /// @tparam RL The row length of the matrices.
  /// @param a The first input matrix.
  /// @param b The second input matrix.
  /// @return A matrix where each component is the smaller of the corresponding components of `a` and `b`.
  template <IsArithmeticT TComponent, vec_length_t CL, vec_length_t RL>
  NO_DISCARD constexpr matrix_t<TComponent, CL, RL> Min(const matrix_t<TComponent, CL, RL> &a,
                                                        const matrix_t<TComponent, CL, RL> &b) noexcept
  {
    return MTL::Zip(a, b, [](TComponent x, TComponent y) -> TComponent { return MTL::Min(x, y); });
  }

  /// @brief Performs a component-wise minimum operation between three matrices.
  /// @tparam TComponent The underlying arithmetic type of the matrices.
  /// @tparam CL The column length of the matrices.
  /// @tparam RL The row length of the matrices.
  /// @param a The first input matrix.
  /// @param b The second input matrix.
  /// @param c The third input matrix.
  /// @return A matrix where each component is the smallest of the corresponding components of `a`, `b` and
  /// `c`.
  template <IsArithmeticT TComponent, vec_length_t CL, vec_length_t RL>
  NO_DISCARD constexpr matrix_t<TComponent, CL, RL> Min(const matrix_t<TComponent, CL, RL> &a,
                                                        const matrix_t<TComponent, CL, RL> &b,
                                                        const matrix_t<TComponent, CL, RL> &c) noexcept
  {
    return MTL::Zip(a, b, c,
                    [](TComponent x, TComponent y, TComponent z) -> TComponent { return MTL::Min(x, y, z); });
  }

  /// @brief Performs a component-wise minimum operation between the matrix `a` and scalar `b`.
  /// @tparam TComponent The underlying arithmetic type of the matrices.
  /// @tparam CL The column length of the matrices.
  /// @tparam RL The row length of the matrices.
  /// @param a The input matrix.
  /// @param b The minimum value each component is allowed to be.
  /// @return A matrix where each component is the smaller of the corresponding component of `a` and `b`.
  template <IsArithmeticT TComponent, vec_length_t CL, vec_length_t RL>
  NO_DISCARD constexpr matrix_t<TComponent, CL, RL> Min(const matrix_t<TComponent, CL, RL> &a,
                                                        TComponent b) noexcept
  {
    using mat_col_t = matrix_t<TComponent, CL, RL>::column_t;
    if constexpr (CL == 2 && RL == 2)
      return Min(a, matrix_t<TComponent, CL, RL>(mat_col_t(b), mat_col_t(b)));
    else if constexpr (CL == 3 && RL == 3)
      return Min(a, matrix_t<TComponent, CL, RL>(mat_col_t(b), mat_col_t(b), mat_col_t(b)));
    else if constexpr (CL == 4 && RL == 4)
      return Min(
        a, matrix_t<TComponent, CL, RL>(mat_col_t(b), mat_col_t(b), mat_col_t(b), mat_col_t(b)));
    else
      static_assert(false, "Unsupported number of cols/rows.");
  }
}
