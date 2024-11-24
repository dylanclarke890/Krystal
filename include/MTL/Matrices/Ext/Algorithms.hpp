#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"
#include "MTL/Matrices/Base.hpp"

namespace Krys::MTL
{
  /// @brief Applies a function to each component of the matrix.
  /// @tparam TComponent The underlying arithmetic type of the matrix.
  /// @tparam CL The column length of the input matrix.
  /// @tparam RL The row length of the input matrix.
  /// @param v The input matrix.
  /// @param func A callable object or lambda to be applied to each component.
  template <IsArithmeticT TComponent, vec_length_t CL, vec_length_t RL, IsRegularCallableT<TComponent> TFunc>
  constexpr void ForEach(const matrix_t<TComponent, CL, RL> &v, TFunc func) noexcept
  {
    if constexpr (CL == 2 && RL == 2)
    {
      func(v[0].x);
      func(v[0].y);

      func(v[1].x);
      func(v[1].y);
    }
    else if constexpr (CL == 3 && RL == 3)
    {
      func(v[0].x);
      func(v[0].y);
      func(v[0].z);

      func(v[1].x);
      func(v[1].y);
      func(v[1].z);

      func(v[2].x);
      func(v[2].y);
      func(v[2].z);
    }
    else if constexpr (CL == 4 && RL == 4)
    {
      func(v[0].x);
      func(v[0].y);
      func(v[0].z);
      func(v[0].w);

      func(v[1].x);
      func(v[1].y);
      func(v[1].z);
      func(v[1].w);

      func(v[2].x);
      func(v[2].y);
      func(v[2].z);
      func(v[2].w);

      func(v[3].x);
      func(v[3].y);
      func(v[3].z);
      func(v[3].w);
    }
    else
    {
      static_assert(false, "Unsupported number of rows/columns");
    }
  }

  /// @brief Creates a new matrix by applying a function to each component of the input matrix.
  /// @tparam TComponentIn The underlying arithmetic type of the input matrix.
  /// @tparam TOut The underlying arithmetic type of the output matrix.
  /// @tparam CL The column length of the input matrix.
  /// @tparam RL The row length of the input matrix.
  /// @param v The input matrix.
  /// @param func A callable object or lambda that returns the transformed value for each component.
  /// @return A matrix where each component is the result of applying `func` to the corresponding input
  /// component.
  template <IsArithmeticT TComponent, vec_length_t CL, vec_length_t RL, typename TFunc>
  constexpr auto MapEach(const matrix_t<TComponent, CL, RL> &v,
                         TFunc func) noexcept -> matrix_t<decltype(func(declval<TComponent>())), CL, RL>
  {
    using TReturn = decltype(func(declval<TComponent>()));
    if constexpr (CL == 2 && RL == 2)
      return matrix_t<TReturn, 2, 2>(func(v[0].x), func(v[0].y), func(v[1].x), func(v[1].y));
    else if constexpr (CL == 3 && RL == 3)
      return matrix_t<TReturn, 3, 3>(func(v[0].x), func(v[0].y), func(v[0].z), func(v[1].x), func(v[1].y),
                                     func(v[1].z), func(v[2].x), func(v[2].y), func(v[2].z));
    else if constexpr (CL == 4 && RL == 4)
      return matrix_t<TReturn, 4, 4>(func(v[0].x), func(v[0].y), func(v[0].z), func(v[0].w), func(v[1].x),
                                     func(v[1].y), func(v[1].z), func(v[1].w), func(v[2].x), func(v[2].y),
                                     func(v[2].z), func(v[2].w), func(v[3].x), func(v[3].y), func(v[3].z),
                                     func(v[3].w));
    else
      static_assert(false, "Unsupported number of rows/columns");
  }

  /// @brief Creates a new matrix from two input matrices by applying a function to each component pair of
  /// the input matrices.
  /// @tparam TComponentInA The underlying arithmetic type of the first input matrix.
  /// @tparam TComponentInB The underlying arithmetic type of the second input matrix.
  /// @tparam TOut The underlying arithmetic type of the output matrix.
  /// @tparam CL The column length of the input matrix.
  /// @tparam RL The row length of the input matrix.
  /// @param v The input matrix.
  /// @param func A callable object or lambda that returns the transformed value for each component.
  /// @return A matrix where each component is the result of applying `func` to the corresponding pair of
  /// input components.
  template <IsArithmeticT TComponentA, IsArithmeticT TComponentB, vec_length_t CL, vec_length_t RL,
            typename TFunc>
  constexpr auto Zip(const matrix_t<TComponentA, CL, RL> &a, const matrix_t<TComponentB, CL, RL> &b,
                     TFunc func) noexcept
    -> matrix_t<decltype(func(declval<TComponentA>(), declval<TComponentB>())), CL, RL>
  {
    using TReturn = decltype(func(declval<TComponentA>(), declval<TComponentB>()));
    if constexpr (CL == 2 && RL == 2)
    {
      return matrix_t<TReturn, 2, 2>(func(a[0].x, b[0].x), func(a[0].y, b[0].y), func(a[1].x, b[1].x),
                                     func(a[1].y, b[1].y));
    }
    else if constexpr (CL == 3 && RL == 3)
    {
      return matrix_t<TReturn, 3, 3>(func(a[0].x, b[0].x), func(a[0].y, b[0].y), func(a[0].z, b[0].z),
                                     func(a[1].x, b[1].x), func(a[1].y, b[1].y), func(a[1].z, b[1].z),
                                     func(a[2].x, b[2].x), func(a[2].y, b[2].y), func(a[2].z, b[2].z));
    }
    else if constexpr (CL == 4 && RL == 4)
    {
      return matrix_t<TReturn, 4, 4>(
        func(a[0].x, b[0].x), func(a[0].y, b[0].y), func(a[0].z, b[0].z), func(a[0].w, b[0].w),
        func(a[1].x, b[1].x), func(a[1].y, b[1].y), func(a[1].z, b[1].z), func(a[1].w, b[1].w),
        func(a[2].x, b[2].x), func(a[2].y, b[2].y), func(a[2].z, b[2].z), func(a[2].w, b[2].w),
        func(a[3].x, b[3].x), func(a[3].y, b[3].y), func(a[3].z, b[3].z), func(a[3].w, b[3].w));
    }
    else
      static_assert(false, "Unsupported number of rows/columns");
  }

  /// @brief Creates a new matrix from three input matrices by applying a function to each component triplet
  /// of
  /// the input matrices.
  /// @tparam TComponentA The underlying arithmetic type of the first input matrix.
  /// @tparam TComponentB The underlying arithmetic type of the second input matrix.
  /// @tparam TComponentC The underlying arithmetic type of the third input matrix.
  /// @tparam CL The column length of the input matrix.
  /// @tparam RL The row length of the input matrix.
  /// @param v The input matrix.
  /// @param func A callable object or lambda that returns the transformed value for each component.
  /// @return A matrix where each component is the result of applying `func` to the corresponding pair of
  /// input components.
  template <IsArithmeticT TComponentA, IsArithmeticT TComponentB, IsArithmeticT TComponentC, vec_length_t CL,
            vec_length_t RL, typename TFunc>
  constexpr auto Zip(const matrix_t<TComponentA, CL, RL> &a, const matrix_t<TComponentB, CL, RL> &b,
                     const matrix_t<TComponentC, CL, RL> &c, TFunc func) noexcept
    -> matrix_t<decltype(func(declval<TComponentA>(), declval<TComponentB>(), declval<TComponentC>())), CL,
                RL>
  {
    using TReturn = decltype(func(declval<TComponentA>(), declval<TComponentB>(), declval<TComponentC>()));

    if constexpr (CL == 2 && RL == 2)
    {
      return matrix_t<TReturn, 2, 2>(func(a[0].x, b[0].x, c[0].x), func(a[0].y, b[0].y, c[0].y),
                                     func(a[1].x, b[1].x, c[1].x), func(a[1].y, b[1].y, c[1].y));
    }
    else if constexpr (CL == 3 && RL == 3)
    {
      return matrix_t<TReturn, 3, 3>(
        func(a[0].x, b[0].x, c[0].x), func(a[0].y, b[0].y, c[0].y), func(a[0].z, b[0].z, c[0].z),
        func(a[1].x, b[1].x, c[1].x), func(a[1].y, b[1].y, c[1].y), func(a[1].z, b[1].z, c[1].z),
        func(a[2].x, b[2].x, c[2].x), func(a[2].y, b[2].y, c[2].y), func(a[2].z, b[2].z, c[2].z));
    }
    else if constexpr (CL == 4 && RL == 4)
    {
      return matrix_t<TReturn, 4, 4>(
        func(a[0].x, b[0].x, c[0].x), func(a[0].y, b[0].y, c[0].y), func(a[0].z, b[0].z, c[0].z),
        func(a[0].w, b[0].w, c[0].w), func(a[1].x, b[1].x, c[1].x), func(a[1].y, b[1].y, c[1].y),
        func(a[1].z, b[1].z, c[1].z), func(a[1].w, b[1].w, c[1].w), func(a[2].x, b[2].x, c[2].x),
        func(a[2].y, b[2].y, c[2].y), func(a[2].z, b[2].z, c[2].z), func(a[2].w, b[2].w, c[2].w),
        func(a[3].x, b[3].x, c[3].x), func(a[3].y, b[3].y, c[3].y), func(a[3].z, b[3].z, c[3].z),
        func(a[3].w, b[3].w, c[3].w));
    }
    else
    {
      static_assert(CL > 0 && RL > 0, "Unsupported number of rows/columns");
    }
  }

  /// @brief Computes the sum of all components of the matrix.
  /// @tparam TComponent The underlying arithmetic type of the input matrix.
  /// @tparam CL The column length of the input matrix.
  /// @tparam RL The row length of the input matrix.
  /// @param v The input matrix.
  /// @return The sum of the components of `v`.
  template <IsArithmeticT TComponent, vec_length_t CL, vec_length_t RL>
  NO_DISCARD constexpr TComponent Sum(const matrix_t<TComponent, CL, RL> &v) noexcept
  {
    if constexpr (CL == 2 && RL == 2)
      return TComponent(v[0].x + v[0].y + v[1].x + v[1].y);
    else if constexpr (CL == 3 && RL == 3)
      return TComponent(v[0].x + v[0].y + v[0].z + v[1].x + v[1].y + v[1].z + v[2].x + v[2].y + v[2].z);
    else if constexpr (CL == 4 && RL == 4)
      return TComponent(v[0].x + v[0].y + v[0].z + v[0].w + v[1].x + v[1].y + v[1].z + v[1].w + v[2].x
                        + v[2].y + v[2].z + v[2].w + v[3].x + v[3].y + v[3].z + v[3].w);
    else
      static_assert(false, "Unsupported number of rows/columns");
  }

  /// @brief Computes the sum of all components of the matrix after applying a function to each component.
  /// @tparam TComponent The underlying arithmetic type of the input matrix.
  /// @tparam CL The column length of the input matrix.
  /// @tparam RL The row length of the input matrix.
  /// @param v The input matrix.
  /// @param func A callable object or lambda to transform each component before summing.
  /// @return The sum of the transformed components of `v`.
  template <IsArithmeticT TComponent, vec_length_t CL, vec_length_t RL, IsRegularCallableT<TComponent> TFunc>
  NO_DISCARD constexpr TComponent Sum(const matrix_t<TComponent, CL, RL> &v, TFunc func) noexcept
  {
    if constexpr (CL == 2 && RL == 2)
      return TComponent(func(v[0].x) + func(v[0].y) + func(v[1].x) + func(v[1].y));
    else if constexpr (CL == 3 && RL == 3)
      return TComponent(func(v[0].x) + func(v[0].y) + func(v[0].z) + func(v[1].x) + func(v[1].y)
                        + func(v[1].z) + func(v[2].x) + func(v[2].y) + func(v[2].z));
    else if constexpr (CL == 4 && RL == 4)
      return TComponent(func(v[0].x) + func(v[0].y) + func(v[0].z) + func(v[0].w) + func(v[1].x)
                        + func(v[1].y) + func(v[1].z) + func(v[1].w) + func(v[2].x) + func(v[2].y)
                        + func(v[2].z) + func(v[2].w) + func(v[3].x) + func(v[3].y) + func(v[3].z)
                        + func(v[3].w));
    else
      static_assert(false, "Unsupported number of rows/columns");
  }

  template <IsArithmeticT TComponent, vec_length_t CL, vec_length_t RL>
  NO_DISCARD constexpr matrix_t<TComponent, CL, RL> &Fill(matrix_t<TComponent, CL, RL> &m,
                                                          TComponent v) noexcept
  {
    using mat_col_t = matrix_t<TComponent, CL, RL>::column_t;
    if constexpr (CL == 2 && RL == 2)
      m = matrix_t<TComponent, CL, RL>(mat_col_t(v, v), mat_col_t(v, v));
    else if constexpr (CL == 3 && RL == 3)
      m = matrix_t<TComponent, CL, RL>(mat_col_t(v, v, v), mat_col_t(v, v, v), mat_col_t(v, v, v));
    else if constexpr (CL == 4 && RL == 4)
      m =  matrix_t<TComponent, CL, RL>(mat_col_t(v, v, v, v), mat_col_t(v, v, v, v),
                                          mat_col_t(v, v, v, v), mat_col_t(v, v, v, v));
    else
      static_assert(false, "Unsupported number of cols/rows.");

    return m;
  }
}