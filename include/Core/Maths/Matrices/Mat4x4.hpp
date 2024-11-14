#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"
#include "Core/Debug/Macros.hpp"
#include "Core/Maths/Matrices/Base.hpp"
#include "Core/Maths/Vectors/Base.hpp"

namespace Krys::MTL
{
  template <IsArithmeticT TComponent>
  struct Matrix<TComponent, 4, 4>
  {
  private:
    static constexpr vec_length_t RowLength = 4;
    static constexpr vec_length_t ColLength = 4;

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
        : _values {column_t(component_t(0)), column_t(component_t(0)), column_t(component_t(0)),
                   column_t(component_t(0))}
    {
    }

    explicit constexpr Matrix(component_t scalar) noexcept
        : _values {column_t(scalar, component_t(0), component_t(0), component_t(0)),
                   column_t(component_t(0), scalar, component_t(0), component_t(0)),
                   column_t(component_t(0), component_t(0), scalar, component_t(0)),
                   column_t(component_t(0), component_t(0), component_t(0), scalar)}
    {
    }

    explicit constexpr Matrix(component_t x0, component_t y0, component_t z0, component_t w0, component_t x1,
                              component_t y1, component_t z1, component_t w1, component_t x2, component_t y2,
                              component_t z2, component_t w2, component_t x3, component_t y3, component_t z3,
                              component_t w3) noexcept
        : _values {column_t(x0, y0, z0, w0), column_t(x1, y1, z1, w1), column_t(x2, y2, z2, w2),
                   column_t(x3, y3, z3, w3)}
    {
    }

    explicit constexpr Matrix(const column_t &col0, const column_t &col1, const column_t &col2,
                              const column_t &col3) noexcept
        : _values {column_t(col0), column_t(col1), column_t(col2), column_t(col3)}
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

    constexpr NO_DISCARD mat_t &operator=(const mat_t &other) noexcept
    {
      _values[0] = other._values[0];
      _values[1] = other._values[1];
      _values[2] = other._values[2];
      _values[3] = other._values[3];
      return *this;
    }

    constexpr NO_DISCARD mat_t &operator=(mat_t &&other) noexcept
    {
      _values = std::move(other._values);
      return *this;
    }

#pragma endregion Assignment

#pragma region Equality

    constexpr bool operator==(const mat_t &other) const noexcept
    {
      return _values[0] == other._values[0] && _values[1] == other._values[1]
             && _values[2] == other._values[2] && _values[3] == other._values[3];
    }

    constexpr bool operator!=(const mat_t &other) const noexcept
    {
      return !(*this == other);
    }

#pragma endregion Equality

#pragma region Element Access

    constexpr NO_DISCARD vec_length_t GetColLength() const noexcept
    {
      return ColLength;
    }

    constexpr NO_DISCARD vec_length_t GetRowLength() const noexcept
    {
      return RowLength;
    }

    template <vec_length_t Index>
    REQUIRES((Index < ColLength))
    constexpr NO_DISCARD const column_t &Get() const noexcept
    {
      return _values[Index];
    }

    constexpr NO_DISCARD const column_t &operator[](vec_length_t col) const noexcept
    {
      KRYS_ASSERT(col < ColLength, "Index out of bounds", 0);
      return _values[col];
    }

#pragma endregion Element Access

#pragma region Addition

    constexpr NO_DISCARD mat_t operator+(const mat_t &other) const noexcept
    {
      return mat_t(_values[0] + other._values[0], _values[1] + other._values[1],
                   _values[2] + other._values[2], _values[3] + other._values[3]);
    }

    constexpr NO_DISCARD mat_t operator+(component_t scalar) const noexcept
    {
      return mat_t(_values[0] + scalar, _values[1] + scalar, _values[2] + scalar, _values[3] + scalar);
    }

    constexpr NO_DISCARD mat_t &operator+=(const mat_t &other) noexcept
    {
      _values[0] += other._values[0];
      _values[1] += other._values[1];
      _values[2] += other._values[2];
      _values[3] += other._values[3];
      return *this;
    }

    constexpr NO_DISCARD mat_t &operator+=(component_t scalar) noexcept
    {
      _values[0] += scalar;
      _values[1] += scalar;
      _values[2] += scalar;
      _values[3] += scalar;
      return *this;
    }

#pragma endregion Addition

#pragma region Subtraction

    constexpr NO_DISCARD mat_t operator-(const mat_t &other) const noexcept
    {
      return mat_t(_values[0] - other._values[0], _values[1] - other._values[1],
                   _values[2] - other._values[2], _values[3] - other._values[3]);
    }

    constexpr NO_DISCARD mat_t operator-(component_t scalar) const noexcept
    {
      return mat_t(_values[0] - scalar, _values[1] - scalar, _values[2] - scalar, _values[3] - scalar);
    }

    constexpr NO_DISCARD mat_t &operator-=(const mat_t &other) noexcept
    {
      _values[0] -= other._values[0];
      _values[1] -= other._values[1];
      _values[2] -= other._values[2];
      _values[3] -= other._values[3];
      return *this;
    }

    constexpr NO_DISCARD mat_t &operator-=(component_t scalar) noexcept
    {
      _values[0] -= scalar;
      _values[1] -= scalar;
      _values[2] -= scalar;
      _values[3] -= scalar;
      return *this;
    }

#pragma endregion Subtraction

#pragma region Multiplication

    constexpr NO_DISCARD mat_t operator*(const mat_t &other) const noexcept
    {
      const column_t &a0 = _values[0];
      const column_t &a1 = _values[1];
      const column_t &a2 = _values[2];
      const column_t &a3 = _values[3];

      const column_t &b0 = other._values[0];
      const column_t &b1 = other._values[1];
      const column_t &b2 = other._values[2];
      const column_t &b3 = other._values[3];

      column_t c0(a0[0] * b0[0] + a0[1] * b1[0] + a0[2] * b2[0] + a0[3] * b3[0],
                  a1[0] * b0[0] + a1[1] * b1[0] + a1[2] * b2[0] + a1[3] * b3[0],
                  a2[0] * b0[0] + a2[1] * b1[0] + a2[2] * b2[0] + a2[3] * b3[0],
                  a3[0] * b0[0] + a3[1] * b1[0] + a3[2] * b2[0] + a3[3] * b3[0]);

      column_t c1(a0[0] * b0[1] + a0[1] * b1[1] + a0[2] * b2[1] + a0[3] * b3[1],
                  a1[0] * b0[1] + a1[1] * b1[1] + a1[2] * b2[1] + a1[3] * b3[1],
                  a2[0] * b0[1] + a2[1] * b1[1] + a2[2] * b2[1] + a2[3] * b3[1],
                  a3[0] * b0[1] + a3[1] * b1[1] + a3[2] * b2[1] + a3[3] * b3[1]);

      column_t c2(a0[0] * b0[2] + a0[1] * b1[2] + a0[2] * b2[2] + a0[3] * b3[2],
                  a1[0] * b0[2] + a1[1] * b1[2] + a1[2] * b2[2] + a1[3] * b3[2],
                  a2[0] * b0[2] + a2[1] * b1[2] + a2[2] * b2[2] + a2[3] * b3[2],
                  a3[0] * b0[2] + a3[1] * b1[2] + a3[2] * b2[2] + a3[3] * b3[2]);

      column_t c3(a0[0] * b0[3] + a0[1] * b1[3] + a0[2] * b2[3] + a0[3] * b3[3],
                  a1[0] * b0[3] + a1[1] * b1[3] + a1[2] * b2[3] + a1[3] * b3[3],
                  a2[0] * b0[3] + a2[1] * b1[3] + a2[2] * b2[3] + a2[3] * b3[3],
                  a3[0] * b0[3] + a3[1] * b1[3] + a3[2] * b2[3] + a3[3] * b3[3]);

      return mat_t(c0, c1, c2, c3);
    }

    constexpr NO_DISCARD mat_t operator*(component_t scalar) const noexcept
    {
      return mat_t(_values[0] * scalar, _values[1] * scalar, _values[2] * scalar, _values[3] * scalar);
    }

    constexpr NO_DISCARD column_t operator*(const column_t &vector) const noexcept
    {
      const column_t &a0 = _values[0];
      const column_t &a1 = _values[1];
      const column_t &a2 = _values[2];
      const column_t &a3 = _values[3];
      const column_t &v = vector;

      const column_t col = column_t(a0[0] * v[0] + a0[1] * v[1] + a0[2] * v[2], // Row 1
                                    a1[0] * v[0] + a1[1] * v[1] + a1[2] * v[2], // Row 2
                                    a2[0] * v[0] + a2[1] * v[1] + a2[2] * v[2], // Row 3
                                    a3[0] * v[0] + a3[1] * v[1] + a3[2] * v[2]  // Row 4
      );

      return col;
    }

    constexpr NO_DISCARD mat_t &operator*=(const mat_t &other) noexcept
    {
      const column_t &a0 = _values[0];
      const column_t &a1 = _values[1];
      const column_t &a2 = _values[2];
      const column_t &a3 = _values[3];

      const column_t &b0 = other._values[0];
      const column_t &b1 = other._values[1];
      const column_t &b2 = other._values[2];
      const column_t &b3 = other._values[3];

      _values[0] = column_t(a0[0] * b0[0] + a0[1] * b1[0] + a0[2] * b2[0] + a0[3] * b3[0],
                            a1[0] * b0[0] + a1[1] * b1[0] + a1[2] * b2[0] + a1[3] * b3[0],
                            a2[0] * b0[0] + a2[1] * b1[0] + a2[2] * b2[0] + a2[3] * b3[0],
                            a3[0] * b0[0] + a3[1] * b1[0] + a3[2] * b2[0] + a3[3] * b3[0]);

      _values[1] = column_t(a0[0] * b0[1] + a0[1] * b1[1] + a0[2] * b2[1] + a0[3] * b3[1],
                            a1[0] * b0[1] + a1[1] * b1[1] + a1[2] * b2[1] + a1[3] * b3[1],
                            a2[0] * b0[1] + a2[1] * b1[1] + a2[2] * b2[1] + a2[3] * b3[1],
                            a3[0] * b0[1] + a3[1] * b1[1] + a3[2] * b2[1] + a3[3] * b3[1]);

      _values[2] = column_t(a0[0] * b0[2] + a0[1] * b1[2] + a0[2] * b2[2] + a0[3] * b3[2],
                            a1[0] * b0[2] + a1[1] * b1[2] + a1[2] * b2[2] + a1[3] * b3[2],
                            a2[0] * b0[2] + a2[1] * b1[2] + a2[2] * b2[2] + a2[3] * b3[2],
                            a3[0] * b0[2] + a3[1] * b1[2] + a3[2] * b2[2] + a3[3] * b3[2]);

      _values[3] = column_t(a0[0] * b0[3] + a0[1] * b1[3] + a0[2] * b2[3] + a0[3] * b3[3],
                            a1[0] * b0[3] + a1[1] * b1[3] + a1[2] * b2[3] + a1[3] * b3[3],
                            a2[0] * b0[3] + a2[1] * b1[3] + a2[2] * b2[3] + a2[3] * b3[3],
                            a3[0] * b0[3] + a3[1] * b1[3] + a3[2] * b2[3] + a3[3] * b3[3]);

      return *this;
    }

    constexpr NO_DISCARD mat_t &operator*=(component_t scalar) noexcept
    {
      _values[0] *= scalar;
      _values[1] *= scalar;
      _values[2] *= scalar;
      _values[3] *= scalar;
      return *this;
    }

#pragma endregion Multiplication

#pragma region Division

    constexpr NO_DISCARD mat_t operator/(component_t scalar) const noexcept
    {
      KRYS_ASSERT(scalar != 0, "Division by zero", 0);
      return mat_t(_values[0] / scalar, _values[1] / scalar, _values[2] / scalar, _values[3] / scalar);
    }

    constexpr mat_t &operator/=(component_t scalar) noexcept
    {
      KRYS_ASSERT(scalar != 0, "Division by zero", 0);
      _values[0] /= scalar;
      _values[1] /= scalar;
      _values[2] /= scalar;
      _values[3] /= scalar;
      return *this;
    }

#pragma endregion Division

#pragma region Unary

    constexpr NO_DISCARD mat_t operator-() const noexcept
    {
      return mat_t(-_values[0], -_values[1], -_values[2], -_values[3]);
    }

    constexpr NO_DISCARD mat_t operator+() const noexcept
    {
      return *this;
    }

#pragma endregion Unary
  };
}