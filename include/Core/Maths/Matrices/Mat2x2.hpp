#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"
#include "Core/Debug/Macros.hpp"
#include "Core/Maths/Matrices/Base.hpp"
#include "Core/Maths/Vectors/Base.hpp"

namespace Krys::Maths
{
  template <IsArithmeticT TComponent>
  struct Matrix<TComponent, 2, 2>
  {
  private:
    static constexpr vec_length_t RowLength = 2;
    static constexpr vec_length_t ColLength = 2;

  public:
    using component_t = TComponent;
    using row_t = Vector<component_t, RowLength>;
    using column_t = Vector<component_t, ColLength>;

    using mat_t = Matrix<component_t, RowLength, ColLength>;
    using mat_transpose_t = Matrix<component_t, ColLength, RowLength>;

  private:
    column_t _values[RowLength];

  public:
    static constexpr mat_t I = mat_t(static_cast<component_t>(1));

#pragma region Construction

    explicit constexpr Matrix() noexcept : _values {column_t(0, 0), column_t(0, 0)}
    {
    }

    explicit constexpr Matrix(component_t scalar) noexcept
        : _values {column_t(scalar, 0), column_t(0, scalar)}
    {
    }

    explicit constexpr Matrix(component_t x0, component_t y0, component_t x1, component_t y1) noexcept
        : _values {column_t(x0, y0), column_t(x1, y1)}
    {
    }

    explicit constexpr Matrix(const column_t &col0, const column_t &col1) noexcept
        : _values {column_t(col0.x, col0.y), column_t(col1.x, col1.y)}
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
      return _values[0] == other._values[0] && _values[1] == other._values[1];
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

    constexpr NO_DISCARD const column_t &operator[](vec_length_t col) const noexcept
    {
      KRYS_ASSERT(index < Length, "Index out of bounds", 0);
      return _values[col];
    }

#pragma endregion Element Access

#pragma region Addition

    constexpr NO_DISCARD mat_t operator+(const mat_t &other) const noexcept
    {
      return mat_t(_values[0] + other._values[0], _values[1] + other._values[1]);
    }

    constexpr NO_DISCARD mat_t operator+(component_t scalar) const noexcept
    {
      return mat_t(_values[0].x + scalar, _values[0].y + scalar, _values[1].x + scalar,
                   _values[1].y + scalar);
    }

    constexpr NO_DISCARD mat_t &operator+=(const mat_t &other) noexcept
    {
      _values[0] += other._values[0];
      _values[1] += other._values[1];
      return *this;
    }

    constexpr NO_DISCARD mat_t &operator+=(component_t scalar) noexcept
    {
      _values[0].x += scalar;
      _values[0].y += scalar;
      _values[1].x += scalar;
      _values[1].y += scalar;
      return *this;
    }

#pragma endregion Addition

#pragma region Subtraction

    constexpr NO_DISCARD mat_t operator-(const mat_t &other) const noexcept
    {
      return mat_t(_values[0] - other._values[0], _values[1] - other._values[1]);
    }

    constexpr NO_DISCARD mat_t operator-(component_t scalar) const noexcept
    {
      return mat_t(_values[0].x - scalar, _values[0].y - scalar, _values[1].x - scalar,
                   _values[1].y - scalar);
    }

    constexpr NO_DISCARD mat_t &operator-=(const mat_t &other) noexcept
    {
      _values[0] -= other._values[0];
      _values[1] -= other._values[1];
      return *this;
    }

    constexpr NO_DISCARD mat_t &operator-=(component_t scalar) noexcept
    {
      _values[0].x -= scalar;
      _values[0].y -= scalar;
      _values[1].x -= scalar;
      _values[1].y -= scalar;
      return *this;
    }

#pragma endregion Subtraction

#pragma region Multiplication

    constexpr NO_DISCARD mat_t operator*(const mat_t &other) const noexcept
    {
      const column_t &a0 = _values[0];
      const column_t &a1 = _values[1];
      const column_t &b0 = other._values[0];
      const column_t &b1 = other._values[1];

      const column_t c0 = column_t(a0[0] * b0[0] + a0[1] * b1[0], // row 1, col 1
                                   a1[0] * b0[0] + a1[1] * b1[0]  // row 2, col 1
      );

      const column_t c1 = column_t(a0[0] * b0[1] + a0[1] * b1[1], // row 1, col 2
                                   a1[0] * b0[1] + a1[1] * b1[1]  // row 2, col 2
      );

      return mat_t(c0, c1);
    }

    constexpr NO_DISCARD mat_t operator*(component_t scalar) const noexcept
    {
      return mat_t(_values[0].x * scalar, _values[0].y * scalar, _values[1].x * scalar,
                   _values[1].y * scalar);
    }

    constexpr NO_DISCARD column_t operator*(const column_t &vector) const noexcept
    {
      const column_t &a0 = _values[0];
      const column_t &a1 = _values[1];
      const column_t &v = vector;

      const column_t col = column_t(a0[0] * v[0] + a0[1] * v[1], // Row 1
                                    a1[0] * v[0] + a1[1] * v[1]  // Row 2
      );

      return col;
    }

    constexpr NO_DISCARD mat_t &operator*=(const mat_t &other) noexcept
    {
      const column_t &a0 = _values[0];
      const column_t &a1 = _values[1];
      const column_t &b0 = other._values[0];
      const column_t &b1 = other._values[1];

      _values[0] = column_t(a0[0] * b0[0] + a0[1] * b1[0], // row 1, col 1
                            a1[0] * b0[0] + a1[1] * b1[0]  // row 2, col 1
      );

      _values[1] = column_t(a0[0] * b0[1] + a0[1] * b1[1], // row 1, col 2
                            a1[0] * b0[1] + a1[1] * b1[1]  // row 2, col 2
      );

      return *this;
    }

    constexpr NO_DISCARD mat_t &operator*=(component_t scalar) noexcept
    {
      _values[0].x *= scalar;
      _values[0].y *= scalar;
      _values[1].x *= scalar;
      _values[1].y *= scalar;
      return *this;
    }

#pragma endregion Multiplication

#pragma region Division

    constexpr NO_DISCARD mat_t operator/(component_t scalar) const noexcept
    {
      KRYS_ASSERT(scalar != 0, "Division by zero", 0);
      return mat_t(_values[0].x / scalar, _values[0].y / scalar, _values[1].x / scalar,
                   _values[1].y / scalar);
    }

    constexpr mat_t &operator/=(component_t scalar) noexcept
    {
      KRYS_ASSERT(scalar != 0, "Division by zero", 0);
      _values[0].x /= scalar;
      _values[0].y /= scalar;
      _values[1].x /= scalar;
      _values[1].y /= scalar;
      return *this;
    }

#pragma endregion Division

#pragma region Unary

    constexpr NO_DISCARD mat_t operator-() const noexcept
    {
      return mat_t(column_t(-_values[0].x, -_values[0].y), column_t(-_values[1].x, -_values[1].y));
    }

    constexpr NO_DISCARD mat_t operator+() const noexcept
    {
      return *this;
    }

#pragma endregion Unary
  };
}