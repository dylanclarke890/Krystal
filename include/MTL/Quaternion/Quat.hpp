#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Core/Debug/Macros.hpp"
#include "MTL/Power/Pow.hpp"
#include "MTL/Power/Sqrt.hpp"
#include "MTL/Trigonometric/Acos.hpp"
#include "MTL/Trigonometric/Cos.hpp"
#include "MTL/Trigonometric/Sin.hpp"
#include "MTL/Vectors/Vec3.hpp"

namespace Krys::MTL
{
  template <IsArithmeticT TComponent>
  class Quaternion;

  template <typename T>
  using quaternion_t = MTL::Quaternion<T>;
  using Quat = quaternion_t<float>;

  /// @brief Represents a quaternion, which is a rotation around a 3D axis.
  /// @tparam TComponent the type of the components of the quaternion.
  template <IsArithmeticT TComponent>
  class Quaternion
  {
  public:
    using component_t = TComponent;
    using quat_t = Quaternion<component_t>;
    using vec_t = vector_t<component_t, 3>;

  public:
    /// @brief Construct a unit quaternion.
    explicit constexpr Quaternion() noexcept
        : w(component_t(1.0)), x(component_t(0)), y(component_t(0)), z(component_t(0))
    {
    }

    /// @brief Construct a quaternion with the given components.
    explicit constexpr Quaternion(component_t w, component_t x, component_t y, component_t z) noexcept
        : w(w), x(x), y(y), z(z)
    {
    }

    /// @brief Construct a quaternion which represents a rotation around an axis
    /// @param axis the axis of the rotation.
    /// @param angle the angle of the rotation.
    explicit constexpr Quaternion(const vec_t &axis, component_t angle) noexcept
    {
      component_t halfAngle = angle / component_t(2);
      component_t sinHalfAngle = Sin(halfAngle);
      w = Cos(halfAngle);
      x = axis.x * sinHalfAngle;
      y = axis.y * sinHalfAngle;
      z = axis.z * sinHalfAngle;

      Normalize();
    }

    /// @brief Construct a quaternion from Euler angles.
    /// @param yaw the yaw angle.
    /// @param pitch the pitch angle.
    /// @param roll the roll angle.
    constexpr Quaternion(float yaw, float pitch, float roll) : Quaternion()
    {
      const auto cy = Cos(yaw * 0.5f);
      const auto sy = Sin(yaw * 0.5f);
      const auto cp = Cos(pitch * 0.5f);
      const auto sp = Sin(pitch * 0.5f);
      const auto cr = Cos(roll * 0.5f);
      const auto sr = Sin(roll * 0.5f);

      w = cr * cp * cy + sr * sp * sy;
      x = sr * cp * cy - cr * sp * sy;
      y = cr * sp * cy + sr * cp * sy;
      z = cr * cp * sy - sr * sp * cy;
    }

    constexpr Quaternion(const quat_t &other) noexcept = default;
    constexpr quat_t &operator=(const quat_t &other) noexcept = default;

    constexpr Quaternion(const quat_t &&other) noexcept = default;
    constexpr quat_t &operator=(const quat_t &&other) noexcept = default;

    constexpr bool operator==(const quat_t &other) const noexcept = default;
    constexpr bool operator!=(const quat_t &other) const noexcept = default;

    /// @brief Adds a quaternion to another quaternion.
    /// @param other the other quaternion.
    NO_DISCARD constexpr quat_t operator+(const quat_t &other) const noexcept
    {
      return quat_t(w + other.w, x + other.x, y + other.y, z + other.z);
    }

    /// @brief Adds a quaternion to this quaternion.
    /// @param other the other quaternion.
    constexpr quat_t &operator+=(const quat_t &other) noexcept
    {
      *this = *this + other;
      return *this;
    }

    /// @brief Subtracts a quaternion from another quaternion.
    /// @param other the other quaternion.
    NO_DISCARD constexpr quat_t operator-(const quat_t &other) const noexcept
    {
      return quat_t(w - other.w, x - other.x, y - other.y, z - other.z);
    }

    /// @brief Subtracts a quaternion from this quaternion.
    /// @param other the other quaternion.
    constexpr quat_t &operator-=(const quat_t &other) noexcept
    {
      *this = *this - other;
      return *this;
    }

    /// @brief Multiplies a quaternion by a scalar.
    /// @param scalar the scalar.
    NO_DISCARD constexpr quat_t operator*(const component_t scalar) const noexcept
    {
      return quat_t(w * scalar, x * scalar, y * scalar, z * scalar);
    }

    /// @brief Multiplies this quaternion by a scalar.
    /// @param scalar the scalar.
    constexpr quat_t &operator*=(const component_t scalar) noexcept
    {
      *this = *this * scalar;
      return *this;
    }

    /// @brief Multiplies a quaternion by another quaternion, composing the rotations.
    /// @param other the other quaternion.
    /// @details Calculates the Hamilton product of two quaternions.
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

    /// @brief Multiplies this quaternion by another quaternion, composing the rotations.
    /// @param other the other quaternion.
    /// @details Calculates the Hamilton product of two quaternions.
    constexpr quat_t &operator*=(const quat_t &other) noexcept
    {
      *this = *this * other;
      return *this;
    }

    /// @brief Divides a quaternion by a scalar.
    /// @param scalar the scalar.
    NO_DISCARD constexpr quat_t operator/(const component_t scalar) const noexcept
    {
      KRYS_ASSERT(scalar != 0, "Division by zero.");
      return quat_t(w / scalar, x / scalar, y / scalar, z / scalar);
    }

    /// @brief Divides this quaternion by a scalar.
    /// @param scalar the scalar.
    constexpr quat_t &operator/=(const component_t scalar) noexcept
    {
      KRYS_ASSERT(scalar != 0, "Division by zero.");
      *this = *this / scalar;
      return *this;
    }

    /// @brief Negates the quaternion.
    NO_DISCARD constexpr quat_t operator-() const noexcept
    {
      return quat_t(-w, -x, -y, -z);
    }

    /// @brief Normalize the quaternion.
    constexpr void Normalize() noexcept
    {
      const auto magnitude = Pow(w, 2.0f) + Pow(x, 2.0f) + Pow(y, 2.0f) + Pow(z, 2.0f);
      if (magnitude == 0.0f)
      {
        w = 1.0f;
      }
      else
      {
        const auto d = Sqrt(magnitude);

        w /= d;
        x /= d;
        y /= d;
        z /= d;
      }

      return *this;
    }

    /// @brief Get the length of the quaternion.
    NO_DISCARD constexpr component_t Length() const noexcept
    {
      return Sqrt(w * w + x * x + y * y + z * z);
    }

    /// @brief Get the dot product of two quaternions.
    NO_DISCARD constexpr component_t Dot(const quat_t &other) const noexcept
    {
      return w * other.w + x * other.x + y * other.y + z * other.z;
    }

    /// @brief Spherically interpolates between two quaternions.
    /// @param other the other quaternion.
    /// @param t the interpolation factor.
    NO_DISCARD constexpr quat_t Slerp(const quat_t &other, component_t t) const noexcept
    {
      quat_t q1 = *this;
      quat_t q2 = other;

      component_t dot = q1.Dot(q2);

      if (dot < 0.0f)
      {
        q2 = -q2;
        dot = -dot;
      }

      constexpr component_t threshold = 0.9995f;
      if (dot > threshold)
      {
        quat_t result = q1 + (q2 - q1) * t;
        result.Normalize();
        return result;
      }

      dot = Clamp(dot, -1.0f, 1.0f);
      component_t theta = Acos(dot);
      component_t sinTheta = Sin(theta);
      component_t sinTTheta = Sin(t * theta);

      component_t s0 = Cos(t * theta) - dot * sinTTheta / sinTheta;
      component_t s1 = sinTTheta / sinTheta;

      return q1 * s0 + q2 * s1;
    }

  private:
    component_t w, x, y, z;
  };
}