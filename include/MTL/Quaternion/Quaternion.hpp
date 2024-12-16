#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"

namespace Krys::MTL
{
  template <IsArithmeticT TComponent>
  class Quaternion
  {
  public:
    using quat_t = Quaternion<TComponent>;
    using component_t = TComponent;

  private:
    component_t w, x, y, z;

  public:
#pragma region Construction

    explicit constexpr Quaternion() noexcept
        : w(component_t(0)), x(component_t(0)), y(component_t(0)), z(component_t(0))
    {
    }

    explicit constexpr Quaternion(component_t w, component_t x, component_t y, component_t z) noexcept
        : w(w), x(x), y(y), z(z)
    {
    }

    constexpr Quaternion(const quat_t &other) noexcept : w(other.w), x(other.x), y(other.y), z(other.z)
    {
    }

    constexpr Quaternion(const quat_t &&other) noexcept
        : w(std::move(other.w)), x(std::move(other.x)), y(std::move(other.y)), z(std::move(other.z))
    {
    }

#pragma endregion Construction

#pragma region Assignment

    constexpr quat_t &operator=(const quat_t &other) noexcept
    {
      w = other.w;
      x = other.x;
      y = other.y;
      z = other.z;
      return *this;
    }

    constexpr quat_t &operator=(const quat_t &&other) noexcept
    {
      w = std::move(other.w);
      x = std::move(other.x);
      y = std::move(other.y);
      z = std::move(other.z);
      return *this;
    }

#pragma endregion Assignment

#pragma region Addition

    NO_DISCARD constexpr quat_t operator+(const quat_t &other) const noexcept
    {
      return quat_t(w + other.w, x + other.x, y + other.y, z + other.z);
    }

    constexpr quat_t &operator+=(const quat_t &other) noexcept
    {
      *this = *this + other;
      return *this;
    }

#pragma endregion Addition

#pragma region Subtraction

    NO_DISCARD constexpr quat_t operator-(const quat_t &other) const noexcept
    {
      return quat_t(w - other.w, x - other.x, y - other.y, z - other.z);
    }

    constexpr quat_t &operator-=(const quat_t &other) noexcept
    {
      *this = *this - other;
      return *this;
    }

#pragma endregion Subtraction

#pragma region Multiplication

    NO_DISCARD constexpr quat_t operator*(const component_t scalar) const noexcept
    {
      return quat_t(w * scalar, x * scalar, y * scalar, z * scalar);
    }

    constexpr quat_t &operator*=(const component_t scalar) noexcept
    {
      *this = *this * scalar;
      return *this;
    }

    /// @brief Calculates the Hamilton product of two quaternions.
    /// @param other the other quaternion.
    NO_DISCARD constexpr quat_t operator*(const quat_t &other) const noexcept
    {
      component_t w1 = w;
      component_t x1 = x;
      component_t y1 = y;
      component_t z1 = z;

      component_t w2 = other.w;
      component_t x2 = other.x;
      component_t y2 = other.y;
      component_t z2 = other.z;

      w = w1 * w2 - x1 * x2 - y1 * y2 - z1 * z2;
      x = w1 * x2 + x1 * w2 + y1 * z2 - z1 * y2;
      y = w1 * y2 + y1 * w2 + z1 * x2 - x1 * z2;
      z = w1 * z2 + z1 * w2 + x1 * y2 - y1 * x2;

      return *this;
    }

    /// @brief Calculates the Hamilton product of two quaternions.
    /// @param other the other quaternion.
    constexpr quat_t &operator*=(const quat_t &other) noexcept
    {
      *this = *this * other;
      return *this;
    }

#pragma endregion Multiplication

#pragma region Division

    NO_DISCARD constexpr quat_t operator/(const component_t scalar) const noexcept
    {
      // TODO: assert not zero
      return quat_t(w / scalar, x / scalar, y / scalar, z / scalar);
    }

    constexpr quat_t &operator/=(const component_t scalar) noexcept
    {
      // TODO: assert not zero
      *this = *this / scalar;
      return *this;
    }

#pragma endregion Division
  };
}