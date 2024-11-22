#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"
#include "Core/Maths/Matrices/Base.hpp"

namespace Krys::MTL
{
  /// @brief Checks if any of the components in `v` satisfy the predicate.
  /// @tparam TComponent The underlying arithmetic type of the input matrix.
  /// @tparam CL The column length of the input matrix.
  /// @tparam RL The row length of the input matrix.
  /// @param v The matrix to check.
  /// @returns True if any of the components satified the predicate, false otherwise.
  template <IsArithmeticT TComponent, vec_length_t CL, vec_length_t RL>
  constexpr bool AnyOf(const matrix_t<TComponent, CL, RL> &v, Func<bool(TComponent)> predicate) noexcept;

  /// @brief Checks if all of the components in `v` satisfy the predicate.
  /// @tparam TComponent The underlying arithmetic type of the input matrix.
  /// @tparam CL The column length of the input matrix.
  /// @tparam RL The row length of the input matrix.
  /// @param v The matrix to check.
  /// @returns True if all of the components satified the predicate, false otherwise.
  template <IsArithmeticT TComponent, vec_length_t CL, vec_length_t RL>
  constexpr bool AllOf(const matrix_t<TComponent, CL, RL> &v, Func<bool(TComponent)> predicate) noexcept;

  /// @brief Checks if none of the components in `v` satisfy the predicate.
  /// @tparam TComponent The underlying arithmetic type of the input matrix.
  /// @tparam CL The column length of the input matrix.
  /// @tparam RL The row length of the input matrix.
  /// @param v The matrix to check.
  /// @returns True if none of the components satified the predicate, false otherwise.
  template <IsArithmeticT TComponent, vec_length_t CL, vec_length_t RL>
  constexpr bool NoneOf(const matrix_t<TComponent, CL, RL> &v, Func<bool(TComponent)> predicate) noexcept;

#pragma region AnyOf

  template <IsArithmeticT TComponent>
  constexpr bool AnyOf(const matrix_t<TComponent, 2, 2> &v, Func<bool(TComponent)> predicate) noexcept
  {
    return predicate(v[0].x) || predicate(v[0].y) || predicate(v[1].x) || predicate(v[1].y);
  }

  template <IsArithmeticT TComponent>
  constexpr bool AnyOf(const matrix_t<TComponent, 3, 3> &v, Func<bool(TComponent)> predicate) noexcept
  {
    return predicate(v[0].x) || predicate(v[0].y) || predicate(v[0].z) || predicate(v[1].x)
           || predicate(v[1].y) || predicate(v[1].z) || predicate(v[2].x) || predicate(v[2].y)
           || predicate(v[2].z);
  }

  template <IsArithmeticT TComponent>
  constexpr bool AnyOf(const matrix_t<TComponent, 4, 4> &v, Func<bool(TComponent)> predicate) noexcept
  {
    return predicate(v[0].x) || predicate(v[0].y) || predicate(v[0].z) || predicate(v[0].w)
           || predicate(v[1].x) || predicate(v[1].y) || predicate(v[1].z) || predicate(v[1].w)
           || predicate(v[2].x) || predicate(v[2].y) || predicate(v[2].z) || predicate(v[2].w)
           || predicate(v[3].x) || predicate(v[3].y) || predicate(v[3].z) || predicate(v[3].w);
  }

#pragma endregion AnyOf

#pragma region AllOf

  template <IsArithmeticT TComponent>
  constexpr bool AllOf(const matrix_t<TComponent, 2, 2> &v, Func<bool(TComponent)> predicate) noexcept
  {
    return predicate(v[0].x) && predicate(v[0].y) && predicate(v[1].x) && predicate(v[1].y);
  }

  template <IsArithmeticT TComponent>
  constexpr bool AllOf(const matrix_t<TComponent, 3, 3> &v, Func<bool(TComponent)> predicate) noexcept
  {
    return predicate(v[0].x) && predicate(v[0].y) && predicate(v[0].z) && predicate(v[1].x)
           && predicate(v[1].y) && predicate(v[1].z) && predicate(v[2].x) && predicate(v[2].y)
           && predicate(v[2].z);
  }

  template <IsArithmeticT TComponent>
  constexpr bool AllOf(const matrix_t<TComponent, 4, 4> &v, Func<bool(TComponent)> predicate) noexcept
  {
    return predicate(v[0].x) && predicate(v[0].y) && predicate(v[0].z) && predicate(v[0].w)
           && predicate(v[1].x) && predicate(v[1].y) && predicate(v[1].z) && predicate(v[1].w)
           && predicate(v[2].x) && predicate(v[2].y) && predicate(v[2].z) && predicate(v[2].w)
           && predicate(v[3].x) && predicate(v[3].y) && predicate(v[3].z) && predicate(v[3].w);
  }

#pragma endregion AllOf

#pragma region NoneOf

  template <IsArithmeticT TComponent>
  constexpr bool NoneOf(const matrix_t<TComponent, 2, 2> &v, Func<bool(TComponent)> predicate) noexcept
  {
    return !predicate(v[0].x) && !predicate(v[0].y) && !predicate(v[1].x) && !predicate(v[1].y);
  }

  template <IsArithmeticT TComponent>
  constexpr bool NoneOf(const matrix_t<TComponent, 3, 3> &v, Func<bool(TComponent)> predicate) noexcept
  {
    return !predicate(v[0].x) && !predicate(v[0].y) && !predicate(v[0].z) && !predicate(v[1].x)
           && !predicate(v[1].y) && !predicate(v[1].z) && !predicate(v[2].x) && !predicate(v[2].y)
           && !predicate(v[2].z);
  }

  template <IsArithmeticT TComponent>
  constexpr bool NoneOf(const matrix_t<TComponent, 4, 4> &v, Func<bool(TComponent)> predicate) noexcept
  {
    return !predicate(v[0].x) && !predicate(v[0].y) && !predicate(v[0].z) && !predicate(v[0].w)
           && !predicate(v[1].x) && !predicate(v[1].y) && !predicate(v[1].z) && !predicate(v[1].w)
           && !predicate(v[2].x) && !predicate(v[2].y) && !predicate(v[2].z) && !predicate(v[2].w)
           && !predicate(v[3].x) && !predicate(v[3].y) && !predicate(v[3].z) && !predicate(v[3].w);
  }

#pragma endregion NoneOf
}