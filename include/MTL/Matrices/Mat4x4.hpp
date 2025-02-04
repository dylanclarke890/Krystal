#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"
#include "Debug/Macros.hpp"
#include "MTL/Matrices/_ImplMacros.hpp"
#include "MTL/Matrices/Base.hpp"
#include "MTL/Vectors/Base.hpp"
#include "MTL/Vectors/Vec4.hpp"

namespace Krys
{
  template <IsArithmeticT TComponent>
  using mat4x4_t = MTL::Matrix<TComponent, 4, 4>;
  using Mat4 = mat4x4_t<float>;
  using Mat4x4 = Mat4;

  namespace MTL
  {
    template <IsArithmeticT TComponent>
    struct Matrix<TComponent, 4, 4>
    {
      KRYS_MATRIX_PROPERTIES(4, 4);

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
          : _values {column_t(scalar, component_t(0), component_t(0), component_t(0)),
                     column_t(component_t(0), scalar, component_t(0), component_t(0)),
                     column_t(component_t(0), component_t(0), scalar, component_t(0)),
                     column_t(component_t(0), component_t(0), component_t(0), scalar)}
      {
      }

      explicit constexpr Matrix(component_t x0, component_t y0, component_t z0, component_t w0,
                                component_t x1, component_t y1, component_t z1, component_t w1,
                                component_t x2, component_t y2, component_t z2, component_t w2,
                                component_t x3, component_t y3, component_t z3, component_t w3) noexcept
          : _values {column_t(x0, y0, z0, w0), column_t(x1, y1, z1, w1), column_t(x2, y2, z2, w2),
                     column_t(x3, y3, z3, w3)}
      {
      }

#pragma endregion Constructors

#pragma region Multiplication

      NO_DISCARD constexpr mat_t operator*(const mat_t &other) const noexcept
      {
        const column_t &a0 = _values[0];
        const column_t &a1 = _values[1];
        const column_t &a2 = _values[2];
        const column_t &a3 = _values[3];

        const column_t &b0 = other._values[0];
        const column_t &b1 = other._values[1];
        const column_t &b2 = other._values[2];
        const column_t &b3 = other._values[3];

        column_t c0(a0[0] * b0[0] + a1[0] * b0[1] + a2[0] * b0[2] + a3[0] * b0[3], // Row 1, Col 1
                    a0[1] * b0[0] + a1[1] * b0[1] + a2[1] * b0[2] + a3[1] * b0[3], // Row 2, Col 1
                    a0[2] * b0[0] + a1[2] * b0[1] + a2[2] * b0[2] + a3[2] * b0[3], // Row 3, Col 1
                    a0[3] * b0[0] + a1[3] * b0[1] + a2[3] * b0[2] + a3[3] * b0[3]  // Row 4, Col 1
        );

        column_t c1(a0[0] * b1[0] + a1[0] * b1[1] + a2[0] * b1[2] + a3[0] * b1[3], // Row 1, Col 2
                    a0[1] * b1[0] + a1[1] * b1[1] + a2[1] * b1[2] + a3[1] * b1[3], // Row 2, Col 2
                    a0[2] * b1[0] + a1[2] * b1[1] + a2[2] * b1[2] + a3[2] * b1[3], // Row 3, Col 2
                    a0[3] * b1[0] + a1[3] * b1[1] + a2[3] * b1[2] + a3[3] * b1[3]  // Row 4, Col 2
        );

        column_t c2(a0[0] * b2[0] + a1[0] * b2[1] + a2[0] * b2[2] + a3[0] * b2[3], // Row 1, Col 3
                    a0[1] * b2[0] + a1[1] * b2[1] + a2[1] * b2[2] + a3[1] * b2[3], // Row 2, Col 3
                    a0[2] * b2[0] + a1[2] * b2[1] + a2[2] * b2[2] + a3[2] * b2[3], // Row 3, Col 3
                    a0[3] * b2[0] + a1[3] * b2[1] + a2[3] * b2[2] + a3[3] * b2[3]  // Row 4, Col 3
        );

        column_t c3(a0[0] * b3[0] + a1[0] * b3[1] + a2[0] * b3[2] + a3[0] * b3[3], // Row 1, Col 4
                    a0[1] * b3[0] + a1[1] * b3[1] + a2[1] * b3[2] + a3[1] * b3[3], // Row 2, Col 4
                    a0[2] * b3[0] + a1[2] * b3[1] + a2[2] * b3[2] + a3[2] * b3[3], // Row 3, Col 4
                    a0[3] * b3[0] + a1[3] * b3[1] + a2[3] * b3[2] + a3[3] * b3[3]  // Row 4, Col 4
        );

        return mat_t(c0, c1, c2, c3);
      }

      NO_DISCARD constexpr column_t operator*(const column_t &vector) const noexcept
      {
        const column_t &a0 = _values[0];
        const column_t &a1 = _values[1];
        const column_t &a2 = _values[2];
        const column_t &a3 = _values[3];
        const column_t &v = vector;

        const column_t col = column_t(a0[0] * v[0] + a0[1] * v[1] + a0[2] * v[2]+ a0[3] * v[3],
                                      a1[0] * v[0] + a1[1] * v[1] + a1[2] * v[2]+ a1[3] * v[3],
                                      a2[0] * v[0] + a2[1] * v[1] + a2[2] * v[2]+ a2[3] * v[3],
                                      a3[0] * v[0] + a3[1] * v[1] + a3[2] * v[2]+ a3[3] * v[3]
        );

        return col;
      }

#pragma endregion Multiplication
    };
  }
}