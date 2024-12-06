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
  /// @tparam RL The row length of the matrices.
  /// @tparam CL The column length of the matrices.
  /// @param value The input matrix to clamp.
  /// @param min The matrix containing the minimum values.
  /// @param max The matrix containing the maximum values.
  /// @return A matrix where each component is clamped between the corresponding components of `min` and
  /// `max`.
  template <IsArithmeticT TComponent, vec_length_t RL, vec_length_t CL>
  NO_DISCARD constexpr auto Clamp(const matrix_t<TComponent, RL, CL> &value,
                                  const matrix_t<TComponent, RL, CL> &min,
                                  const matrix_t<TComponent, RL, CL> &max) noexcept
  {
    return MTL::Zip(value, min, max, [](TComponent v, TComponent lo, TComponent hi) -> TComponent
                    { return MTL::Clamp(v, lo, hi); });
  }

  /// @brief Clamps each component of the matrix between the scalar values `min` and `max`.
  /// @tparam TComponent The underlying arithmetic type of the matrix.
  /// @tparam RL The row length of the matrix.
  /// @tparam CL The column length of the matrix.
  /// @param value The input matrix to clamp.
  /// @param min The minimum scalar value for clamping.
  /// @param max The maximum scalar value for clamping.
  /// @return A matrix where each component is clamped between `min` and `max`.
  template <IsArithmeticT TComponent, vec_length_t RL, vec_length_t CL>
  NO_DISCARD constexpr auto Clamp(const matrix_t<TComponent, RL, CL> &value, TComponent min,
                                  TComponent max) noexcept
  {
    return MTL::MapEach(value, [&min, &max](TComponent v) { return MTL::Clamp(v, min, max); });
  }
}
