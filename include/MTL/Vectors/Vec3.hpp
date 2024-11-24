#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"
#include "Core/Debug/Macros.hpp"
#include "MTL/Vectors/Base.hpp"

namespace Krys
{
  template <IsArithmeticT TComponent>
  using vec3_t = MTL::Vector<TComponent, 3>;
  using Vec3 = vec3_t<float>;

  namespace MTL
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

      constexpr vec_t &operator=(const vec_t &other) noexcept
      {
        x = other.x;
        y = other.y;
        z = other.z;
        return *this;
      }

      constexpr vec_t &operator=(vec_t &&other) noexcept
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

      NO_DISCARD constexpr vec_length_t GetLength() const noexcept
      {
        return Length;
      }

      template <vec_length_t Index>
      REQUIRES((Index < Length))
      NO_DISCARD constexpr const component_t &Get() const noexcept
      {
        if constexpr (Index == 0)
          return x;
        else if constexpr (Index == 1)
          return y;
        else
          return z;
      }

      NO_DISCARD constexpr component_t operator[](vec_length_t index) const noexcept
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

      NO_DISCARD constexpr vec_t operator+(const vec_t &other) const noexcept
      {
        return vec_t(x + other.x, y + other.y, z + other.z);
      }

      NO_DISCARD constexpr vec_t operator+(component_t scalar) const noexcept
      {
        return vec_t(x + scalar, y + scalar, z + scalar);
      }

      NO_DISCARD constexpr vec_t &operator+=(const vec_t &other) noexcept
      {
        *this = *this + other;
        return *this;
      }

      NO_DISCARD constexpr vec_t &operator+=(component_t scalar) noexcept
      {
        *this = *this + scalar;
        return *this;
      }

#pragma endregion Addition

#pragma region Subtraction

      NO_DISCARD constexpr vec_t operator-(const vec_t &other) const noexcept
      {
        return vec_t(x - other.x, y - other.y, z - other.z);
      }

      NO_DISCARD constexpr vec_t operator-(component_t scalar) const noexcept
      {
        return vec_t(x - scalar, y - scalar, z - scalar);
      }

      NO_DISCARD constexpr vec_t &operator-=(const vec_t &other) noexcept
      {
        *this = *this - other;
        return *this;
      }

      NO_DISCARD constexpr vec_t &operator-=(component_t scalar) noexcept
      {
        *this = *this - scalar;
        return *this;
      }

#pragma endregion Subtraction

#pragma region Division

      NO_DISCARD constexpr vec_t operator/(const vec_t &other) const noexcept
      {
        KRYS_ASSERT(other.x != 0 && other.y != 0 && other.z != 0, "Division by zero", 0);
        return vec_t(x / other.x, y / other.y, z / other.z);
      }

      NO_DISCARD constexpr vec_t operator/(component_t scalar) const noexcept
      {
        KRYS_ASSERT(scalar != 0, "Division by zero", 0);
        return vec_t(x / scalar, y / scalar, z / scalar);
      }

      NO_DISCARD constexpr vec_t &operator/=(const vec_t &other) noexcept
      {
        *this = *this / other;
        return *this;
      }

      NO_DISCARD constexpr vec_t &operator/=(component_t scalar) noexcept
      {
        *this = *this / scalar;
        return *this;
      }

#pragma endregion Division

#pragma region Multiplication

      NO_DISCARD constexpr vec_t operator*(const vec_t &other) const noexcept
      {
        return vec_t(x * other.x, y * other.y, z * other.z);
      }

      NO_DISCARD constexpr vec_t operator*(component_t scalar) const noexcept
      {
        return vec_t(x * scalar, y * scalar, z * scalar);
      }

      NO_DISCARD constexpr vec_t &operator*=(const vec_t &other) noexcept
      {
        *this = *this * other;
        return *this;
      }

      NO_DISCARD constexpr vec_t &operator*=(component_t scalar) noexcept
      {
        *this = *this * scalar;
        return *this;
      }

#pragma endregion Multiplication

#pragma region Unary

      NO_DISCARD constexpr vec_t operator-() const noexcept
      {
        return vec_t(-x, -y, -z);
      }

      NO_DISCARD constexpr vec_t operator+() const noexcept
      {
        return *this;
      }

#pragma endregion Unary
    };
  }
}