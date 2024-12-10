#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Common/Clamp.hpp"
#include "MTL/Matrices/Base.hpp"
#include "MTL/Matrices/Ext/Clamp.hpp"
#include "MTL/Matrices/Ext/Hadamard.hpp"

namespace Krys::MTL
{
  template <IsArithmeticT TComponent, vec_length_t RL, vec_length_t CL>
  NO_DISCARD constexpr auto Lerp(const matrix_t<TComponent, RL, CL> &x, const matrix_t<TComponent, RL, CL> &y,
                                 const matrix_t<TComponent, RL, CL> &t) noexcept
  {
    matrix_t<TComponent, RL, CL> weight = Clamp(t, TComponent(0), TComponent(1));
    return (Hadamard(x, TComponent(1) - weight)) + (Hadamard(y, weight));
  }

  template <IsArithmeticT TComponent, vec_length_t RL, vec_length_t CL>
  NO_DISCARD constexpr auto Lerp(const matrix_t<TComponent, RL, CL> &x, const matrix_t<TComponent, RL, CL> &y,
                                 TComponent t) noexcept
  {
    t = Clamp(t, TComponent(0), TComponent(1));
    return (x * (TComponent(1) - t)) + (y * t);
  }
}