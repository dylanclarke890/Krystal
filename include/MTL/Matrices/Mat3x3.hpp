#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"
#include "Core/Debug/Macros.hpp"
#include "MTL/Matrices/Base.hpp"
#include "MTL/Matrices/ImplMacros.hpp"
#include "MTL/Vectors/Base.hpp"
#include "MTL/Vectors/Vec3.hpp"

namespace Krys
{
  template <IsArithmeticT TComponent>
  using mat3x3_t = MTL::Matrix<TComponent, 3, 3>;
  using Mat3 = mat3x3_t<float>;
  using Mat3x3 = Mat3;

  namespace MTL
  {
    template <IsArithmeticT TComponent>
    struct Matrix<TComponent, 3, 3>
    {
      KRYS_MATRIX_PROPERTIES(3, 3);

    public:
      KRYS_MATRIX_THREE_COLUMNS_COMMON_CONSTRUCTORS()
      KRYS_MATRIX_ELEMENT_ACCESS()
      KRYS_MATRIX_THREE_COLUMNS_ASSIGNMENT()
      KRYS_MATRIX_THREE_COLUMNS_EQUALITY()
      KRYS_MATRIX_THREE_COLUMNS_ADDITION()
      KRYS_MATRIX_THREE_COLUMNS_SUBTRACTION()
      KRYS_MATRIX_THREE_COLUMNS_COMMON_MULTIPLICATION()
      KRYS_MATRIX_THREE_COLUMNS_DIVISION()
      KRYS_MATRIX_THREE_COLUMNS_UNARY()
      KRYS_MATRIX_THREE_COLUMNS_BITWISE_SHIFT()
      KRYS_MATRIX_THREE_COLUMNS_BITWISE_OR()
      KRYS_MATRIX_THREE_COLUMNS_BITWISE_XOR()
      KRYS_MATRIX_THREE_COLUMNS_BITWISE_NOT()
      KRYS_MATRIX_THREE_COLUMNS_BITWISE_AND()

#pragma region Constructors

      explicit constexpr Matrix(component_t scalar) noexcept
          : _values {column_t(scalar, component_t(0), component_t(0)),
                     column_t(component_t(0), scalar, component_t(0)),
                     column_t(component_t(0), component_t(0), scalar)}
      {
      }

      explicit constexpr Matrix(component_t x0, component_t y0, component_t z0, component_t x1,
                                component_t y1, component_t z1, component_t x2, component_t y2,
                                component_t z2) noexcept
          : _values {column_t(x0, y0, z0), column_t(x1, y1, z1), column_t(x2, y2, z2)}
      {
      }

#pragma endregion Constructors

#pragma region Multiplication

      NO_DISCARD constexpr mat_t operator*(const mat_t &other) const noexcept
      {
        const column_t &a0 = _values[0];
        const column_t &a1 = _values[1];
        const column_t &a2 = _values[2];

        const column_t &b0 = other._values[0];
        const column_t &b1 = other._values[1];
        const column_t &b2 = other._values[2];

        return mat_t(
          column_t(a0[0] * b0[0] + a1[0] * b0[1] + a2[0] * b0[2], a0[1] * b0[0] + a1[1] * b0[1] + a2[1] * b0[2],
                   a0[2] * b0[0] + a1[2] * b0[1] + a2[2] * b0[2]),
          column_t(a0[0] * b1[0] + a1[0] * b1[1] + a2[0] * b1[2], a0[1] * b1[0] + a1[1] * b1[1] + a2[1] * b1[2],
                   a0[2] * b1[0] + a1[2] * b1[1] + a2[2] * b1[2]),
          column_t(a0[0] * b2[0] + a1[0] * b2[1] + a2[0] * b2[2], a0[1] * b2[0] + a1[1] * b2[1] + a2[1] * b2[2],
                   a0[2] * b2[0] + a1[2] * b2[1] + a2[2] * b2[2]));
      }

      NO_DISCARD constexpr column_t operator*(const column_t &vector) const noexcept
      {
        const column_t &a0 = _values[0];
        const column_t &a1 = _values[1];
        const column_t &a2 = _values[2];
        const column_t &v = vector;

        const column_t col = column_t(a0[0] * v[0] + a0[1] * v[1] + a0[2] * v[2],
                                      a1[0] * v[0] + a1[1] * v[1] + a1[2] * v[2],
                                      a2[0] * v[0] + a2[1] * v[1] + a2[2] * v[2] 
        );

        return col;
      }

#pragma endregion Multiplication
    };
  }
}