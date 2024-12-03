#pragma once

#include "Base/Concepts.hpp"
#include "Base/Types.hpp"
#include "MTL/Vectors/Base.hpp"

namespace Krys::MTL
{
  template <IsArithmeticT TComponent, vec_length_t RowLength, vec_length_t ColLength>
  struct Matrix;

  template <IsArithmeticT TComponent, vec_length_t RowLength, vec_length_t ColLength>
  using matrix_t = Matrix<TComponent, RowLength, ColLength>;

  template <typename TMatrix, typename TComponent>
  concept IsMatrix =
    IsComparableT<TMatrix> && IsArithmeticT<TComponent> && SupportsArithmeticOperations<TMatrix, TComponent>
    && IsAddableT<TMatrix, TMatrix> && IsSubtractableT<TMatrix, TMatrix> && IsMultipliableT<TMatrix, TMatrix>
    && requires(TMatrix mat) {
         { mat.GetColLength() } -> std::same_as<vec_length_t>;
         { mat.GetRowLength() } -> std::same_as<vec_length_t>;
       };
}
