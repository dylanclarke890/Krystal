#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Core/Debug/Macros.hpp"
#include "MTL/Common/Clamp.hpp"
#include "MTL/Matrices/Mat3x3.hpp"
#include "MTL/Matrices/Mat3x4.hpp"
#include "MTL/Matrices/Mat4x4.hpp"
#include "MTL/Power/Pow.hpp"
#include "MTL/Power/Sqrt.hpp"
#include "MTL/Trigonometric/Acos.hpp"
#include "MTL/Trigonometric/Cos.hpp"
#include "MTL/Trigonometric/Sin.hpp"
#include "MTL/Vectors/Ext/Geometric.hpp"
#include "MTL/Vectors/Vec3.hpp"
#include "MTL/Vectors/Vec4.hpp"

namespace Krys::MTL
{
  template <IsArithmeticT TComponent>
  class Quaternion;
}

namespace Krys::Impl
{
  template <IsArithmeticT TComponent, typename TMatrix>
  constexpr void SetQuatFrom(MTL::Quaternion<TComponent> &q, const TMatrix &m) noexcept
  {
    // The rotation matrix is of form: (Eric Lengyel's Mathematics for 3D Game Programming and Computer
    // Graphics 2nd ed., p. 92)
    // 1 - 2y^2 - 2z^2        2xy - 2wz            2xz + 2wy
    //    2xy + 2wz        1 - 2x^2 - 2z^2         2yz - 2wx
    //    2xz - 2wy           2yz + 2wx         1 - 2x^2 - 2y^2

    // The element w is easiest picked up as a sum of the diagonals.
    float r = m[0][0] + m[1][1] + m[2][2];
    // Above, r == 3 - 4(x^2+y^2+z^2) == 4(1-x^2-y^2-z^2) - 1 == 4*w^2 - 1.

    if (r > 0) // In this case, |w| > 1/2.
    {
      // We have two choices for the sign of w, arbitrarily pick the positive.
      q.w = MTL::Sqrt(r + 1.f) * 0.5f;
      float inv4w = 1.f / (4.f * q.w);
      q.x = (m[2][1] - m[1][2]) * inv4w;
      q.y = (m[0][2] - m[2][0]) * inv4w;
      q.z = (m[1][0] - m[0][1]) * inv4w;
    }
    // If |q.x| is larger than |q.y| and |q.z|, extract it first. This gives best stability, and we know
    // below x can't be zero.
    else if (m[0][0] > m[1][1] && m[0][0] > m[2][2])
    {
      // We have two choices for the sign of x, arbitrarily pick the positive.
      q.x = MTL::Sqrt(1.f + m[0][0] - m[1][1] - m[2][2]) * 0.5f;
      const float x4 = 1.f / (4.f * q.x);
      q.y = (m[0][1] + m[1][0]) * x4;
      q.z = (m[0][2] + m[2][0]) * x4;
      q.w = (m[2][1] - m[1][2]) * x4;
    }
    // |q.y| is larger than |q.x| and |q.z|
    else if (m[1][1] > m[2][2])
    {
      // We have two choices for the sign of y, arbitrarily pick the positive.
      q.y = MTL::Sqrt(1.f + m[1][1] - m[0][0] - m[2][2]) * 0.5f;
      const float y4 = 1.f / (4.f * q.y);
      q.x = (m[0][1] + m[1][0]) * y4;
      q.z = (m[1][2] + m[2][1]) * y4;
      q.w = (m[0][2] - m[2][0]) * y4;
    }
    // |q.z| is larger than |q.x| or |q.y|
    else
    {
      // We have two choices for the sign of z, arbitrarily pick the positive.
      q.z = MTL::Sqrt(1.f + m[2][2] - m[0][0] - m[1][1]) * 0.5f;

      const float z4 = 1.f / (4.f * q.z);
      q.x = (m[0][2] + m[2][0]) * z4;
      q.y = (m[1][2] + m[2][1]) * z4;
      q.w = (m[1][0] - m[0][1]) * z4;
    }
  }
}

namespace Krys
{
  template <IsArithmeticT T>
  using quaternion_t = MTL::Quaternion<T>;
  using Quat = quaternion_t<float>;

  namespace MTL
  {
    /// @brief Represents an axis-angle pair, which is a rotation around a 3D axis.
    template <IsArithmeticT TComponent>
    struct AxisAngle final
    {
      /// @brief The axis of rotation.
      vec3_t<TComponent> Axis;

      /// @brief The angle of rotation, in radians.
      float AngleRadians;
    };

    /// @brief Represents a quaternion, which is a rotation around a 3D axis.
    /// @tparam TComponent the underlying type of the quaternion components.
    template <IsArithmeticT TComponent>
    class Quaternion
    {
    public:
      using component_t = TComponent;
      using quat_t = Quaternion<component_t>;
      using axis_angle_t = AxisAngle<component_t>;

      component_t w, x, y, z;

    public:
      constexpr ~Quaternion() noexcept = default;

      constexpr bool operator==(const quat_t &other) const noexcept = default;
      constexpr bool operator!=(const quat_t &other) const noexcept = default;

#pragma region Constructors

      constexpr Quaternion(const quat_t &other) noexcept = default;
      constexpr quat_t &operator=(const quat_t &other) noexcept = default;

      constexpr Quaternion(const quat_t &&other) noexcept : w(other.w), x(other.x), y(other.y), z(other.z)
      {
      }

      constexpr quat_t &operator=(const quat_t &&other) noexcept
      {
        w = other.w;
        x = other.x;
        y = other.y;
        z = other.z;
        return *this;
      }

      /// @brief Constructs the identity quaternion.
      /// @details The identity quaternion has a real part of 1 and an imaginary part of 0, it represents no
      /// rotation.
      explicit constexpr Quaternion() noexcept
          : w(component_t(1)), x(component_t(0)), y(component_t(0)), z(component_t(0))
      {
      }

      /// @brief Construct a quaternion with the given components.
      /// @param w the real part of the quaternion.
      /// @param x the imaginary part of the quaternion along the x-axis.
      /// @param y the imaginary part of the quaternion along the y-axis.
      /// @param z the imaginary part of the quaternion along the z-axis.
      /// @note The quaternion is not Normalized after construction.
      explicit constexpr Quaternion(component_t w, component_t x, component_t y, component_t z) noexcept
          : w(w), x(x), y(y), z(z)
      {
      }

      /// @brief Construct a quaternion from a rotation matrix.
      /// @param m the rotation matrix.
      explicit constexpr Quaternion(const mat3x3_t<component_t> &m) noexcept : Quaternion()
      {
        Set(m);
      }

      /// @brief Construct a quaternion from a rotation matrix.
      /// @param m the rotation matrix.
      explicit constexpr Quaternion(const mat3x4_t<component_t> &m) noexcept : Quaternion()
      {
        Set(m);
      }

      /// @brief Construct a quaternion from a rotation matrix.
      /// @param m the rotation matrix.
      explicit constexpr Quaternion(const mat4x4_t<component_t> &m) noexcept : Quaternion()
      {
        Set(m);
      }

      /// @brief Construct a quaternion from a rotation axis and an angle of rotation around that axis.
      /// @param axis the Normalized axis of the rotation.
      /// @param angleRadians the angle of the rotation, in radians.
      explicit constexpr Quaternion(const vec3_t<component_t> &axis, component_t angleRadians) noexcept
      {
        SetFromAxisAngle({axis, angleRadians});
      }

      /// @brief Construct a quaternion from a rotation axis and an angle of rotation around that axis.
      /// @param axis the Normalized axis of the rotation. The w component of the vector should be zero.
      /// @param angleRadians the angle of the rotation, in radians.
      explicit constexpr Quaternion(const vec4_t<component_t> &axis, component_t angleRadians) noexcept
      {
        SetFromAxisAngle({Vec3 {axis.x, axis.y, axis.z}, angleRadians});
      }

      /// @brief Construct a quaternion from a rotation axis and an angle of rotation around that axis.
      /// @param axisAngle the axis-angle pair.
      explicit constexpr Quaternion(const axis_angle_t &axisAngle) noexcept
      {
        SetFromAxisAngle(axisAngle);
      }

#pragma endregion Constructors

#pragma region Set

      /// @brief Set the quaternion from a rotation matrix.
      /// @param m the rotation matrix.
      constexpr void Set(const mat3x3_t<component_t> &m) noexcept
      {
        Impl::SetQuatFrom(*this, m);
      }

      /// @brief Set the quaternion from a rotation matrix.
      /// @param m the rotation matrix.
      constexpr void Set(const mat3x4_t<component_t> &m) noexcept
      {
        Impl::SetQuatFrom(*this, m);
      }

      /// @brief Set the quaternion from a rotation matrix.
      /// @param m the rotation matrix.
      constexpr void Set(const mat4x4_t<component_t> &m) noexcept
      {
        Impl::SetQuatFrom(*this, m);
      }

      /// @brief Directly set the components of the quaternion.
      /// @param w The real part of the quaternion.
      /// @param x The imaginary part of the quaternion along the x-axis.
      /// @param y The imaginary part of the quaternion along the y-axis.
      /// @param z The imaginary part of the quaternion along the z-axis.
      constexpr void Set(float w, float x, float y, float z) noexcept
      {
        this->w = w;
        this->x = x;
        this->y = y;
        this->z = z;
      }

      /// @brief Directly set the components of the quaternion.
      /// @param v The vector to set the quaternion to.
      constexpr void Set(const vec4_t<component_t> &v) noexcept
      {
        Set(v.w, v.x, v.y, v.z);
      }

#pragma endregion Set

#pragma region AxisAngle

      /// @brief Construct a quaternion from a rotation axis and an angle of rotation around that axis.
      /// @param a the axis-angle pair. a.Axis must be Normalized.
      constexpr void SetFromAxisAngle(const axis_angle_t &a) noexcept
      {
        const auto halfAngle = a.AngleRadians * component_t(0.5);
        const auto sinHalfAngle = Sin(halfAngle);
        w = Cos(halfAngle);
        x = a.Axis.x * sinHalfAngle;
        y = a.Axis.y * sinHalfAngle;
        z = a.Axis.z * sinHalfAngle;
      }

      /// @brief Construct a quaternion from a rotation axis and an angle of rotation around that axis.
      /// @param axis the Normalized axis of the rotation.
      /// @param angleRadians the angle of the rotation, in radians.
      constexpr void SetFromAxisAngle(const vec3_t<component_t> &axis, component_t angleRadians) noexcept
      {
        SetFromAxisAngle({axis, angleRadians});
      }

      /// @brief Get the axis-angle representation of the quaternion.
      /// @return the axis-angle representation of the quaternion.
      NO_DISCARD constexpr axis_angle_t ToAxisAngle() const noexcept
      {
        const auto halfAngle = Acos(w);
        const auto sinHalfAngle = Sin(halfAngle);
        if (sinHalfAngle < std::numeric_limits<component_t>::epsilon())
          return {vec3_t<component_t>(1.0f, 0.0f, 0.0f), 0.0f};

        const auto angle = 2.0f * halfAngle;
        return {vec3_t<component_t>(x / sinHalfAngle, y / sinHalfAngle, z / sinHalfAngle), angle};
      }

      /// @brief Get the axis-angle representation of the quaternion. The quaternion must be Normalized.
      /// @param axis the axis of rotation.
      /// @param angleRadians the angle of rotation, in radians.
      constexpr void ToAxisAngle(vec3_t<component_t> &axis, component_t &angleRadians) const noexcept
      {
        const auto a = ToAxisAngle();
        axis = a.Axis;
        angleRadians = a.AngleRadians;
      }

      /// @brief Get the axis of rotation of the quaternion.
      NO_DISCARD vec3_t<component_t> GetAxis() const noexcept
      {
        const auto sinHalfAngle = Sqrt(x * x + y * y + z * z);

        // Handle the case where the quaternion represents no rotation
        if (sinHalfAngle < std::numeric_limits<component_t>::epsilon())
          // No meaningful axis; return a default axis
          return vec3_t<component_t>(1.0f, 0.0f, 0.0f);

        // Normalize the vector part to get the rotation axis
        return vec3_t<component_t>(x / sinHalfAngle, y / sinHalfAngle, z / sinHalfAngle);
      }

      /// @brief Get the angle of rotation around the axis in radians. The quaternion must be Normalized.
      /// @return the angle of rotation around the axis in radians.
      NO_DISCARD component_t GetAngle() const noexcept
      {
        return 2.0f * Acos(w);
      }

      /// @brief Get the angle between this and the target orientation (the shortest route) in radians.
      /// Both this and the target quaternion must be Normalized.
      /// @param target the target orientation.
      NO_DISCARD component_t AngleBetween(const quat_t &target) const noexcept
      {
        // Compute the dot product
        const auto dot = Dot(target);

        // Clamp the dot product to the valid range [-1, 1] to avoid numerical issues
        const auto clampedDot = Clamp(Abs(dot), -1.0f, 1.0f);

        // Compute the shortest angle
        return 2.0f * Acos(clampedDot);
      }

      /// @brief Get the axis of rotation to get from this orientation to target orientation (the shortest
      /// route).
      /// @param target the target orientation.
      NO_DISCARD vec3_t<component_t> AxisFromTo(const quat_t &target) const noexcept
      {
        // Compute the relative rotation quaternion
        const quat_t relative = target * Inverse(*this);

        // Extract the vector part of the relative quaternion
        const vec3_t<component_t> axis(relative.x, relative.y, relative.z);

        // Normalize the axis
        const component_t length = Length(axis);
        if (length < std::numeric_limits<component_t>::epsilon())
          // If the axis length is near zero, return a default axis
          return vec3_t<component_t>(1.0f, 0.0f, 0.0f);
        else
          return axis / length; // Return the normalized axis
      }

#pragma endregion AxisAngle

#pragma region Addition

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

#pragma endregion Addition

#pragma region Subtraction

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

#pragma endregion Subtraction

#pragma region Multiplication

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
      /// @note The product q1 * q2 returns a quaternion that concatenates the two orientation rotations.
      /// The rotation q2 is applied first before q1.
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

        auto w3 = w1 * w2 - x1 * x2 - y1 * y2 - z1 * z2;
        auto x3 = w1 * x2 + x1 * w2 + y1 * z2 - z1 * y2;
        auto y3 = w1 * y2 + y1 * w2 + z1 * x2 - x1 * z2;
        auto z3 = w1 * z2 + z1 * w2 + x1 * y2 - y1 * x2;

        return quat_t {w3, x3, y3, z3};
      }

      /// @brief Multiplies this quaternion by another quaternion, composing the rotations.
      /// @param other the other quaternion.
      /// @details Calculates the Hamilton product of two quaternions.
      constexpr quat_t &operator*=(const quat_t &other) noexcept
      {
        *this = *this * other;
        return *this;
      }

      /// @brief Transforms the given vector by this Quaternion.
      /// @note Technically, this function does not perform a simple multiplication of 'q * v',
      /// but instead performs a conjugation operation 'q*v*q^-1'. This corresponds to transforming
      /// the given vector by this Quaternion.
      constexpr vec3_t<component_t> operator*(const vec3_t<component_t> &v) const noexcept
      {
        const auto q = *this * vec4_t<component_t>(v, 0);
        return vec3_t<component_t>(q.x, q.y, q.z);
      }

      /// @brief Transforms the given vector by this Quaternion.
      /// @note Technically, this function does not perform a simple multiplication of 'q * v',
      /// but instead performs a conjugation operation 'q*v*q^-1'. This corresponds to transforming
      /// the given vector by this Quaternion.
      constexpr vec4_t<component_t> operator*(const vec4_t<component_t> &v) const noexcept
      {
        return vec4_t<component_t>(
          w * v.x + x * v.w + y * v.z - z * v.y, w * v.y - x * v.z + y * v.w + z * v.x,
          w * v.z + x * v.y - y * v.x + z * v.w, w * v.w - x * v.x - y * v.y - z * v.z);
      }

#pragma endregion Multiplication

#pragma region Division

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

      /// @brief Divides a quaternion by another.
      /// @note Division "a / b" results in a quaternion that rotates the orientation b to coincide with the
      /// orientation a.
      NO_DISCARD constexpr quat_t operator/(const quat_t &rhs) const noexcept
      {
        return *this * rhs.Inverse();
      }

      /// @brief Divides this quaternion by another.
      /// @note Division "a / b" results in a quaternion that rotates the orientation b to coincide with the
      /// orientation a.
      constexpr quat_t &operator/=(const quat_t &rhs) noexcept
      {
        *this = *this / rhs;
        return *this;
      }

#pragma endregion Division

#pragma region ToMatrix

      /// @brief Converts this quaternion to a 3x3 rotation matrix.
      NO_DISCARD constexpr mat3x3_t<component_t> ToMat3x3() const noexcept
      {
        KRYS_ASSERT(IsNormalized(), "Quaternion is not normalized.");

        const auto x2 = x + x;
        const auto y2 = y + y;
        const auto z2 = z + z;
        const auto xx = x * x2;
        const auto xy = x * y2;
        const auto xz = x * z2;
        const auto yy = y * y2;
        const auto yz = y * z2;
        const auto zz = z * z2;
        const auto wx = w * x2;
        const auto wy = w * y2;
        const auto wz = w * z2;

        return mat3x3_t<component_t>(1 - (yy + zz), xy - wz, xz + wy, xy + wz, 1 - (xx + zz), yz - wx,
                                     xz - wy, yz + wx, 1 - (xx + yy));
      }

      /// @brief Converts this quaternion to a 3x4 rotation matrix.
      NO_DISCARD constexpr mat3x4_t<component_t> ToMat3x4() const noexcept
      {
        KRYS_ASSERT(IsNormalized(), "Quaternion is not normalized.");

        const auto x2 = x + x;
        const auto y2 = y + y;
        const auto z2 = z + z;
        const auto xx = x * x2;
        const auto xy = x * y2;
        const auto xz = x * z2;
        const auto yy = y * y2;
        const auto yz = y * z2;
        const auto zz = z * z2;
        const auto wx = w * x2;
        const auto wy = w * y2;
        const auto wz = w * z2;

        return mat3x4_t<component_t>(1 - (yy + zz), xy - wz, xz + wy, 0, xy + wz, 1 - (xx + zz), yz - wx, 0,
                                     xz - wy, yz + wx, 1 - (xx + yy), 0);
      }

      /// @brief Converts this quaternion to a 4x4 rotation matrix.
      NO_DISCARD constexpr mat4x4_t<component_t> ToMat4x4() const noexcept
      {
        KRYS_ASSERT(IsNormalized(), "Quaternion is not normalized.");

        const auto x2 = x + x;
        const auto y2 = y + y;
        const auto z2 = z + z;
        const auto xx = x * x2;
        const auto xy = x * y2;
        const auto xz = x * z2;
        const auto yy = y * y2;
        const auto yz = y * z2;
        const auto zz = z * z2;
        const auto wx = w * x2;
        const auto wy = w * y2;
        const auto wz = w * z2;

        return mat4x4_t<component_t>(1 - (yy + zz), xy - wz, xz + wy, 0, xy + wz, 1 - (xx + zz), yz - wx, 0,
                                     xz - wy, yz + wx, 1 - (xx + yy), 0, 0, 0, 0, 1);
      }

      /// @brief Converts this quaternion to a 4x4 rotation matrix with translation.
      /// @param translation the translation vector.
      NO_DISCARD constexpr mat4x4_t<component_t>
        ToMat4x4(const vec3_t<component_t> &translation) const noexcept
      {
        KRYS_ASSERT(IsNormalized(), "Quaternion is not normalized.");

        const auto x2 = x + x;
        const auto y2 = y + y;
        const auto z2 = z + z;
        const auto xx = x * x2;
        const auto xy = x * y2;
        const auto xz = x * z2;
        const auto yy = y * y2;
        const auto yz = y * z2;
        const auto zz = z * z2;
        const auto wx = w * x2;
        const auto wy = w * y2;
        const auto wz = w * z2;

        return mat4x4_t<component_t>(1 - (yy + zz), xy - wz, xz + wy, translation.x, xy + wz, 1 - (xx + zz),
                                     yz - wx, translation.y, xz - wy, yz + wx, 1 - (xx + yy), translation.z,
                                     0, 0, 0, 1);
      }

      /// @brief Converts this quaternion to a 4x4 rotation matrix with translation.
      /// @param translation the translation vector. The w component of the vector is ignored.
      NO_DISCARD constexpr mat4x4_t<component_t>
        ToMat4x4(const vec4_t<component_t> &translation) const noexcept
      {
        KRYS_ASSERT(IsNormalized(), "Quaternion is not normalized.");
        return ToMat4x4(vec3_t<component_t>(translation.x, translation.y, translation.z));
      }

#pragma endregion ToMatrix

      /// @brief Negates this quaternion.
      NO_DISCARD constexpr quat_t operator-() const noexcept
      {
        return quat_t(-w, -x, -y, -z);
      }

      /// @brief Unary plus operator. No effect.
      NO_DISCARD constexpr quat_t operator+() const noexcept
      {
        return *this;
      }

      /// @brief Get the conjugate of this quaternion.
      /// @note The conjugate of a quaternion is the quaternion with the same real part and the negated
      /// imaginary.
      /// @note (q* = (w, -x, -y, -z))
      /// @return the conjugate of this quaternion.
      NO_DISCARD constexpr quat_t Conjugate() const noexcept
      {
        return quat_t(w, -x, -y, -z);
      }

      /// @brief Get the dot product of this and another quaternion.
      /// @param other the other quaternion.
      /// @return the dot product of the two quaternions.
      NO_DISCARD constexpr component_t Dot(const quat_t &other) const noexcept
      {
        return w * other.w + x * other.x + y * other.y + z * other.z;
      }

      /// @brief Get the inverse of this quaternion.
      /// @note The inverse of a quaternion is the conjugate of the quaternion divided by the dot product of
      /// the quaternion with itself.
      /// @note (q^-1 = q^* / (q * q))
      NO_DISCARD constexpr quat_t Inverse() const noexcept
      {
        KRYS_ASSERT(Dot(*this) != 0, "Cannot invert a zero quaternion.");
        return Conjugate() / Dot(*this);
      }

      /// @brief Get the length of this quaternion.
      /// @return the length of the quaternion.
      NO_DISCARD constexpr component_t Length() const noexcept
      {
        return Sqrt(w * w + x * x + y * y + z * z);
      }

      /// @brief Normalize this quaternion.
      constexpr quat_t &Normalize() noexcept
      {
        KRYS_ASSERT(Length() != 0, "Cannot normalize a zero quaternion.");

        *this /= Length();
        return *this;
      }

      /// @brief Check whether this quaternion is normalized.
      /// @return true if the quaternion is normalized, false otherwise.
      NO_DISCARD constexpr bool IsNormalized() const noexcept
      {
        return Abs(Length() - 1) < (std::numeric_limits<component_t>::epsilon() * 10);
      }
    };
  }
}