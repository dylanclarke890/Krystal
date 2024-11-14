#pragma once

#include "Base/Concepts.hpp"
#include "Base/Types.hpp"
#include "Core/Maths/Vectors/Base.hpp"

namespace Krys::Maths
{
  template <IsArithmeticT TComponent, vec_length_t RowLength, vec_length_t ColLength>
  struct Matrix;

  template <typename TMatrix, typename TComponent>
  concept IsMatrix =
    IsComparableT<TMatrix> && IsArithmeticT<TComponent> && SupportsArithmeticOperations<TMatrix, TComponent>
    && IsAddableT<TMatrix, TMatrix> && IsSubtractableT<TMatrix, TMatrix> && IsMultipliableT<TMatrix, TMatrix>
    && requires(TMatrix mat) {
         { mat.GetColLength() } -> std::same_as<vec_length_t>;
         { mat.GetRowLength() } -> std::same_as<vec_length_t>;
       };

  template <typename TMatrix, typename TComponent>
  concept IsSquareMatrix = IsMatrix<TMatrix, TComponent> && requires(TMatrix mat) {
    { TMatrix::I } -> std::same_as<const TMatrix &>;
  };
}