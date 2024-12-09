#pragma once

#include "Base/Concepts.hpp"
#include "Base/Types.hpp"
#include "MTL/Vectors/Base.hpp"

namespace Krys::MTL
{
#define KRYS_MATRIX_HANDEDNESS_LH 1
#define KRYS_MATRIX_HANDEDNESS_RH 2
#define KRYS_MATRIX_HANDEDNESS KRYS_MATRIX_HANDEDNESS_LH

#define KRYS_MATRIX_DEPTH_RANGE_ZERO_TO_ONE 1
#define KRYS_MATRIX_DEPTH_RANGE_NEGATIVE_ONE_TO_ONE 2
#define KRYS_MATRIX_DEPTH_RANGE KRYS_MATRIX_DEPTH_RANGE_ZERO_TO_ONE

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

#define KRYS_STATIC_ASSERT_MATRIX_SIZE(RL, CL)                                                               \
  static_assert(RL >= 2 && RL <= 4 && CL >= 2 && CL <= 4, "Matrix must be between 2x2 and 4x4.")

#define KRYS_STATIC_ASSERT_SQUARE_MATRIX(RL, CL)                                                             \
  KRYS_STATIC_ASSERT_MATRIX_SIZE(RL, CL);                                                                    \
  static_assert(RL == CL, "Matrix must be square.");
}
