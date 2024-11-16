#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"
#include "Core/Maths/Matrices/Algorithms.hpp"
#include "Core/Maths/Matrices/Base.hpp"
#include "Core/Maths/Scalars/Limits.hpp"

namespace Krys::MTL
{
#pragma region Min

  /// @brief Performs a component-wise minimum operation between two matrices.
  /// @tparam TComponent The underlying arithmetic type of the matrices.
  /// @tparam CL The column length of the matrices.
  /// @tparam RL The row length of the matrices.
  /// @param a The first input matrix.
  /// @param b The second input matrix.
  /// @return A matrix where each component is the smaller of the corresponding components of `a` and `b`.
  template <IsArithmeticT TComponent, vec_length_t CL, vec_length_t RL>
  constexpr NO_DISCARD matrix_t<TComponent, CL, RL> Min(const matrix_t<TComponent, CL, RL> &a,
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
  constexpr NO_DISCARD matrix_t<TComponent, CL, RL> Min(const matrix_t<TComponent, CL, RL> &a,
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
  constexpr NO_DISCARD matrix_t<TComponent, CL, RL>
    Min(const matrix_t<TComponent, CL, RL> &a, const matrix_t<TComponent, CL, RL> &b,
        const matrix_t<TComponent, CL, RL> &c, const matrix_t<TComponent, CL, RL> &d) noexcept
  {
    using T = TComponent;
    return MTL::Zip<T, T, T, T, CL, RL>(a, b, c, d,
                                        [](T x, T y, T z, T w) -> T { return MTL::Min(x, y, z, w); });
  }

#pragma endregion Min

#pragma region FMin

  /// @brief Performs a component-wise minimum operation between two floating point matrices, ignoring NaN.
  /// @tparam TComponent The underlying floating-point type of the matrices.
  /// @tparam CL The column length of the matrices.
  /// @tparam RL The row length of the matrices.
  /// @param a The first input matrix.
  /// @param b The second input matrix.
  /// @return A matrix where each component is the smaller of the corresponding components of `a` and `b`, or
  /// `b` if `a` is NaN.
  template <IsFloatingPointT TComponent, vec_length_t CL, vec_length_t RL>
  constexpr NO_DISCARD matrix_t<TComponent, CL, RL> FMin(const matrix_t<TComponent, CL, RL> &a,
                                                         const matrix_t<TComponent, CL, RL> &b) noexcept
  {
    using T = TComponent;
    return MTL::Zip<T, T, CL, RL>(a, b, [](T x, T y) -> T { return MTL::FMin(x, y); });
  }

  /// @brief Performs a component-wise minimum operation between three floating point matrices, ignoring NaN.
  /// @tparam TComponent The underlying floating-point type of the matrices.
  /// @tparam CL The column length of the matrices.
  /// @tparam RL The row length of the matrices.
  /// @param a The first input matrix.
  /// @param b The second input matrix.
  /// @param c The third input matrix.
  /// @return A matrix where each component is the smallest of the corresponding components of `a`, `b` and
  /// `c`, ignoring NaN.
  template <IsFloatingPointT TComponent, vec_length_t CL, vec_length_t RL>
  constexpr NO_DISCARD matrix_t<TComponent, CL, RL> FMin(const matrix_t<TComponent, CL, RL> &a,
                                                         const matrix_t<TComponent, CL, RL> &b,
                                                         const matrix_t<TComponent, CL, RL> &c) noexcept
  {
    using T = TComponent;
    return MTL::Zip<T, T, T, CL, RL>(a, b, c, [](T x, T y, T z) -> T { return MTL::FMin(x, y, z); });
  }

  /// @brief Performs a component-wise minimum operation between four floating point matrices, ignoring NaN.
  /// @tparam TComponent The underlying floating-point type of the matrices.
  /// @tparam CL The column length of the matrices.
  /// @tparam RL The row length of the matrices.
  /// @param a The first input matrix.
  /// @param b The second input matrix.
  /// @param c The third input matrix.
  /// @param d The fourth input matrix.
  /// @return A matrix where each component is the smallest of the corresponding components of `a`, `b`, `c`
  /// and `d`, ignoring NaN.
  template <IsFloatingPointT TComponent, vec_length_t CL, vec_length_t RL>
  constexpr NO_DISCARD matrix_t<TComponent, CL, RL>
    FMin(const matrix_t<TComponent, CL, RL> &a, const matrix_t<TComponent, CL, RL> &b,
         const matrix_t<TComponent, CL, RL> &c, const matrix_t<TComponent, CL, RL> &d) noexcept
  {
    using T = TComponent;
    return MTL::Zip<T, T, T, T, CL, RL>(a, b, c, d,
                                        [](T x, T y, T z, T w) -> T { return MTL::FMin(x, y, z, w); });
  }

#pragma endregion FMin

#pragma region Max

  /// @brief Performs a component-wise maximum operation between two matrices.
  /// @tparam TComponent The underlying arithmetic type of the matrices.
  /// @tparam CL The column length of the matrices.
  /// @tparam RL The row length of the matrices.
  /// @param a The first input matrix.
  /// @param b The second input matrix.
  /// @return A matrix where each component is the larger of the corresponding components of `a` and `b`.
  template <IsArithmeticT TComponent, vec_length_t CL, vec_length_t RL>
  constexpr NO_DISCARD matrix_t<TComponent, CL, RL> Max(const matrix_t<TComponent, CL, RL> &a,
                                                        const matrix_t<TComponent, CL, RL> &b) noexcept
  {
    using T = TComponent;
    return MTL::Zip<T, T, CL, RL>(a, b, [](T x, T y) -> T { return MTL::Max(x, y); });
  }

  /// @brief Performs a component-wise maximum operation between three matrices.
  /// @tparam TComponent The underlying arithmetic type of the matrices.
  /// @tparam CL The column length of the matrices.
  /// @tparam RL The row length of the matrices.
  /// @param a The first input matrix.
  /// @param b The second input matrix.
  /// @param c The third input matrix.
  /// @return A matrix where each component is the largest of the corresponding components of `a`, `b` and
  /// `c`.
  template <IsArithmeticT TComponent, vec_length_t CL, vec_length_t RL>
  constexpr NO_DISCARD matrix_t<TComponent, CL, RL> Max(const matrix_t<TComponent, CL, RL> &a,
                                                        const matrix_t<TComponent, CL, RL> &b,
                                                        const matrix_t<TComponent, CL, RL> &c) noexcept
  {
    using T = TComponent;
    return MTL::Zip<T, T, T, CL, RL>(a, b, c, [](T x, T y, T z) -> T { return MTL::Max(x, y, z); });
  }

  /// @brief Performs a component-wise maximum operation between four matrices.
  /// @tparam TComponent The underlying arithmetic type of the matrices.
  /// @tparam CL The column length of the matrices.
  /// @tparam RL The row length of the matrices.
  /// @param a The first input matrix.
  /// @param b The second input matrix.
  /// @param c The third input matrix.
  /// @param d The fourth input matrix.
  /// @return A matrix where each component is the largest of the corresponding components of `a`, `b`, `c`
  /// and `d`.
  template <IsArithmeticT TComponent, vec_length_t CL, vec_length_t RL>
  constexpr NO_DISCARD matrix_t<TComponent, CL, RL>
    Max(const matrix_t<TComponent, CL, RL> &a, const matrix_t<TComponent, CL, RL> &b,
        const matrix_t<TComponent, CL, RL> &c, const matrix_t<TComponent, CL, RL> &d) noexcept
  {
    using T = TComponent;
    return MTL::Zip<T, T, T, T, CL, RL>(a, b, c, d,
                                        [](T x, T y, T z, T w) -> T { return MTL::Max(x, y, z, w); });
  }

#pragma endregion Max

#pragma region FMax

  /// @brief Performs a component-wise maximum operation between two floating point matrices, ignoring NaN.
  /// @tparam TComponent The underlying arithmetic type of the matrices.
  /// @tparam CL The column length of the matrices.
  /// @tparam RL The row length of the matrices.
  /// @param a The first input matrix.
  /// @param b The second input matrix.
  /// @return A matrix where each component is the larger of the corresponding components of `a` and `b`.
  template <IsFloatingPointT TComponent, vec_length_t CL, vec_length_t RL>
  constexpr NO_DISCARD matrix_t<TComponent, CL, RL> FMax(const matrix_t<TComponent, CL, RL> &a,
                                                         const matrix_t<TComponent, CL, RL> &b) noexcept
  {
    using T = TComponent;
    return MTL::Zip<T, T, CL, RL>(a, b, [](T x, T y) -> T { return MTL::FMax(x, y); });
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
  constexpr NO_DISCARD matrix_t<TComponent, CL, RL> FMax(const matrix_t<TComponent, CL, RL> &a,
                                                         const matrix_t<TComponent, CL, RL> &b,
                                                         const matrix_t<TComponent, CL, RL> &c) noexcept
  {
    using T = TComponent;
    return MTL::Zip<T, T, T, CL, RL>(a, b, c, [](T x, T y, T z) -> T { return MTL::FMax(x, y, z); });
  }

  /// @brief Performs a component-wise maximum operation between four floating point matrices, ignoring NaN.
  /// @tparam TComponent The underlying floating-point type of the matrices.
  /// @tparam CL The column length of the matrices.
  /// @tparam RL The row length of the matrices.
  /// @param a The first input matrix.
  /// @param b The second input matrix.
  /// @param c The third input matrix.
  /// @param d The fourth input matrix.
  /// @return A matrix where each component is the largest of the corresponding components of `a`, `b`, `c`
  /// and `d`, ignoring NaN.
  template <IsFloatingPointT TComponent, vec_length_t CL, vec_length_t RL>
  constexpr NO_DISCARD matrix_t<TComponent, CL, RL>
    FMax(const matrix_t<TComponent, CL, RL> &a, const matrix_t<TComponent, CL, RL> &b,
         const matrix_t<TComponent, CL, RL> &c, const matrix_t<TComponent, CL, RL> &d) noexcept
  {
    using T = TComponent;
    return MTL::Zip<T, T, T, T, CL, RL>(a, b, c, d,
                                        [](T x, T y, T z, T w) -> T { return MTL::FMax(x, y, z, w); });
  }

#pragma endregion FMax

#pragma region Clamp

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
  constexpr NO_DISCARD matrix_t<TComponent, CL, RL> Clamp(const matrix_t<TComponent, CL, RL> &value,
                                                          const matrix_t<TComponent, CL, RL> &min,
                                                          const matrix_t<TComponent, CL, RL> &max) noexcept
  {
    using T = TComponent;
    return MTL::Zip<T, T, T, CL, RL>(value, min, max,
                                     [](T v, T mn, T mx) -> T { return MTL::Min(MTL::Max(v, mn), mx); });
  }

#pragma endregion Clamp
}
