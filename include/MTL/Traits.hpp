#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Matrices/Base.hpp"
#include "MTL/Vectors/Base.hpp"

namespace Krys::MTL
{
  template <IsArithmeticT TComponent>
  struct Traits
  {
    static constexpr bool IsVec = false;
    static constexpr bool IsMat = false;
    static constexpr vec_length_t TotalComponents = 1;
  };

  template <IsArithmeticT TComponent, vec_length_t L>
  struct Traits<vector_t<TComponent, L>>
  {
    static constexpr bool IsVec = false;
    static constexpr bool IsMat = false;
    static constexpr vec_length_t TotalComponents = L;
  };

  template <IsArithmeticT TComponent, vec_length_t RL, vec_length_t CL>
  struct Traits<matrix_t<TComponent, RL, CL>>
  {
    static constexpr bool IsVec = false;
    static constexpr bool IsMat = false;
    static constexpr vec_length_t TotalComponents = RL * CL;
  };
}