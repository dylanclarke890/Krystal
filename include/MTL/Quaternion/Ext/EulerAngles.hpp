#pragma once

#include "MTL/Matrices/Ext/EulerAngles.hpp"
#include "MTL/Matrices/Mat3x3.hpp"
#include "MTL/Matrices/Mat3x4.hpp"
#include "MTL/Matrices/Mat4x4.hpp"
#include "MTL/Quaternion/Ext/Transform.hpp"
#include "MTL/Quaternion/Quat.hpp"
#include "MTL/Vectors/Vec3.hpp"

namespace Krys::MTL
{
#pragma region ToEuler

  /// @brief Converts the given quaternion to Euler angles using the XYX convention.
  /// @tparam TComponent the component type of the quaternion.
  /// @param q the quaternion.
  /// @return A vector of Euler angles around the X, Y, and X axes.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr vec3_t<TComponent> ToEulerXYX(const Quaternion<TComponent> &q) noexcept
  {
    return MTL::ToEulerXYX(q.ToMat3x3());
  }

  /// @brief Converts the given quaternion to Euler angles using the XZX convention.
  /// @tparam TComponent the component type of the quaternion.
  /// @param q the quaternion.
  /// @return A vector of Euler angles around the X, Z, and X axes.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr vec3_t<TComponent> ToEulerXZX(const Quaternion<TComponent> &q) noexcept
  {
    return MTL::ToEulerXZX(q.ToMat3x3());
  }

  /// @brief Converts the given quaternion to Euler angles using the YXY convention.
  /// @tparam TComponent the component type of the quaternion.
  /// @param q the quaternion.
  /// @return A vector of Euler angles around the Y, X, and Y axes.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr vec3_t<TComponent> ToEulerYXY(const Quaternion<TComponent> &q) noexcept
  {
    return MTL::ToEulerYXY(q.ToMat3x3());
  }

  /// @brief Converts the given quaternion to Euler angles using the YZY convention.
  /// @tparam TComponent the component type of the quaternion.
  /// @param q the quaternion.
  /// @return A vector of Euler angles around the Y, Z, and Y axes.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr vec3_t<TComponent> ToEulerYZY(const Quaternion<TComponent> &q) noexcept
  {
    return MTL::ToEulerYZY(q.ToMat3x3());
  }

  /// @brief Converts the given quaternion to Euler angles using the ZXZ convention.
  /// @tparam TComponent the component type of the quaternion.
  /// @param q the quaternion.
  /// @return A vector of Euler angles around the Z, X, and Z axes.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr vec3_t<TComponent> ToEulerZXZ(const Quaternion<TComponent> &q) noexcept
  {
    return MTL::ToEulerZXZ(q.ToMat3x3());
  }

  /// @brief Converts the given quaternion to Euler angles using the ZYZ convention.
  /// @tparam TComponent the component type of the quaternion.
  /// @param q the quaternion.
  /// @return A vector of Euler angles around the Z, Y, and Z axes.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr vec3_t<TComponent> ToEulerZYZ(const Quaternion<TComponent> &q) noexcept
  {
    return MTL::ToEulerZYZ(q.ToMat3x3());
  }

  /// @brief Converts the given quaternion to Euler angles using the XYZ convention.
  /// @tparam TComponent the component type of the quaternion.
  /// @param q the quaternion.
  /// @return A vector of Euler angles around the X, Y, and Z axes.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr vec3_t<TComponent> ToEulerXYZ(const Quaternion<TComponent> &q) noexcept
  {
    return MTL::ToEulerXYZ(q.ToMat3x3());
  }

  /// @brief Converts the given quaternion to Euler angles using the XZY convention.
  /// @tparam TComponent the component type of the quaternion.
  /// @param q the quaternion.
  /// @return A vector of Euler angles around the X, Z, and Y axes.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr vec3_t<TComponent> ToEulerXZY(const Quaternion<TComponent> &q) noexcept
  {
    return MTL::ToEulerXZY(q.ToMat3x3());
  }

  /// @brief Converts the given quaternion to Euler angles using the YXZ convention.
  /// @tparam TComponent the component type of the quaternion.
  /// @param q the quaternion.
  /// @return A vector of Euler angles around the Y, X, and Z axes.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr vec3_t<TComponent> ToEulerYXZ(const Quaternion<TComponent> &q) noexcept
  {
    return MTL::ToEulerYXZ(q.ToMat3x3());
  }

  /// @brief Converts the given quaternion to Euler angles using the YZX convention.
  /// @tparam TComponent the component type of the quaternion.
  /// @param q the quaternion.
  /// @return A vector of Euler angles around the Y, Z, and X axes.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr vec3_t<TComponent> ToEulerYZX(const Quaternion<TComponent> &q) noexcept
  {
    return MTL::ToEulerYZX(q.ToMat3x3());
  }

  /// @brief Converts the given quaternion to Euler angles using the ZXY convention.
  /// @tparam TComponent the component type of the quaternion.
  /// @param q the quaternion.
  /// @return A vector of Euler angles around the Z, X, and Y axes.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr vec3_t<TComponent> ToEulerZXY(const Quaternion<TComponent> &q) noexcept
  {
    return MTL::ToEulerZXY(q.ToMat3x3());
  }

  /// @brief Converts the given quaternion to Euler angles using the ZYX convention.
  /// @tparam TComponent the component type of the quaternion.
  /// @param q the quaternion.
  /// @return A vector of Euler angles around the Z, Y, and X axes.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr vec3_t<TComponent> ToEulerZYX(const Quaternion<TComponent> &q) noexcept
  {
    return MTL::ToEulerZYX(q.ToMat3x3());
  }

#pragma endregion ToEuler

#pragma region FromEuler

  /// @brief Creates a quaternion from Euler angles using the XYX convention.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr Quaternion<TComponent> FromEulerXYX(TComponent x2, TComponent y, TComponent x) noexcept
  {
    return (RotateX(x2) * RotateY(y) * RotateX(x)).Normalize();
  }

  /// @brief Creates a quaternion from Euler angles using the XYX convention.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr Quaternion<TComponent> FromEulerXYX(const vec3_t<TComponent> &v) noexcept
  {
    return FromEulerXYX(v.x, v.y, v.z);
  }

  /// @brief Creates a quaternion from Euler angles using the XZX convention.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr Quaternion<TComponent> FromEulerXZX(TComponent x2, TComponent z, TComponent x) noexcept
  {
    return (RotateX(x2) * RotateZ(z) * RotateX(x)).Normalize();
  }

  /// @brief Creates a quaternion from Euler angles using the XZX convention.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr Quaternion<TComponent> FromEulerXZX(const vec3_t<TComponent> &v) noexcept
  {
    return FromEulerXZX(v.x, v.y, v.z);
  }

  /// @brief Creates a quaternion from Euler angles using the YXY convention.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr Quaternion<TComponent> FromEulerYXY(TComponent y2, TComponent x, TComponent y) noexcept
  {
    return (RotateY(y2) * RotateX(x) * RotateY(y)).Normalize();
  }

  /// @brief Creates a quaternion from Euler angles using the YXY convention.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr Quaternion<TComponent> FromEulerYXY(const vec3_t<TComponent> &v) noexcept
  {
    return FromEulerYXY(v.x, v.y, v.z);
  }

  /// @brief Creates a quaternion from Euler angles using the YZY convention.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr Quaternion<TComponent> FromEulerYZY(TComponent y2, TComponent z, TComponent y) noexcept
  {
    return (RotateY(y2) * RotateZ(z) * RotateY(y)).Normalize();
  }

  /// @brief Creates a quaternion from Euler angles using the YZY convention.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr Quaternion<TComponent> FromEulerYZY(const vec3_t<TComponent> &v) noexcept
  {
    return FromEulerYZY(v.x, v.y, v.z);
  }

  /// @brief Creates a quaternion from Euler angles using the ZXZ convention.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr Quaternion<TComponent> FromEulerZXZ(TComponent z2, TComponent x, TComponent z) noexcept
  {
    return (RotateZ(z2) * RotateX(x) * RotateZ(z)).Normalize();
  }

  /// @brief Creates a quaternion from Euler angles using the ZXZ convention.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr Quaternion<TComponent> FromEulerZXZ(const vec3_t<TComponent> &v) noexcept
  {
    return FromEulerZXZ(v.x, v.y, v.z);
  }

  /// @brief Creates a quaternion from Euler angles using the ZYZ convention.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr Quaternion<TComponent> FromEulerZYZ(TComponent z2, TComponent y, TComponent z) noexcept
  {
    return (RotateZ(z2) * RotateY(y) * RotateZ(z)).Normalize();
  }

  /// @brief Creates a quaternion from Euler angles using the ZYZ convention.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr Quaternion<TComponent> FromEulerZYZ(const vec3_t<TComponent> &v) noexcept
  {
    return FromEulerZYZ(v.x, v.y, v.z);
  }

  /// @brief Creates a quaternion from Euler angles using the XYZ convention.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr Quaternion<TComponent> FromEulerXYZ(TComponent x, TComponent y, TComponent z) noexcept
  {
    return (RotateX(x) * RotateY(y) * RotateZ(z)).Normalize();
  }

  /// @brief Creates a quaternion from Euler angles using the XYZ convention.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr Quaternion<TComponent> FromEulerXYZ(const vec3_t<TComponent> &v) noexcept
  {
    return FromEulerXYZ(v.x, v.y, v.z);
  }

  /// @brief Creates a quaternion from Euler angles using the XZY convention.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr Quaternion<TComponent> FromEulerXZY(TComponent x, TComponent z, TComponent y) noexcept
  {
    return (RotateX(x) * RotateZ(z) * RotateY(y)).Normalize();
  }

  /// @brief Creates a quaternion from Euler angles using the XZY convention.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr Quaternion<TComponent> FromEulerXZY(const vec3_t<TComponent> &v) noexcept
  {
    return FromEulerXZY(v.x, v.y, v.z);
  }

  /// @brief Creates a quaternion from Euler angles using the YXZ convention.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr Quaternion<TComponent> FromEulerYXZ(TComponent y, TComponent x, TComponent z) noexcept
  {
    return (RotateY(y) * RotateX(x) * RotateZ(z)).Normalize();
  }

  /// @brief Creates a quaternion from Euler angles using the YXZ convention.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr Quaternion<TComponent> FromEulerYXZ(const vec3_t<TComponent> &v) noexcept
  {
    return FromEulerYXZ(v.x, v.y, v.z);
  }

  /// @brief Creates a quaternion from Euler angles using the YZX convention.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr Quaternion<TComponent> FromEulerYZX(TComponent y, TComponent z, TComponent x) noexcept
  {
    return (RotateY(y) * RotateZ(z) * RotateX(x)).Normalize();
  }

  /// @brief Creates a quaternion from Euler angles using the YZX convention.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr Quaternion<TComponent> FromEulerYZX(const vec3_t<TComponent> &v) noexcept
  {
    return FromEulerYZX(v.x, v.y, v.z);
  }

  /// @brief Creates a quaternion from Euler angles using the ZXY convention.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr Quaternion<TComponent> FromEulerZXY(TComponent z, TComponent x, TComponent y) noexcept
  {
    return (RotateZ(z) * RotateX(x) * RotateY(y)).Normalize();
  }

  /// @brief Creates a quaternion from Euler angles using the ZXY convention.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr Quaternion<TComponent> FromEulerZXY(const vec3_t<TComponent> &v) noexcept
  {
    return FromEulerZXY(v.x, v.y, v.z);
  }

  /// @brief Creates a quaternion from Euler angles using the ZYX convention.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr Quaternion<TComponent> FromEulerZYX(TComponent z, TComponent y, TComponent x) noexcept
  {
    return (RotateZ(z) * RotateY(y) * RotateX(x)).Normalize();
  }

  /// @brief Creates a quaternion from Euler angles using the ZYX convention.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr Quaternion<TComponent> FromEulerZYX(const vec3_t<TComponent> &v) noexcept
  {
    return FromEulerZYX(v.x, v.y, v.z);
  }

#pragma endregion FromEuler
}