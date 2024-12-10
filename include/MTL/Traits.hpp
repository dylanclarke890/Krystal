#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Matrices/Base.hpp"
#include "MTL/Vectors/Base.hpp"

namespace Krys::MTL
{
  template <typename T>
  struct Traits;

  template <IsArithmeticT TComponent, vec_length_t RL, vec_length_t CL>
  struct Traits<matrix_t<TComponent, RL, CL>>
  {
    using ComponentType = TComponent;
    static constexpr bool IsMathsType = true;
    static constexpr bool IsVec = false;
    static constexpr bool IsMat = true;
    static constexpr vec_length_t TotalComponents = RL * CL;

    static constexpr vec_length_t RowLength = RL;
    static constexpr vec_length_t ColLength = CL;
    static constexpr bool IsRowMajor = false;
    static constexpr bool IsSquareMatrix = RL == CL;
  };

  template <IsArithmeticT TComponent, vec_length_t L>
  struct Traits<vector_t<TComponent, L>>
  {
    using ComponentType = TComponent;
    static constexpr bool IsMathsType = true;
    static constexpr bool IsVec = true;
    static constexpr bool IsMat = false;
    static constexpr vec_length_t TotalComponents = L;

    static constexpr vec_length_t Length = L;
    static constexpr bool SupportsCrossProduct = (L == 3);
  };

  template <IsArithmeticT T>
  struct Traits<T>
  {
    using ComponentType = T;
    static constexpr bool IsMathsType = true;
    static constexpr bool IsVec = false;
    static constexpr bool IsMat = false;
    static constexpr vec_length_t TotalComponents = 1;
  };

  template <typename T>
  struct Traits
  {
    static constexpr bool IsMathsType = false;
    static constexpr bool IsVec = false;
    static constexpr bool IsMat = false;
    static constexpr vec_length_t TotalComponents = 0;
  };
}