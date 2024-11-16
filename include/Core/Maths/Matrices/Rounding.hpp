#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"
#include "Core/Maths/Matrices/Algorithms.hpp"
#include "Core/Maths/Matrices/Base.hpp"
#include "Core/Maths/Scalars/Rounding.hpp"

namespace Krys::MTL
{
  /// @brief Rounds each component of the matrix to the nearest integer. Halfway cases are rounded away from
  /// zero.
  /// @tparam TComponent The underlying floating-point type of the matrix.
  /// @tparam CL The column length of the matrix.
  /// @tparam RL The row length of the matrix.
  /// @param m The input matrix.
  /// @returns A matrix with each component rounded to the nearest integer.
  template <IsFloatingPointT TComponent, vec_length_t CL, vec_length_t RL>
  constexpr NO_DISCARD matrix_t<TComponent, CL, RL> Round(const matrix_t<TComponent, CL, RL> &m) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, T, CL, RL>(m, [](T val) -> T { return Round(val); });
  }

  /// @brief Computes the largest integer not greater than each component of the matrix.
  /// @tparam TComponent The underlying floating-point type of the matrix.
  /// @tparam CL The column length of the matrix.
  /// @tparam RL The row length of the matrix.
  /// @param m The input matrix.
  /// @returns A matrix with each component rounded down to the largest integer.
  template <IsFloatingPointT TComponent, vec_length_t CL, vec_length_t RL>
  constexpr NO_DISCARD matrix_t<TComponent, CL, RL> Floor(const matrix_t<TComponent, CL, RL> &m) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, T, CL, RL>(m, [](T val) -> T { return Floor(val); });
  }

  /// @brief Computes the smallest integer not smaller than each component of the matrix.
  /// @tparam TComponent The underlying floating-point type of the matrix.
  /// @tparam CL The column length of the matrix.
  /// @tparam RL The row length of the matrix.
  /// @param m The input matrix.
  /// @returns A matrix with each component rounded up to the smallest integer.
  template <IsFloatingPointT TComponent, vec_length_t CL, vec_length_t RL>
  constexpr NO_DISCARD matrix_t<TComponent, CL, RL> Ceil(const matrix_t<TComponent, CL, RL> &m) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, T, CL, RL>(m, [](T val) -> T { return Ceil(val); });
  }

  /// @brief Computes the nearest integer not greater in magnitude than each component of the matrix.
  /// @tparam TComponent The underlying floating-point type of the matrix.
  /// @tparam CL The column length of the matrix.
  /// @tparam RL The row length of the matrix.
  /// @param m The input matrix.
  /// @returns A matrix with each component truncated to the nearest integer not greater in magnitude.
  template <IsFloatingPointT TComponent, vec_length_t CL, vec_length_t RL>
  constexpr NO_DISCARD matrix_t<TComponent, CL, RL> Trunc(const matrix_t<TComponent, CL, RL> &m) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, T, CL, RL>(m, [](T val) -> T { return Trunc(val); });
  }
}
