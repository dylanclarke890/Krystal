#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Common/Abs.hpp"
#include "MTL/Matrices/Base.hpp"
#include "MTL/Matrices/Ext/Algorithms.hpp"

namespace Krys::MTL
{
  /// @brief Computes the absolute value of each component in the input matrix.
  /// @tparam TComponent A signed arithmetic type.
  /// @tparam CL The column length of the matrix.
  /// @tparam RL The row length of the matrix.
  /// @param m The input matrix.
  /// @returns A matrix where each component is the absolute value of the corresponding input component.
  template <IsSignedT TComponent, vec_length_t CL, vec_length_t RL>
  NO_DISCARD constexpr auto Abs(const matrix_t<TComponent, CL, RL> &m) noexcept
  {
    return MTL::MapEach(m, [](TComponent x) -> TComponent { return MTL::Abs(x); });
  }
}
