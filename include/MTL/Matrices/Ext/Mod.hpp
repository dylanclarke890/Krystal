#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Common/Mod.hpp"
#include "MTL/Matrices/Base.hpp"
#include "MTL/Matrices/Ext/Algorithms.hpp"

namespace Krys::MTL
{
  /// @brief Computes the modulus of each component in the input matrix.
  /// @tparam TComponent An arithmetic type.
  /// @tparam CL The column length of the matrix.
  /// @tparam RL The row length of the matrix.
  /// @param m The input matrix.
  /// @returns A matrix where each component is the modulus of the corresponding input component.
  template <IsArithmeticT TComponent, vec_length_t CL, vec_length_t RL>
  NO_DISCARD constexpr matrix_t<TComponent, CL, RL> Mod(const matrix_t<TComponent, CL, RL> &a,
                                                        const matrix_t<TComponent, CL, RL> &b) noexcept
  {
    return MTL::Zip(a, b, [](TComponent x, TComponent y) -> TComponent { return MTL::Mod(x, y); });
  }
}