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

      constexpr Vector(const vec_t &other) noexcept : x(other.x)
      {
      }

      constexpr Vector(vec_t &&other) noexcept : x(std::move(other.x))
      {
      }

#pragma endregion Construction

#pragma region Assignment

      constexpr NO_DISCARD vec_t &operator=(const vec_t &other) noexcept
      {
        x = other.x;
        return *this;
      }

      constexpr NO_DISCARD vec_t &operator=(vec_t &other) noexcept
      {
        x = other.x;
        return *this;
      }

      constexpr NO_DISCARD vec_t &operator=(vec_t &&other) noexcept
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

      constexpr NO_DISCARD vec_length_t GetLength() const noexcept
      {
        return Length;
      }

      template <vec_length_t Index>
      REQUIRES((Index < Length))
      constexpr NO_DISCARD const component_t &Get() const noexcept
      {
        return x;
      }

      constexpr NO_DISCARD component_t operator[](vec_length_t index) const noexcept
      {
        KRYS_ASSERT(index < Length, "Index out of bounds", 0);
        return x;
      }

#pragma endregion Element Access

#pragma region Addition

      constexpr NO_DISCARD vec_t operator+(const vec_t &other) const noexcept
      {
        return vec_t(x + other.x);
      }

      constexpr NO_DISCARD vec_t operator+(component_t scalar) const noexcept
      {
        return vec_t(x + scalar);
      }

      constexpr NO_DISCARD vec_t &operator+=(const vec_t &other) noexcept
      {
        x += other.x;
        return *this;
      }

      constexpr NO_DISCARD vec_t &operator+=(component_t scalar) noexcept
      {
        x += scalar;
        return *this;
      }

#pragma endregion Addition

#pragma region Subtraction

      constexpr NO_DISCARD vec_t operator-(const vec_t &other) const noexcept
      {
        return vec_t(x - other.x);
      }

      constexpr NO_DISCARD vec_t operator-(component_t scalar) const noexcept
      {
        return vec_t(x - scalar);
      }

      constexpr NO_DISCARD vec_t &operator-=(const vec_t &other) noexcept
      {
        x -= other.x;
        return *this;
      }

      constexpr NO_DISCARD vec_t &operator-=(component_t scalar) noexcept
      {
        x -= scalar;
        return *this;
      }

#pragma endregion Subtraction

#pragma region Division

      constexpr NO_DISCARD vec_t operator/(const vec_t &other) const noexcept
      {
        KRYS_ASSERT(other.x != 0, "Division by zero", 0);

        return vec_t(x / other.x);
      }

      constexpr NO_DISCARD vec_t operator/(component_t scalar) const noexcept
      {
        KRYS_ASSERT(scalar != 0, "Division by zero", 0);

        return vec_t(x / scalar);
      }

      constexpr NO_DISCARD vec_t &operator/=(const vec_t &other) noexcept
      {
        KRYS_ASSERT(other.x != 0, "Division by zero", 0);

        x /= other.x;
        return *this;
      }

      constexpr NO_DISCARD vec_t &operator/=(component_t scalar) noexcept
      {
        KRYS_ASSERT(scalar != 0, "Division by zero", 0);

        x /= scalar;
        return *this;
      }

#pragma endregion Division

#pragma region Multiplication

      constexpr NO_DISCARD vec_t operator*(const vec_t &other) const noexcept
      {
        return vec_t(x * other.x);
      }

      constexpr NO_DISCARD vec_t operator*(component_t scalar) const noexcept
      {
        return vec_t(x * scalar);
      }

      constexpr NO_DISCARD vec_t &operator*=(const vec_t &other) noexcept
      {
        x *= other.x;
        return *this;
      }

      constexpr NO_DISCARD vec_t &operator*=(component_t scalar) noexcept
      {
        x *= scalar;
        return *this;
      }

#pragma endregion Multiplication

#pragma region Unary

      constexpr NO_DISCARD vec_t operator-() const noexcept
      {
        return vec_t(-x);
      }

      constexpr NO_DISCARD vec_t operator+() const noexcept
      {
        return *this;
      }

#pragma endregion Unary
    };
  }
}