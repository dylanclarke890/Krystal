#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"
#include "Core/Maths/Matrices/Algorithms.hpp"
#include "Core/Maths/Matrices/Base.hpp"
#include "Core/Maths/Scalars/Arithmetic.hpp"

namespace Krys::MTL
{
  /// @brief Computes the absolute value of each component in the input matrix.
  /// @tparam TComponent A signed arithmetic type.
  /// @tparam CL The column length of the matrix.
  /// @tparam RL The row length of the matrix.
  /// @param m The input matrix.
  /// @returns A matrix where each component is the absolute value of the corresponding input component.
  template <IsSignedT TComponent, vec_length_t CL, vec_length_t RL>
  constexpr NO_DISCARD matrix_t<TComponent, CL, RL> Abs(const matrix_t<TComponent, CL, RL> &m) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, T, CL, RL>(m, [](T x) -> T { return MTL::Abs(x); });
  }

  /// @brief Computes the modulus of each component in the input matrix.
  /// @tparam TComponent An arithmetic type.
  /// @tparam CL The column length of the matrix.
  /// @tparam RL The row length of the matrix.
  /// @param m The input matrix.
  /// @returns A matrix where each component is the modulus of the corresponding input component.
  template <IsArithmeticT TComponent, vec_length_t CL, vec_length_t RL>
  constexpr NO_DISCARD matrix_t<TComponent, CL, RL> Mod(const matrix_t<TComponent, CL, RL> &m) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, T, CL, RL>(m, [](T x) -> T { return MTL::Mod(x); });
  }
}