#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Matrices/Base.hpp"
#include "MTL/Vectors/Base.hpp"

namespace Krys::MTL
{
  template <IsArithmeticT TComponent, vec_length_t RL, vec_length_t CL>
  NO_DISCARD constexpr matrix_t<TComponent, RL, CL> OuterProduct(const vector_t<TComponent, RL> &a,
                                                                 const vector_t<TComponent, CL> &b) noexcept
  {
    matrix_t<TComponent, RL, CL> mat;
    for (vec_length_t i = 0; i < b.GetLength(); ++i)
      mat[i] = a * b[i];
    return mat;
  }
}