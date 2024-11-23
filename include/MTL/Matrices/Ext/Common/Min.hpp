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
    using T = TComponent;
    return MTL::Zip<T, T, CL, RL>(a, b, [](T x, T y) -> T { return MTL::Min(x, y); });
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
    using T = TComponent;
    return MTL::Zip<T, T, T, CL, RL>(a, b, c, [](T x, T y, T z) -> T { return MTL::Min(x, y, z); });
  }

  /// @brief Performs a component-wise minimum operation between four matrices.
  /// @tparam TComponent The underlying arithmetic type of the matrices.
  /// @tparam CL The column length of the matrices.
  /// @tparam RL The row length of the matrices.
  /// @param a The first input matrix.
  /// @param b The second input matrix.
  /// @param c The third input matrix.
  /// @param d The fourth input matrix.
  /// @return A matrix where each component is the smallest of the corresponding components of `a`, `b`, `c`
  /// and `d`.
  template <IsArithmeticT TComponent, vec_length_t CL, vec_length_t RL>
  NO_DISCARD constexpr matrix_t<TComponent, CL, RL>
    Min(const matrix_t<TComponent, CL, RL> &a, const matrix_t<TComponent, CL, RL> &b,
        const matrix_t<TComponent, CL, RL> &c, const matrix_t<TComponent, CL, RL> &d) noexcept
  {
    using T = TComponent;
    return MTL::Zip<T, T, T, T, CL, RL>(a, b, c, d,
                                        [](T x, T y, T z, T w) -> T { return MTL::Min(x, y, z, w); });
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
    using T = TComponent;
    return MTL::Zip<T, T, CL, RL>(a, matrix_t<T, CL, RL>(b), [](T x, T y) -> T { return MTL::Min(x, y); });
  }
}
