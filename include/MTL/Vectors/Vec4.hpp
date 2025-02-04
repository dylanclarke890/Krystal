#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"
#include "Debug/Macros.hpp"
#include "MTL/Vectors/Base.hpp"

namespace Krys
{
  template <IsArithmeticT TComponent>
  using vec4_t = MTL::Vector<TComponent, 4>;
  using Vec4 = vec4_t<float>;
  using Vec4i = vec4_t<int32>;
  using Vec4ui = vec4_t<uint32>;

  namespace MTL
  {
    template <IsArithmeticT TComponent>
    struct Vector<TComponent, 4>
    {
    private:
      static constexpr vec_length_t Length = 4;

    public:
      using component_t = TComponent;
      using vec_t = Vector<component_t, Length>;

    public:
      component_t x, y, z, w;

      constexpr ~Vector() noexcept = default;

#pragma region Construction

      explicit constexpr Vector() noexcept
          : x(component_t(0)), y(component_t(0)), z(component_t(0)), w(component_t(0))
      {
      }

      explicit constexpr Vector(component_t scalar) noexcept : x(scalar), y(scalar), z(scalar), w(scalar)
      {
      }

      explicit constexpr Vector(component_t x, component_t y, component_t z, component_t w) noexcept
          : x(x), y(y), z(z), w(w)
      {
      }

      explicit constexpr Vector(const vector_t<component_t, 3>& other, component_t w) noexcept
          : x(other.x), y(other.y), z(other.z), w(w)
      {
      }

      constexpr Vector(initializer_list<component_t> il) noexcept
      {
        auto it = il.begin();
        x = (it != il.end()) ? *it++ : TComponent(0);
        y = (it != il.end()) ? *it++ : TComponent(0);
        z = (it != il.end()) ? *it++ : TComponent(0);
        w = (it != il.end()) ? *it++ : TComponent(0);
        KRYS_ASSERT(it == il.end(), "Too many initializer list values");
      }

      constexpr Vector(const vec_t &other) noexcept : x(other.x), y(other.y), z(other.z), w(other.w)
      {
      }

      constexpr Vector(vec_t &&other) noexcept
          : x(std::move(other.x)), y(std::move(other.y)), z(std::move(other.z)), w(std::move(other.w))
      {
      }

#pragma endregion Construction

#pragma region Assignment

      constexpr vec_t &operator=(const vec_t &other) noexcept
      {
        x = other.x;
        y = other.y;
        z = other.z;
        w = other.w;
        return *this;
      }

      constexpr vec_t &operator=(vec_t &&other) noexcept
      {
        x = std::move(other.x);
        y = std::move(other.y);
        z = std::move(other.z);
        w = std::move(other.w);
        return *this;
      }

#pragma endregion Assignment

#pragma region Equality

      constexpr bool operator==(const vec_t &other) const noexcept
      {
        return x == other.x && y == other.y && z == other.z && w == other.w;
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
        else if constexpr (Index == 2)
          return z;
        else
          return w;
      }

      template <vec_length_t Index>
      REQUIRES((Index < Length))
      NO_DISCARD constexpr component_t &Get() noexcept
      {
        if constexpr (Index == 0)
          return x;
        else if constexpr (Index == 1)
          return y;
        else if constexpr (Index == 2)
          return z;
        else
          return w;
      }

      NO_DISCARD constexpr component_t operator[](vec_length_t index) const noexcept
      {
        KRYS_ASSERT(index < Length, "Index out of bounds");
        switch (index)
        {
          case 0:  return x;
          case 1:  return y;
          case 2:  return z;
          default:
          case 3:  return w;
        }
      }

      NO_DISCARD constexpr component_t& operator[](vec_length_t index) noexcept
      {
        KRYS_ASSERT(index < Length, "Index out of bounds");
        switch (index)
        {
          case 0:  return x;
          case 1:  return y;
          case 2:  return z;
          default:
          case 3:  return w;
        }
      }

#pragma endregion Element Access

#pragma region Addition

      NO_DISCARD constexpr vec_t operator+(const vec_t &other) const noexcept
      {
        return vec_t(x + other.x, y + other.y, z + other.z, w + other.w);
      }

      NO_DISCARD constexpr vec_t operator+(component_t scalar) const noexcept
      {
        return vec_t(x + scalar, y + scalar, z + scalar, w + scalar);
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
        return vec_t(x - other.x, y - other.y, z - other.z, w - other.w);
      }

      NO_DISCARD constexpr vec_t operator-(component_t scalar) const noexcept
      {
        return vec_t(x - scalar, y - scalar, z - scalar, w - scalar);
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
        KRYS_ASSERT(other.x != 0 && other.y != 0 && other.z != 0 && other.w != 0, "Division by zero");
        return vec_t(x / other.x, y / other.y, z / other.z, w / other.w);
      }

      NO_DISCARD constexpr vec_t operator/(component_t scalar) const noexcept
      {
        KRYS_ASSERT(scalar != 0, "Division by zero");
        return vec_t(x / scalar, y / scalar, z / scalar, w / scalar);
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
        return vec_t(x * other.x, y * other.y, z * other.z, w * other.w);
      }

      NO_DISCARD constexpr vec_t operator*(component_t scalar) const noexcept
      {
        return vec_t(x * scalar, y * scalar, z * scalar, w * scalar);
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
        return vec_t(-x, -y, -z, -w);
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
        return vec_t(x << shift, y << shift, z << shift, w << shift);
      }

      NO_DISCARD constexpr vec_t operator>>(int shift) const noexcept
      requires(IsIntegralT<TComponent>)
      {
        return vec_t(x >> shift, y >> shift, z >> shift, w >> shift);
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
        return vec_t(x | scalar, x | scalar, z | scalar, w | scalar);
      }

      NO_DISCARD constexpr vec_t operator|(const vec_t &other) const noexcept
      requires(IsIntegralT<TComponent>)
      {
        return vec_t(x | other.x, x | other.y, z | other.z, w | other.w);
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
        return vec_t(x ^ scalar, y ^ scalar, z ^ scalar, w ^ scalar);
      }

      NO_DISCARD constexpr vec_t operator^(const vec_t &other) const noexcept
      requires(IsIntegralT<TComponent>)
      {
        return vec_t(x ^ other.x, y ^ other.y, z ^ other.z, w ^ other.w);
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
        return vec_t(x & scalar, y & scalar, z & scalar, w & scalar);
      }

      NO_DISCARD constexpr vec_t operator&(const vec_t &other) const noexcept
      requires(IsIntegralT<TComponent>)
      {
        return vec_t(x & other.x, y & other.y, z & other.z, w & other.w);
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
        return vec_t(~x, ~y, ~z, ~w);
      }

#pragma endregion Bitwise Not
    };
  }
}