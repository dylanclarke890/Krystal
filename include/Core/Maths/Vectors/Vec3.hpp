#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"
#include "Core/Debug/Macros.hpp"
#include "Core/Maths/Vectors/Base.hpp"

namespace Krys::MTL
{
  template <IsArithmeticT TComponent>
  struct Vector<TComponent, 3>
  {
  private:
    static constexpr vec_length_t Length = 3;

  public:
    using component_t = TComponent;
    using vec_t = Vector<component_t, Length>;

  public:
    component_t x, y, z;

    constexpr ~Vector() noexcept = default;

#pragma region Construction

    explicit constexpr Vector() noexcept : x(component_t(0)), y(component_t(0)), z(component_t(0))
    {
    }

    explicit constexpr Vector(component_t scalar) noexcept : x(scalar), y(scalar), z(scalar)
    {
    }

    explicit constexpr Vector(component_t x, component_t y, component_t z) noexcept : x(x), y(y), z(z)
    {
    }

    constexpr Vector(const vec_t &other) noexcept : x(other.x), y(other.y), z(other.z)
    {
    }

    constexpr Vector(vec_t &&other) noexcept
        : x(std::move(other.x)), y(std::move(other.y)), z(std::move(other.z))
    {
    }

#pragma endregion Construction

#pragma region Assignment

    constexpr NO_DISCARD vec_t &operator=(const vec_t &other) noexcept
    {
      x = other.x;
      y = other.y;
      z = other.z;
      return *this;
    }

    constexpr NO_DISCARD vec_t &operator=(vec_t &&other) noexcept
    {
      x = std::move(other.x);
      y = std::move(other.y);
      z = std::move(other.z);
      return *this;
    }

#pragma endregion Assignment

#pragma region Equality

    constexpr bool operator==(const vec_t &other) const noexcept
    {
      return x == other.x && y == other.y && z == other.z;
    }

    constexpr bool operator!=(const vec_t &other) const noexcept
    {
      return !(*this == other);
    }

#pragma endregion Equality

#pragma region Element Access

    constexpr NO_DISCARD vec_length_t GetLength() const noexcept
    {
      return Length;
    }

    template <vec_length_t Index>
    REQUIRES((Index < Length))
    constexpr NO_DISCARD const component_t &Get() const noexcept
    {
      if (Index == 0)
        return x;
      if (Index == 1)
        return y;
      return z;
    }

    constexpr NO_DISCARD component_t operator[](vec_length_t index) const noexcept
    {
      KRYS_ASSERT(index < Length, "Index out of bounds", 0);
      switch (index)
      {
        case 0:  return x;
        case 1:  return y;
        default:
        case 2:  return z;
      }
    }

#pragma endregion Element Access

#pragma region Addition

    constexpr NO_DISCARD vec_t operator+(const vec_t &other) const noexcept
    {
      return vec_t(x + other.x, y + other.y, z + other.z);
    }

    constexpr NO_DISCARD vec_t operator+(component_t scalar) const noexcept
    {
      return vec_t(x + scalar, y + scalar, z + scalar);
    }

    constexpr NO_DISCARD vec_t &operator+=(const vec_t &other) noexcept
    {
      x += other.x;
      y += other.y;
      z += other.z;
      return *this;
    }

    constexpr NO_DISCARD vec_t &operator+=(component_t scalar) const noexcept
    {
      x += scalar;
      y += scalar;
      z += scalar;
      return *this;
    }

#pragma endregion Addition

#pragma region Subtraction

    constexpr NO_DISCARD vec_t operator-(const vec_t &other) const noexcept
    {
      return vec_t(x - other.x, y - other.y, z - other.z);
    }

    constexpr NO_DISCARD vec_t operator-(component_t scalar) const noexcept
    {
      return vec_t(x - scalar, y - scalar, z - scalar);
    }

    constexpr NO_DISCARD vec_t &operator-=(const vec_t &other) noexcept
    {
      x -= other.x;
      y -= other.y;
      z -= other.z;
      return *this;
    }

    constexpr NO_DISCARD vec_t &operator-=(component_t scalar) noexcept
    {
      x -= scalar;
      y -= scalar;
      z -= scalar;
      return *this;
    }

#pragma endregion Subtraction

#pragma region Division

    constexpr NO_DISCARD vec_t operator/(const vec_t &other) const noexcept
    {
      KRYS_ASSERT(other.x != 0 && other.y != 0 && other.z != 0, "Division by zero", 0);

      return vec_t(x / other.x, y / other.y, z / other.z);
    }

    constexpr NO_DISCARD vec_t operator/(component_t scalar) const noexcept
    {
      KRYS_ASSERT(scalar != 0, "Division by zero", 0);

      return vec_t(x / scalar, y / scalar, z / scalar);
    }

    constexpr NO_DISCARD vec_t &operator/=(const vec_t &other) noexcept
    {
      KRYS_ASSERT(other.x != 0 && other.y != 0 && other.z != 0, "Division by zero", 0);

      x /= other.x;
      y /= other.y;
      z /= other.z;
      return *this;
    }

    constexpr NO_DISCARD vec_t &operator/=(component_t scalar) noexcept
    {
      KRYS_ASSERT(scalar != 0, "Division by zero", 0);

      x /= scalar;
      y /= scalar;
      z /= scalar;
      return *this;
    }

#pragma endregion Division

#pragma region Multiplication

    constexpr NO_DISCARD vec_t operator*(const vec_t &other) const noexcept
    {
      return vec_t(x * other.x, y * other.y, z * other.z);
    }

    constexpr NO_DISCARD vec_t operator*(component_t scalar) const noexcept
    {
      return vec_t(x * scalar, y * scalar, z * scalar);
    }

    constexpr NO_DISCARD vec_t &operator*=(const vec_t &other) noexcept
    {
      x *= other.x;
      y *= other.y;
      z *= other.z;
      return *this;
    }

    constexpr NO_DISCARD vec_t &operator*=(component_t scalar) noexcept
    {
      x *= scalar;
      y *= scalar;
      z *= scalar;
      return *this;
    }

#pragma endregion Multiplication

#pragma region Unary

    constexpr NO_DISCARD vec_t operator-() const noexcept
    {
      return vec_t(-x, -y, -z);
    }

    constexpr NO_DISCARD vec_t operator+() const noexcept
    {
      return *this;
    }

#pragma endregion Unary
  };
}