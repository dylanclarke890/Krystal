#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"
#include "Core/Debug/Macros.hpp"
#include "MTL/Matrices/Base.hpp"
#include "MTL/Vectors/Base.hpp"
#include "MTL/Vectors/Vec3.hpp"

namespace Krys
{
  template <IsArithmeticT TComponent>
  using mat3x3_t = MTL::Matrix<TComponent, 3, 3>;
  using Mat3 = mat3x3_t<float>;
  
  namespace MTL
  {
    template <IsArithmeticT TComponent>
    struct Matrix<TComponent, 3, 3>
    {
    private:
      static constexpr vec_length_t RowLength = 3;
      static constexpr vec_length_t ColLength = 3;

    public:
      using component_t = TComponent;
      using row_t = Vector<component_t, RowLength>;
      using column_t = Vector<component_t, ColLength>;

      using mat_t = Matrix<component_t, RowLength, ColLength>;
      using mat_transpose_t = Matrix<component_t, ColLength, RowLength>;

      static constexpr mat_t I() noexcept
      {
        return mat_t(component_t(1));
      }

    private:
      column_t _values[RowLength];

    public:
#pragma region Construction

      explicit constexpr Matrix() noexcept
          : _values {column_t(component_t(0)), column_t(component_t(0)), column_t(component_t(0))}
      {
      }

      explicit constexpr Matrix(component_t scalar) noexcept
          : _values {column_t(scalar, component_t(0), component_t(0)),
                     column_t(component_t(0), scalar, component_t(0)),
                     column_t(component_t(0), component_t(0), scalar)}
      {
      }

      explicit constexpr Matrix(component_t x0, component_t y0, component_t z0, component_t x1,
                                component_t y1, component_t z1, component_t x2, component_t y2,
                                component_t z2) noexcept
          : _values {column_t(x0, y0, z0), column_t(x1, y1, z0), column_t(x2, y2, z2)}
      {
      }

      explicit constexpr Matrix(const column_t &col0, const column_t &col1, const column_t &col2) noexcept
          : _values {column_t(col0), column_t(col1), column_t(col2)}
      {
      }

      constexpr Matrix(const mat_t &other) noexcept : _values(other._values)
      {
      }

      constexpr Matrix(mat_t &&other) noexcept : _values(std::move(other._values))
      {
      }

#pragma endregion Construction

#pragma region Assignment

      NO_DISCARD constexpr mat_t &operator=(const mat_t &other) noexcept
      {
        _values[0] = other._values[0];
        _values[1] = other._values[1];
        _values[2] = other._values[2];
        return *this;
      }

      NO_DISCARD constexpr mat_t &operator=(mat_t &&other) noexcept
      {
        _values = std::move(other._values);
        return *this;
      }

#pragma endregion Assignment

#pragma region Equality

      constexpr bool operator==(const mat_t &other) const noexcept
      {
        return _values[0] == other._values[0] && _values[1] == other._values[1]
               && _values[2] == other._values[2];
      }

      constexpr bool operator!=(const mat_t &other) const noexcept
      {
        return !(*this == other);
      }

#pragma endregion Equality

#pragma region Element Access

      NO_DISCARD constexpr vec_length_t GetColLength() const noexcept
      {
        return ColLength;
      }

      NO_DISCARD constexpr vec_length_t GetRowLength() const noexcept
      {
        return RowLength;
      }

      template <vec_length_t Index>
      REQUIRES((Index < ColLength))
      NO_DISCARD constexpr const column_t &Get() const noexcept
      {
        return _values[Index];
      }

      NO_DISCARD constexpr const column_t &operator[](vec_length_t col) const noexcept
      {
        KRYS_ASSERT(col < ColLength, "Index out of bounds", 0);
        return _values[col];
      }

#pragma endregion Element Access

#pragma region Addition

      NO_DISCARD constexpr mat_t operator+(const mat_t &other) const noexcept
      {
        return mat_t(_values[0] + other._values[0], _values[1] + other._values[1],
                     _values[2] + other._values[2]);
      }

      NO_DISCARD constexpr mat_t operator+(component_t scalar) const noexcept
      {
        return mat_t(_values[0] + scalar, _values[1] + scalar, _values[2] + scalar);
      }

      NO_DISCARD constexpr mat_t &operator+=(const mat_t &other) noexcept
      {
        _values[0] += other._values[0];
        _values[1] += other._values[1];
        _values[2] += other._values[2];
        return *this;
      }

      NO_DISCARD constexpr mat_t &operator+=(component_t scalar) noexcept
      {
        _values[0] += scalar;
        _values[1] += scalar;
        _values[2] += scalar;
        return *this;
      }

#pragma endregion Addition

#pragma region Subtraction

      NO_DISCARD constexpr mat_t operator-(const mat_t &other) const noexcept
      {
        return mat_t(_values[0] - other._values[0], _values[1] - other._values[1],
                     _values[2] - other._values[2]);
      }

      NO_DISCARD constexpr mat_t operator-(component_t scalar) const noexcept
      {
        return mat_t(_values[0] - scalar, _values[1] - scalar, _values[2] - scalar);
      }

      NO_DISCARD constexpr mat_t &operator-=(const mat_t &other) noexcept
      {
        _values[0] -= other._values[0];
        _values[1] -= other._values[1];
        _values[2] -= other._values[2];
        return *this;
      }

      NO_DISCARD constexpr mat_t &operator-=(component_t scalar) noexcept
      {
        _values[0] -= scalar;
        _values[1] -= scalar;
        _values[2] -= scalar;
        return *this;
      }

#pragma endregion Subtraction

#pragma region Multiplication

      NO_DISCARD constexpr mat_t operator*(const mat_t &other) const noexcept
      {
        const column_t &a0 = _values[0];
        const column_t &a1 = _values[1];
        const column_t &a2 = _values[2];

        const column_t &b0 = other._values[0];
        const column_t &b1 = other._values[1];
        const column_t &b2 = other._values[2];

        const column_t c0 = column_t(a0[0] * b0[0] + a0[1] * b1[0] + a0[2] * b2[0], // row 1, col 1
                                     a1[0] * b0[0] + a1[1] * b1[0] + a1[2] * b2[0], // row 2, col 1
                                     a2[0] * b0[0] + a2[1] * b1[0] + a2[2] * b2[0]  // row 3, col 1
        );

        const column_t c1 = column_t(a0[0] * b0[1] + a0[1] * b1[1] + a0[2] * b2[1], // row 1, col 2
                                     a1[0] * b0[1] + a1[1] * b1[1] + a1[2] * b2[1], // row 2, col 2
                                     a2[0] * b0[1] + a2[1] * b1[1] + a2[2] * b2[1]  // row 3, col 2
        );

        const column_t c2 = column_t(a0[0] * b0[2] + a0[1] * b1[2] + a0[2] * b2[2], // row 1, col 3
                                     a1[0] * b0[2] + a1[1] * b1[2] + a1[2] * b2[2], // row 2, col 3
                                     a2[0] * b0[2] + a2[1] * b1[2] + a2[2] * b2[2]  // row 3, col 3
        );

        return mat_t(c0, c1, c2);
      }

      NO_DISCARD constexpr mat_t operator*(component_t scalar) const noexcept
      {
        return mat_t(_values[0] * scalar, _values[1] * scalar, _values[2] * scalar);
      }

      NO_DISCARD constexpr column_t operator*(const column_t &vector) const noexcept
      {
        const column_t &a0 = _values[0];
        const column_t &a1 = _values[1];
        const column_t &a2 = _values[2];
        const column_t &v = vector;

        const column_t col = column_t(a0[0] * v[0] + a0[1] * v[1] + a0[2] * v[2], // Row 1
                                      a1[0] * v[0] + a1[1] * v[1] + a1[2] * v[2], // Row 2
                                      a2[0] * v[0] + a2[1] * v[1] + a2[2] * v[2]  // Row 3
        );

        return col;
      }

      NO_DISCARD constexpr mat_t &operator*=(const mat_t &other) noexcept
      {
        const column_t &a0 = _values[0];
        const column_t &a1 = _values[1];
        const column_t &a2 = _values[2];

        const column_t &b0 = other._values[0];
        const column_t &b1 = other._values[1];
        const column_t &b2 = other._values[2];

        _values[0] = column_t(a0[0] * b0[0] + a0[1] * b1[0] + a0[2] * b2[0], // row 1, col 1
                              a1[0] * b0[0] + a1[1] * b1[0] + a1[2] * b2[0], // row 2, col 1
                              a2[0] * b0[0] + a2[1] * b1[0] + a2[2] * b2[0]  // row 3, col 1
        );

        _values[1] = column_t(a0[0] * b0[1] + a0[1] * b1[1] + a0[2] * b2[1], // row 1, col 2
                              a1[0] * b0[1] + a1[1] * b1[1] + a1[2] * b2[1], // row 2, col 2
                              a2[0] * b0[1] + a2[1] * b1[1] + a2[2] * b2[1]  // row 3, col 2
        );

        _values[2] = column_t(a0[0] * b0[2] + a0[1] * b1[2] + a0[2] * b2[2], // row 1, col 3
                              a1[0] * b0[2] + a1[1] * b1[2] + a1[2] * b2[2], // row 2, col 3
                              a2[0] * b0[2] + a2[1] * b1[2] + a2[2] * b2[2]  // row 3, col 3
        );

        return *this;
      }

      NO_DISCARD constexpr mat_t &operator*=(component_t scalar) noexcept
      {
        _values[0] *= scalar;
        _values[1] *= scalar;
        _values[2] *= scalar;
        return *this;
      }

#pragma endregion Multiplication

#pragma region Division

      NO_DISCARD constexpr mat_t operator/(component_t scalar) const noexcept
      {
        KRYS_ASSERT(scalar != 0, "Division by zero", 0);
        return mat_t(_values[0] / scalar, _values[1] / scalar, _values[2] / scalar);
      }

      constexpr mat_t &operator/=(component_t scalar) noexcept
      {
        KRYS_ASSERT(scalar != 0, "Division by zero", 0);
        _values[0] /= scalar;
        _values[1] /= scalar;
        _values[2] /= scalar;
        return *this;
      }

#pragma endregion Division

#pragma region Unary

      NO_DISCARD constexpr mat_t operator-() const noexcept
      {
        return mat_t(-_values[0], -_values[1], -_values[2]);
      }

      NO_DISCARD constexpr mat_t operator+() const noexcept
      {
        return *this;
      }

#pragma endregion Unary
    };
  }
}