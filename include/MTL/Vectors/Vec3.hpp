#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"
#include "Debug/Macros.hpp"
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

      constexpr Vector() noexcept : x(component_t(0)), y(component_t(0)), z(component_t(0))
      {
      }

      explicit constexpr Vector(component_t scalar) noexcept : x(scalar), y(scalar), z(scalar)
      {
      }

      constexpr Vector(component_t x, component_t y, component_t z) noexcept : x(x), y(y), z(z)
      {
      }

      explicit constexpr Vector(const vector_t<component_t, 4>& other) noexcept : x(other.x), y(other.y), z(other.z)
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

      template <vec_length_t Index>
      REQUIRES((Index < Length))
      NO_DISCARD constexpr component_t &Get() noexcept
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
        KRYS_ASSERT(index < Length, "Index out of bounds");
        switch (index)
        {
          case 0:  return x;
          case 1:  return y;
          default:
          case 2:  return z;
        }
      }

      NO_DISCARD constexpr component_t& operator[](vec_length_t index)  noexcept
      {
        KRYS_ASSERT(index < Length, "Index out of bounds");
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

      constexpr vec_t &operator+=(const vec_t &other) noexcept
      {
        *this = *this + other;
        return *this;
      }

      constexpr vec_t &operator+=(component_t scalar) noexcept
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

      constexpr vec_t &operator-=(const vec_t &other) noexcept
      {
        *this = *this - other;
        return *this;
      }

      constexpr vec_t &operator-=(component_t scalar) noexcept
      {
        *this = *this - scalar;
        return *this;
      }

#pragma endregion Subtraction

#pragma region Division

      NO_DISCARD constexpr vec_t operator/(const vec_t &other) const noexcept
      {
        KRYS_ASSERT(other.x != 0 && other.y != 0 && other.z != 0, "Division by zero");
        return vec_t(x / other.x, y / other.y, z / other.z);
      }

      NO_DISCARD constexpr vec_t operator/(component_t scalar) const noexcept
      {
        KRYS_ASSERT(scalar != 0, "Division by zero");
        return vec_t(x / scalar, y / scalar, z / scalar);
      }

      constexpr vec_t &operator/=(const vec_t &other) noexcept
      {
        *this = *this / other;
        return *this;
      }

      constexpr vec_t &operator/=(component_t scalar) noexcept
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

      constexpr vec_t &operator*=(const vec_t &other) noexcept
      {
        *this = *this * other;
        return *this;
      }

      constexpr vec_t &operator*=(component_t scalar) noexcept
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

#pragma region Bitwise Shift

      NO_DISCARD constexpr vec_t operator<<(int shift) const noexcept
      requires(IsIntegralT<TComponent>)
      {
        return vec_t(x << shift, y << shift, z << shift);
      }

      NO_DISCARD constexpr vec_t operator>>(int shift) const noexcept
      requires(IsIntegralT<TComponent>)
      {
        return vec_t(x >> shift, y >> shift, z >> shift);
      }

      constexpr const vec_t &operator<<=(int shift) noexcept
      requires(IsIntegralT<TComponent>)
      {
        *this = *this << shift;
        return *this;
      }

      constexpr const vec_t &operator>>=(int shift) noexcept
      requires(IsIntegralT<TComponent>)
      {
        *this = *this >> shift;
        return *this;
      }

#pragma endregion Bitwise Shift

#pragma region Bitwise Or

      NO_DISCARD constexpr vec_t operator|(TComponent scalar) const noexcept
      requires(IsIntegralT<TComponent>)
      {
        return vec_t(x | scalar, x | scalar, z | scalar);
      }

      NO_DISCARD constexpr vec_t operator|(const vec_t &other) const noexcept
      requires(IsIntegralT<TComponent>)
      {
        return vec_t(x | other.x, x | other.y, z | other.z);
      }

      constexpr const vec_t &operator|=(TComponent scalar) noexcept
      requires(IsIntegralT<TComponent>)
      {
        *this = *this | scalar;
        return *this;
      }

      constexpr const vec_t &operator|=(const vec_t &other) noexcept
      requires(IsIntegralT<TComponent>)
      {
        *this = *this | other;
        return *this;
      }

#pragma endregion Bitwise Or

#pragma region Bitwise Xor

      NO_DISCARD constexpr vec_t operator^(TComponent scalar) const noexcept
      requires(IsIntegralT<TComponent>)
      {
        return vec_t(x ^ scalar, y ^ scalar, z ^ scalar);
      }

      NO_DISCARD constexpr vec_t operator^(const vec_t &other) const noexcept
      requires(IsIntegralT<TComponent>)
      {
        return vec_t(x ^ other.x, y ^ other.y, z ^ other.z);
      }

      constexpr const vec_t &operator^=(TComponent scalar) noexcept
      requires(IsIntegralT<TComponent>)
      {
        *this = *this ^ scalar;
        return *this;
      }

      constexpr const vec_t &operator^=(const vec_t &other) noexcept
      requires(IsIntegralT<TComponent>)
      {
        *this = *this ^ other;
        return *this;
      }

#pragma endregion Bitwise Xor

#pragma region Bitwise And

      NO_DISCARD constexpr vec_t operator&(TComponent scalar) const noexcept
      requires(IsIntegralT<TComponent>)
      {
        return vec_t(x & scalar, y & scalar, z & scalar);
      }

      NO_DISCARD constexpr vec_t operator&(const vec_t &other) const noexcept
      requires(IsIntegralT<TComponent>)
      {
        return vec_t(x & other.x, y & other.y, z & other.z);
      }

      constexpr const vec_t &operator&=(TComponent scalar) noexcept
      requires(IsIntegralT<TComponent>)
      {
        *this = *this & scalar;
        return *this;
      }

      constexpr const vec_t &operator&=(const vec_t &other) noexcept
      requires(IsIntegralT<TComponent>)
      {
        *this = *this & other;
        return *this;
      }

#pragma endregion Bitwise And

#pragma region Bitwise Not

      NO_DISCARD constexpr vec_t operator~() const noexcept
      requires(IsIntegralT<TComponent>)
      {
        return vec_t(~x, ~y, ~z);
      }

#pragma endregion Bitwise Not
    };
  }
}