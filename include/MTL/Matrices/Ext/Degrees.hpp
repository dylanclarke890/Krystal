#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Common/Degrees.hpp"
#include "MTL/Matrices/Base.hpp"
#include "MTL/Matrices/Ext/Algorithms.hpp"

namespace Krys::MTL
{
  /// @brief Converts each component in `v` to degrees.
  /// @tparam TComponent The underlying arithmetic type of the input matrix.
  /// @tparam RL The row length of the input matrix.
  /// @tparam CL The column length of the input matrix.
  /// @param v The input matrix.
  /// @returns The converted matrix.
  template <IsArithmeticT TComponent, vec_length_t RL, vec_length_t CL>
  NO_DISCARD constexpr auto Degrees(const matrix_t<TComponent, RL, CL> &m) noexcept
  {
    return MTL::MapEach(m, [](TComponent x) -> TComponent { return MTL::Degrees(x); });
  }
}
