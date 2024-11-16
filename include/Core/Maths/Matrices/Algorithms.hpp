#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"
#include "Core/Maths/Matrices/Base.hpp"

namespace Krys::MTL
{
  /// @brief Applies a function to each component of the matrix.
  /// @tparam TComponent The underlying arithmetic type of the matrix.
  /// @tparam CL The column length of the input matrix.
  /// @tparam RL The row length of the input matrix.
  /// @param v The input matrix.
  /// @param func A callable object or lambda to be applied to each component.
  template <IsArithmeticT TComponent, vec_length_t CL, vec_length_t RL>
  constexpr void ForEach(const matrix_t<TComponent, CL, RL> &v, Func<void(TComponent v)> func) noexcept;

  /// @brief Creates a new matrix by applying a function to each component of the input matrix.
  /// @tparam TComponentIn The underlying arithmetic type of the input matrix.
  /// @tparam TOut The underlying arithmetic type of the output matrix.
  /// @tparam CL The column length of the input matrix.
  /// @tparam RL The row length of the input matrix.
  /// @param v The input matrix.
  /// @param func A callable object or lambda that returns the transformed value for each component.
  /// @return A matrix where each component is the result of applying `func` to the corresponding input
  /// component.
  template <IsArithmeticT TComponentIn, IsArithmeticT TOut, vec_length_t CL, vec_length_t RL>
  constexpr matrix_t<TOut, CL, RL> Map(const matrix_t<TComponentIn, CL, RL> &v,
                                       Func<TOut(TComponentIn v)> func) noexcept;

  /// @brief Creates a new matrix from two input matrices by applying a function to each component pair of
  /// the input matrices.
  /// @tparam TComponentInA The underlying arithmetic type of the first input matrix.
  /// @tparam TComponentInB The underlying arithmetic type of the second input matrix.
  /// @tparam TOut The underlying arithmetic type of the output matrix.
  /// @tparam CL The column length of the input matrix.
  /// @tparam RL The row length of the input matrix.
  /// @param v The input matrix.
  /// @param func A callable object or lambda that returns the transformed value for each component.
  /// @return A matrix where each component is the result of applying `func` to the corresponding input
  /// component.
  template <IsArithmeticT TComponentInA, IsArithmeticT TComponentInB, IsArithmeticT TOut, vec_length_t CL,
            vec_length_t RL>
  constexpr matrix_t<TOut, CL, RL> Zip(const matrix_t<TComponentInA, CL, RL> &a,
                                       const matrix_t<TComponentInB, CL, RL> &b,
                                       Func<TOut(TComponentInA a, TComponentInB b)> func) noexcept;

  /// @brief Computes the sum of all components of the matrix.
  /// @tparam TComponent The underlying arithmetic type of the input matrix.
  /// @tparam CL The column length of the input matrix.
  /// @tparam RL The row length of the input matrix.
  /// @param v The input matrix.
  /// @return The sum of the components of `v`.
  template <IsArithmeticT TComponent, vec_length_t CL, vec_length_t RL>
  constexpr NO_DISCARD TComponent Sum(const matrix_t<TComponent, CL, RL> &v) noexcept;

  /// @brief Computes the sum of all components of the matrix after applying a function to each component.
  /// @tparam TComponent The underlying arithmetic type of the input matrix.
  /// @tparam CL The column length of the input matrix.
  /// @tparam RL The row length of the input matrix.
  /// @param v The input matrix.
  /// @param func A callable object or lambda to transform each component before summing.
  /// @return The sum of the transformed components of `v`.
  template <IsArithmeticT TComponent, vec_length_t CL, vec_length_t RL>
  constexpr NO_DISCARD TComponent Sum(const matrix_t<TComponent, CL, RL> &v,
                                      Func<TComponent(TComponent v)> func) noexcept;

#pragma region ForEach

  template <IsArithmeticT TComponent>
  constexpr void ForEach(const matrix_t<TComponent, 2, 2> &v, Func<void(TComponent v)> func) noexcept
  {
    func(v[0].x);
    func(v[0].y);

    func(v[1].x);
    func(v[1].y);
  }

  template <IsArithmeticT TComponent>
  constexpr void ForEach(const matrix_t<TComponent, 3, 3> &v, Func<void(TComponent v)> func) noexcept
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

  template <IsArithmeticT TComponent>
  constexpr void ForEach(const matrix_t<TComponent, 4, 4> &v, Func<void(TComponent v)> func) noexcept
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

#pragma endregion ForEach

#pragma region Map

  template <IsArithmeticT TComponentIn, IsArithmeticT TOut>
  constexpr matrix_t<TOut, 2, 2> Map(const matrix_t<TComponentIn, 2, 2> &v,
                                     Func<TOut(TComponentIn v)> func) noexcept
  {
    return matrix_t<TOut, 2, 2>(func(v[0].x), func(v[0].y), func(v[1].x), func(v[1].y));
  }

  template <IsArithmeticT TComponentIn, IsArithmeticT TOut>
  constexpr matrix_t<TOut, 3, 3> Map(const matrix_t<TComponentIn, 3, 3> &v,
                                     Func<TOut(TComponentIn v)> func) noexcept
  {
    return matrix_t<TOut, 3, 3>(func(v[0].x), func(v[0].y), func(v[0].z), func(v[1].x), func(v[1].y),
                                func(v[1].z), func(v[2].x), func(v[2].y), func(v[2].z));
  }

  template <IsArithmeticT TComponentIn, IsArithmeticT TOut>
  constexpr matrix_t<TOut, 4, 4> Map(const matrix_t<TComponentIn, 4, 4> &v,
                                     Func<TOut(TComponentIn v)> func) noexcept
  {
    return matrix_t<TOut, 4, 4>(func(v[0].x), func(v[0].y), func(v[0].z), func(v[0].w), func(v[1].x),
                                func(v[1].y), func(v[1].z), func(v[1].w), func(v[2].x), func(v[2].y),
                                func(v[2].z), func(v[2].w), func(v[3].x), func(v[3].y), func(v[3].z),
                                func(v[3].w));
  }

#pragma endregion Map

#pragma region Zip

  template <IsArithmeticT TComponentInA, IsArithmeticT TComponentInB, IsArithmeticT TOut>
  constexpr matrix_t<TOut, 2, 2> Zip(const matrix_t<TComponentInA, 2, 2> &a,
                                     const matrix_t<TComponentInB, 2, 2> &b,
                                     Func<TOut(TComponentInA a, TComponentInB b)> func) noexcept
  {
    return matrix_t<TOut, 2, 2>(func(a[0].x, b[0].x), func(a[0].y, b[0].y), func(a[1].x, b[1].x),
                                func(a[1].y, b[1].y));
  }

  template <IsArithmeticT TComponentInA, IsArithmeticT TComponentInB, IsArithmeticT TOut>
  constexpr matrix_t<TOut, 3, 3> Zip(const matrix_t<TComponentInA, 3, 3> &a,
                                     const matrix_t<TComponentInB, 3, 3> &b,
                                     Func<TOut(TComponentInA a, TComponentInB b)> func) noexcept
  {
    return matrix_t<TOut, 3, 3>(func(a[0].x, b[0].x), func(a[0].y, b[0].y), func(a[0].z, b[0].z),
                                func(a[1].x, b[1].x), func(a[1].y, b[1].y), func(a[1].z, b[1].z),
                                func(a[2].x, b[2].x), func(a[2].y, b[2].y), func(a[2].z, b[2].z));
  }

  template <IsArithmeticT TComponentInA, IsArithmeticT TComponentInB, IsArithmeticT TOut>
  constexpr matrix_t<TOut, 4, 4> Zip(const matrix_t<TComponentInA, 4, 4> &a,
                                     const matrix_t<TComponentInB, 4, 4> &b,
                                     Func<TOut(TComponentInA a, TComponentInB b)> func) noexcept
  {
    return matrix_t<TOut, 4, 4>(
      func(a[0].x, b[0].x), func(a[0].y, b[0].y), func(a[0].z, b[0].z), func(a[0].w, b[0].w),
      func(a[1].x, b[1].x), func(a[1].y, b[1].y), func(a[1].z, b[1].z), func(a[1].w, b[1].w),
      func(a[2].x, b[2].x), func(a[2].y, b[2].y), func(a[2].z, b[2].z), func(a[2].w, b[2].w),
      func(a[3].x, b[3].x), func(a[3].y, b[3].y), func(a[3].z, b[3].z), func(a[3].w, b[3].w));
  }

#pragma endregion Zip

#pragma region Sum

  template <IsArithmeticT TComponent>
  constexpr NO_DISCARD TComponent Sum(const matrix_t<TComponent, 2, 2> &v) noexcept
  {
    return TComponent(v[0].x + v[0].y + v[1].x + v[1].y);
  }

  template <IsArithmeticT TComponent>
  constexpr NO_DISCARD TComponent Sum(const matrix_t<TComponent, 3, 3> &v) noexcept
  {
    return TComponent(v[0].x + v[0].y + v[0].z + v[1].x + v[1].y + v[1].z + v[2].x + v[2].y + v[2].z);
  }

  template <IsArithmeticT TComponent>
  constexpr NO_DISCARD TComponent Sum(const matrix_t<TComponent, 4, 4> &v) noexcept
  {
    return TComponent(v[0].x + v[0].y + v[0].z + v[0].w + v[1].x + v[1].y + v[1].z + v[1].w + v[2].x + v[2].y
                      + v[2].z + v[2].w + v[3].x + v[3].y + v[3].z + v[3].w);
  }

  template <IsArithmeticT TComponent>
  constexpr NO_DISCARD TComponent Sum(const matrix_t<TComponent, 2, 2> &v,
                                      Func<TComponent(TComponent v)> func) noexcept
  {
    return TComponent(func(v[0].x) + func(v[0].y) + func(v[1].x) + func(v[1].y));
  }

  template <IsArithmeticT TComponent>
  constexpr NO_DISCARD TComponent Sum(const matrix_t<TComponent, 3, 3> &v,
                                      Func<TComponent(TComponent v)> func) noexcept
  {
    return TComponent(func(v[0].x) + func(v[0].y) + func(v[0].z) + func(v[1].x) + func(v[1].y) + func(v[1].z)
                      + func(v[2].x) + func(v[2].y) + func(v[2].z));
  }

  template <IsArithmeticT TComponent>
  constexpr NO_DISCARD TComponent Sum(const matrix_t<TComponent, 4, 4> &v,
                                      Func<TComponent(TComponent v)> func) noexcept
  {
    return TComponent(func(v[0].x) + func(v[0].y) + func(v[0].z) + func(v[0].w) + func(v[1].x) + func(v[1].y)
                      + func(v[1].z) + func(v[1].w) + func(v[2].x) + func(v[2].y) + func(v[2].z)
                      + func(v[2].w) + func(v[3].x) + func(v[3].y) + func(v[3].z) + func(v[3].w));
  }

#pragma endregion Sum
}