#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Common/Rounding.hpp"
#include "MTL/Matrices/Base.hpp"
#include "MTL/Matrices/Ext/Algorithms.hpp"

namespace Krys::MTL
{
  /// @brief Computes the smallest integer not smaller than each component of the matrix.
  /// @tparam TComponent The underlying floating-point type of the matrix.
  /// @tparam RL The row length of the matrix.
  /// @tparam CL The column length of the matrix.
  /// @param m The input matrix.
  /// @returns A matrix with each component rounded up to the smallest integer.
  template <IsFloatingPointT TComponent, vec_length_t RL, vec_length_t CL>
  NO_DISCARD constexpr auto Ceil(const matrix_t<TComponent, RL, CL> &m) noexcept
  {
    return MTL::MapEach(m, [](TComponent x) -> TComponent { return MTL::Ceil(x); });
  }

  /// @brief Computes the largest integer not greater than each component of the matrix.
  /// @tparam TComponent The underlying floating-point type of the matrix.
  /// @tparam CL The column length of the matrix.
  /// @tparam RL The row length of the matrix.
  /// @param m The input matrix.
  /// @returns A matrix with each component rounded down to the largest integer.
  template <IsFloatingPointT TComponent, vec_length_t RL, vec_length_t CL>
  NO_DISCARD constexpr auto Floor(const matrix_t<TComponent, RL, CL> &m) noexcept
  {
    return MTL::MapEach(m, [](TComponent x) -> TComponent { return MTL::Floor(x); });
  }

  /// @brief Rounds each component of the matrix to the nearest integer. Halfway cases are rounded away from
  /// zero.
  /// @tparam TComponent The underlying floating-point type of the matrix.
  /// @tparam CL The column length of the matrix.
  /// @tparam RL The row length of the matrix.
  /// @param m The input matrix.
  /// @returns A matrix with each component rounded to the nearest integer.
  template <IsFloatingPointT TComponent, vec_length_t RL, vec_length_t CL>
  NO_DISCARD constexpr auto Round(const matrix_t<TComponent, RL, CL> &m) noexcept
  {
    return MTL::MapEach(m, [](TComponent x) -> TComponent { return MTL::Round(x); });
  }

  /// @brief Computes the nearest integer not greater in magnitude than each component of the matrix.
  /// @tparam TComponent The underlying floating-point type of the matrix.
  /// @tparam CL The column length of the matrix.
  /// @tparam RL The row length of the matrix.
  /// @param m The input matrix.
  /// @returns A matrix with each component truncated to the nearest integer not greater in magnitude.
  template <IsFloatingPointT TComponent, vec_length_t RL, vec_length_t CL>
  NO_DISCARD constexpr auto Trunc(const matrix_t<TComponent, RL, CL> &m) noexcept
  {
    return MTL::MapEach(m, [](TComponent x) -> TComponent { return MTL::Trunc(x); });
  }
}
