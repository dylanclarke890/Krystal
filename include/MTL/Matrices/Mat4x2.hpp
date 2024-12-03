#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"
#include "Core/Debug/Macros.hpp"
#include "MTL/Matrices/Base.hpp"
#include "MTL/Matrices/ImplMacros.hpp"
#include "MTL/Vectors/Base.hpp"
#include "MTL/Vectors/Vec4.hpp"

namespace Krys
{
  template <IsArithmeticT TComponent>
  using mat4x2_t = MTL::Matrix<TComponent, 4, 2>;
  using Mat4x2 = mat4x2_t<float>;

  namespace MTL
  {
    template <IsArithmeticT TComponent>
    struct Matrix<TComponent, 4, 2>
    {
      KRYS_MATRIX_PROPERTIES(4, 2);

    public:
      KRYS_MATRIX_TWO_COLUMNS_COMMON_CONSTRUCTORS()
      KRYS_MATRIX_ELEMENT_ACCESS()
      KRYS_MATRIX_TWO_COLUMNS_ASSIGNMENT()
      KRYS_MATRIX_TWO_COLUMNS_EQUALITY()
      KRYS_MATRIX_TWO_COLUMNS_ADDITION()
      KRYS_MATRIX_TWO_COLUMNS_SUBTRACTION()
      KRYS_MATRIX_TWO_COLUMNS_COMMON_MULTIPLICATION()
      KRYS_MATRIX_TWO_COLUMNS_DIVISION()
      KRYS_MATRIX_TWO_COLUMNS_UNARY()

      explicit constexpr Matrix(component_t scalar) noexcept : _values {column_t(scalar), column_t(scalar)}
      {
      }

      explicit constexpr Matrix(component_t x0, component_t y0, component_t z0, component_t w0,
                                component_t x1, component_t y1, component_t z1, component_t w1) noexcept
          : _values {column_t(x0, y0, z0, w0), column_t(x1, y1, z1, w1)}
      {
      }

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
    };
  }
}