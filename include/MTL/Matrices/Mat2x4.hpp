#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"
#include "Core/Debug/Macros.hpp"
#include "MTL/Matrices/Base.hpp"
#include "MTL/Matrices/ImplMacros.hpp"
#include "MTL/Vectors/Base.hpp"
#include "MTL/Vectors/Vec2.hpp"

namespace Krys
{
  template <IsArithmeticT TComponent>
  using mat2x4_t = MTL::Matrix<TComponent, 2, 4>;
  using Mat2x4 = mat2x4_t<float>;

  namespace MTL
  {
    template <IsArithmeticT TComponent>
    struct Matrix<TComponent, 2, 4>
    {
      KRYS_MATRIX_PROPERTIES(2, 4);

    public:
      KRYS_MATRIX_FOUR_COLUMNS_COMMON_CONSTRUCTORS()
      KRYS_MATRIX_ELEMENT_ACCESS()
      KRYS_MATRIX_FOUR_COLUMNS_ASSIGNMENT()
      KRYS_MATRIX_FOUR_COLUMNS_EQUALITY()
      KRYS_MATRIX_FOUR_COLUMNS_ADDITION()
      KRYS_MATRIX_FOUR_COLUMNS_SUBTRACTION()
      KRYS_MATRIX_FOUR_COLUMNS_COMMON_MULTIPLICATION()
      KRYS_MATRIX_FOUR_COLUMNS_DIVISION()
      KRYS_MATRIX_FOUR_COLUMNS_UNARY()
      KRYS_MATRIX_FOUR_COLUMNS_BITWISE_SHIFT()
      KRYS_MATRIX_FOUR_COLUMNS_BITWISE_OR()
      KRYS_MATRIX_FOUR_COLUMNS_BITWISE_XOR()
      KRYS_MATRIX_FOUR_COLUMNS_BITWISE_NOT()
      KRYS_MATRIX_FOUR_COLUMNS_BITWISE_AND()

#pragma region Constructors

      explicit constexpr Matrix(component_t scalar) noexcept
          : _values {column_t(scalar), column_t(scalar), column_t(scalar), column_t(scalar)}
      {
      }

      explicit constexpr Matrix(component_t x0, component_t y0, component_t x1, component_t y1,
                                component_t x2, component_t y2, component_t x3, component_t y3) noexcept
          : _values {column_t(x0, y0), column_t(x1, y1), column_t(x2, y2), column_t(x3, y3)}
      {
      }

#pragma endregion Constructors

#pragma region Multiplication

      NO_DISCARD constexpr mat_t operator*(const mat_t &other) const noexcept
      {
        const column_t &a0 = _values[0];
        const column_t &a1 = _values[1];
        const column_t &b0 = other._values[0];
        const column_t &b1 = other._values[1];

        const column_t c0 = column_t(a0[0] * b0[0] + a1[0] * b0[1], // row 1, col 1
                                     a0[1] * b0[0] + a1[1] * b0[1]  // row 2, col 1
        );

        const column_t c1 = column_t(a0[0] * b1[0] + a1[0] * b1[1], // row 1, col 2
                                     a0[1] * b1[0] + a1[1] * b1[1]  // row 2, col 2
        );

        return mat_t(c0, c1);
      }

      NO_DISCARD constexpr column_t operator*(const column_t &vector) const noexcept
      {
        // Matrix columns
        const column_t &col0 = _values[0];
        const column_t &col1 = _values[1];

        // Resulting vector is the dot product of rows (implicitly derived) and the input vector
        return column_t(col0[0] * vector[0] + col1[0] * vector[1], // Row 1
                        col0[1] * vector[0] + col1[1] * vector[1]  // Row 2
        );
      }

#pragma endregion Multiplication
    };
  }
}