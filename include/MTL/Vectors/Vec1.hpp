#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"
#include "Core/Debug/Macros.hpp"
#include "MTL/Vectors/Base.hpp"

namespace Krys
{
  template <IsArithmeticT TComponent>
  using vec1_t = MTL::Vector<TComponent, 1>;
  using Vec1 = vec1_t<float>;

  namespace MTL
  {
    template <IsArithmeticT TComponent>
    struct Vector<TComponent, 1>
    {
    private:
      static constexpr vec_length_t Length = 1;

    public:
      using component_t = TComponent;
      using vec_t = Vector<component_t, Length>;

    public:
      component_t x;

      constexpr ~Vector() noexcept = default;

#pragma region Construction

      explicit constexpr Vector() noexcept : x(component_t(0))
      {
      }

      explicit constexpr Vector(component_t scalar) noexcept : x(scalar)
      {
      }

      constexpr Vector(initializer_list<component_t> il) noexcept
      {
        auto it = il.begin();
        x = (it != il.end()) ? *it++ : TComponent(0);
        KRYS_ASSERT(it == il.end(), "Too many initializer list values", 0);
      }

      constexpr Vector(const vec_t &other) noexcept : x(other.x)
      {
      }

      constexpr Vector(vec_t &&other) noexcept : x(std::move(other.x))
      {
      }

#pragma endregion Construction

#pragma region Assignment

      constexpr vec_t &operator=(const vec_t &other) noexcept
      {
        x = other.x;
        return *this;
      }

      constexpr vec_t &operator=(vec_t &&other) noexcept
      {
        x = std::move(other.x);
        return *this;
      }

#pragma endregion Assignment

#pragma region Equality

      constexpr bool operator==(const vec_t &other) const noexcept
      {
        return x == other.x;
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
        return x;
      }

      template <vec_length_t Index>
      REQUIRES((Index < Length))
      NO_DISCARD constexpr component_t &Get() noexcept
      {
        return x;
      }

      NO_DISCARD constexpr component_t operator[](vec_length_t index) const noexcept
      {
        KRYS_ASSERT(index < Length, "Index out of bounds", 0);
        return x;
      }

      NO_DISCARD constexpr component_t &operator[](vec_length_t index) noexcept
      {
        KRYS_ASSERT(index < Length, "Index out of bounds", 0);
        return x;
      }

#pragma endregion Element Access

#pragma region Addition

      NO_DISCARD constexpr vec_t operator+(const vec_t &other) const noexcept
      {
        return vec_t(x + other.x);
      }

      NO_DISCARD constexpr vec_t operator+(component_t scalar) const noexcept
      {
        return vec_t(x + scalar);
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
        return vec_t(x - other.x);
      }

      NO_DISCARD constexpr vec_t operator-(component_t scalar) const noexcept
      {
        return vec_t(x - scalar);
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
        KRYS_ASSERT(other.x != 0, "Division by zero", 0);
        return vec_t(x / other.x);
      }

      NO_DISCARD constexpr vec_t operator/(component_t scalar) const noexcept
      {
        KRYS_ASSERT(scalar != 0, "Division by zero", 0);
        return vec_t(x / scalar);
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
        return vec_t(x * other.x);
      }

      NO_DISCARD constexpr vec_t operator*(component_t scalar) const noexcept
      {
        return vec_t(x * scalar);
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
        return vec_t(-x);
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
        return vec_t(x << shift);
      }

      NO_DISCARD constexpr vec_t operator>>(int shift) const noexcept
      requires(IsIntegralT<TComponent>)
      {
        return vec_t(x >> shift);
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
        return vec_t(x | scalar);
      }

      NO_DISCARD constexpr vec_t operator|(const vec_t &other) const noexcept
      requires(IsIntegralT<TComponent>)
      {
        return vec_t(x | other.x);
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
        return vec_t(x ^ scalar);
      }

      NO_DISCARD constexpr vec_t operator^(const vec_t &other) const noexcept
      requires(IsIntegralT<TComponent>)
      {
        return vec_t(x ^ other.x);
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
        return vec_t(x & scalar);
      }

      NO_DISCARD constexpr vec_t operator&(const vec_t &other) const noexcept
      requires(IsIntegralT<TComponent>)
      {
        return vec_t(x & other.x);
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
        return vec_t(~x);
      }

#pragma endregion Bitwise Not
    };
  }
}