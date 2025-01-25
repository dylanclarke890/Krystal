#pragma once

#include "Base/Attributes.hpp"
#include "MTL/Quaternion/Quat.hpp"
#include "MTL/Vectors/Ext/Geometric.hpp"
#include "MTL/Vectors/Vec3.hpp"

namespace Krys::MTL
{
  /// @brief Rotates the given vector by the given quaternion.
  /// @param q the quaternion. Must be normalized.
  /// @param v the vector to rotate.
  /// @return the rotated vector.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr vec3_t<TComponent> Rotate(const Quaternion<TComponent> &q,
                                                 const vec3_t<TComponent> &v) noexcept
  {
    // Convert the vector to a quaternion with w = 0
    Quaternion<TComponent> quat(0.0f, v.x, v.y, v.z);

    // Perform the rotation: q * v * q^-1
    // The conjugate of a quaternion is the same as the inverse, if the quaternion is normalized.
    Quaternion<TComponent> rotated = q * quat * q.Conjugate();

    // Extract the rotated vector (x, y, z) from the resulting quaternion
    return vec3_t<TComponent>(rotated.x, rotated.y, rotated.z);
  }

  /// @brief Rotates the given vector by the given quaternion.
  /// @tparam TComponent the component type of the quaternion and the vector.
  /// @param quat the quaternion.
  /// @param x the x component of the vector.
  /// @param y the y component of the vector.
  /// @param z the z component of the vector.
  /// @return the rotated vector.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr vec3_t<TComponent> Rotate(const Quaternion<TComponent> &q, TComponent x, TComponent y,
                                                 TComponent z) noexcept
  {
    return Rotate(q, vec3_t<TComponent>(x, y, z));
  }

  /// @brief Creates a new quaternion that rotates about the positive X axis by the given angle.
  /// @tparam TComponent the component type of the quaternion.
  /// @param angle the angle of rotation, in radians.
  /// @return the quaternion that rotates about the positive X axis by the given angle.
  template <IsArithmeticT TComponent>
  NO_DISCARD Quaternion<TComponent> RotateX(TComponent angle) noexcept
  {
    return Quaternion<TComponent>(vec3_t<TComponent>(1, 0, 0), angle);
  }

  /// @brief Creates a new quaternion that rotates about the positive Y axis by the given angle.
  /// @tparam TComponent the component type of the quaternion.
  /// @param angle the angle of rotation, in radians.
  /// @return the quaternion that rotates about the positive Y axis by the given angle.
  template <IsArithmeticT TComponent>
  NO_DISCARD Quaternion<TComponent> RotateY(TComponent angle) noexcept
  {
    return Quaternion<TComponent>(vec3_t<TComponent>(0, 1, 0), angle);
  }

  /// @brief Creates a new quaternion that rotates about the positive Z axis by the given angle.
  /// @tparam TComponent the component type of the quaternion.
  /// @param angle the angle of rotation, in radians.
  /// @return the quaternion that rotates about the positive Z axis by the given angle.
  template <IsArithmeticT TComponent>
  NO_DISCARD Quaternion<TComponent> RotateZ(TComponent angle) noexcept
  {
    return Quaternion<TComponent>(vec3_t<TComponent>(0, 0, 1), angle);
  }

  /// @brief Creates a new quaternion that rotates about the given axis by the given angle.
  /// @tparam TComponent the component type of the quaternion.
  /// @param axis the axis of rotation.
  /// @param angle the angle of rotation, in radians.
  /// @return a quaternion that rotates about the given axis by the given angle.
  template <IsArithmeticT TComponent>
  NO_DISCARD Quaternion<TComponent> RotateAxisAngle(const vec3_t<TComponent> &axis, TComponent angle) noexcept
  {
    return Quaternion<TComponent>(axis, angle);
  }

  /// @brief Get the world X axis from the given quaternion.
  /// @tparam TComponent the component type of the quaternion.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr vec3_t<TComponent> GetWorldX(const Quaternion<TComponent> &q) noexcept
  {
    return Rotate(q, vec3_t<TComponent>(1, 0, 0));
  }

  /// @brief Get the world Y axis from the given quaternion.
  /// @tparam TComponent the component type of the quaternion.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr vec3_t<TComponent> GetWorldY(const Quaternion<TComponent> &q) noexcept
  {
    return Rotate(q, vec3_t<TComponent>(0, 1, 0));
  }

  /// @brief Get the world Z axis from the given quaternion.
  /// @tparam TComponent the component type of the quaternion.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr vec3_t<TComponent> GetWorldZ(const Quaternion<TComponent> &q) noexcept
  {
    return Rotate(q, vec3_t<TComponent>(0, 0, 1));
  }

  /// @brief Creates a new quaternion that rotates sourceDirection vector (in world space) to coincide with
  /// the targetDirection vector (in world space). Rotation is performed around the origin. The vectors
  /// sourceDirection and targetDirection are assumed to be normalized.
  /// @tparam TComponent the component type of the vectors.
  /// @param sourceDirection the source direction vector.
  /// @param targetDirection the target direction vector.
  /// @note There are multiple such rotations - this function returns the rotation that has the shortest angle
  /// (when decomposed to axis-angle notation).
  /// @return the quaternion that rotates sourceDirection to targetDirection.
  template <IsFloatingPointT TComponent>
  NO_DISCARD Quaternion<TComponent> RotateFromTo(const vec3_t<TComponent> &sourceDirection,
                                                 const vec3_t<TComponent> &targetDirection) noexcept
  {
    // If sourceDirection == targetDirection, the cross product comes out zero, and normalization would fail.
    // In that case, pick an arbitrary axis.
    vec3_t<TComponent> axis = MTL::Cross(sourceDirection, targetDirection);
    TComponent oldLength = MTL::Length(axis);
    axis = MTL::Normalize(axis);

    if (oldLength != 0.f)
    {
      TComponent halfCosAngle = 0.5f * sourceDirection.Dot(targetDirection);
      TComponent cosHalfAngle = Sqrt(0.5f + halfCosAngle);
      TComponent sinHalfAngle = Sqrt(0.5f - halfCosAngle);
      return Quat(axis.x * sinHalfAngle, axis.y * sinHalfAngle, axis.z * sinHalfAngle, cosHalfAngle);
    }
    else
      return Quat(1.0f, 0.0f, 0.0f, 0.0f);
  }

  /// @brief Creates a new quaternion that rotates sourceDirection vector to coincide with the targetDirection
  /// vector, and then rotates sourceDirection2 (which was transformed by 1.) to targetDirection2, but keeping
  /// the constraint that sourceDirection must look at targetDirection.
  template <IsArithmeticT TComponent>
  NO_DISCARD Quaternion<TComponent> RotateFromTo(const vec3_t<TComponent> &sourceDirection,
                                                 const vec3_t<TComponent> &targetDirection,
                                                 const vec3_t<TComponent> &sourceDirection2,
                                                 const vec3_t<TComponent> &targetDirection2) noexcept
  {
  }

  /// @brief Creates a new quaternion that rotates the localForward vector to coincide with the
  /// targetDirection vector, while keeping the localUp vector pointing in the same direction in world space.
  /// @tparam TComponent the component type of the vectors.
  /// @param localForward the local forward vector.
  /// @param targetDirection the target direction vector.
  /// @param localUp the local up vector.
  /// @param worldUp the world up vector.
  /// @note The localForward, targetDirection, localUp, and worldUp vectors are assumed to be normalized.
  /// @return the quaternion that rotates the localForward vector to coincide with the targetDirection vector.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr Quaternion<TComponent>
    LookAt(const vec3_t<TComponent> &localForward, const vec3_t<TComponent> &targetDirection,
           const vec3_t<TComponent> &localUp, const vec3_t<TComponent> &worldUp) noexcept
  {
  }
}