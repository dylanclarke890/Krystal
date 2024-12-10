#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Matrices/Base.hpp"
#include "MTL/Matrices/Ext/Algorithms.hpp"
#include "MTL/Matrices/Mat4x4.hpp"
#include "MTL/Trigonometric/Cos.hpp"
#include "MTL/Trigonometric/Sin.hpp"
#include "MTL/Vectors/Ext/Geometric.hpp"
#include "MTL/Vectors/Vec3.hpp"

namespace Krys::MTL
{
  /// @brief Apply a translation vector to a matrix.
  /// @tparam TComponent The underlying floating-point type of the matrix.
  /// @param m The input matrix.
  /// @returns A new matrix with the translation applied.
  template <IsFloatingPointT TComponent>
  NO_DISCARD constexpr auto Translate(const mat4x4_t<TComponent> &m, const vec3_t<TComponent> &v) noexcept
  {
    matrix_t<TComponent, 4, 4> result {m};
    result[3] = m[0] * v[0] + m[1] * v[1] + m[2] * v[2] + m[3];
    return result;
  }

  /// @brief
  /// @tparam TComponent The underlying floating-point type of the matrix.
  /// @param m The input matrix.
  /// @param angle The rotation, in radians.
  /// @returns
  template <IsFloatingPointT TComponent>
  NO_DISCARD constexpr auto Rotate(const mat4x4_t<TComponent> &m, TComponent angle,
                                   const vec3_t<TComponent> &v) noexcept
  {
    const TComponent c = MTL::Cos(angle);
    const TComponent s = MTL::Sin(angle);

    vec3_t<TComponent> axis(MTL::Normalize(v));
    vec3_t<TComponent> temp((TComponent(1) - c) * axis);

    mat4x4_t<TComponent> rot;
    rot[0][0] = c + temp[0] * axis[0];
    rot[0][1] = temp[0] * axis[1] + s * axis[2];
    rot[0][2] = temp[0] * axis[2] - s * axis[1];

    rot[1][0] = temp[1] * axis[0] - s * axis[2];
    rot[1][1] = c + temp[1] * axis[1];
    rot[1][2] = temp[1] * axis[2] + s * axis[0];

    rot[2][0] = temp[2] * axis[0] + s * axis[1];
    rot[2][1] = temp[2] * axis[1] - s * axis[0];
    rot[2][2] = c + temp[2] * axis[2];

    mat4x4_t<TComponent> result;
    result[0] = m[0] * rot[0][0] + m[1] * rot[0][1] + m[2] * rot[0][2];
    result[1] = m[0] * rot[1][0] + m[1] * rot[1][1] + m[2] * rot[1][2];
    result[2] = m[0] * rot[2][0] + m[1] * rot[2][1] + m[2] * rot[2][2];
    result[3] = m[3];

    return result;
  }

  /// @brief Apply a scale vector to a matrix.
  /// @tparam TComponent The underlying floating-point type of the matrix.
  /// @param m The input matrix.
  /// @returns A new matrix with the scale applied.
  template <IsFloatingPointT TComponent>
  NO_DISCARD constexpr auto Scale(const mat4x4_t<TComponent> &m, const vec3_t<TComponent> &v) noexcept
  {
    mat4x4_t<TComponent> result;
    result[0] = m[0] * v[0];
    result[1] = m[1] * v[1];
    result[2] = m[2] * v[2];
    result[3] = m[3];

    return result;
  }

  /// @brief Constructs a right handed look at matrix.
  /// @tparam TComponent The underlying floating-point type of the matrix.
  /// @returns The look at matrix.
  template <IsFloatingPointT TComponent>
  NO_DISCARD constexpr auto LookAt_RH(const vec3_t<TComponent> &eye, const vec3_t<TComponent> &center,
                                      const vec3_t<TComponent> &up) noexcept -> mat4x4_t<TComponent>
  {
    const vec3_t<TComponent> f(MTL::Normalize(center - eye));
    const vec3_t<TComponent> s(MTL::Normalize(MTL::Cross(f, up)));
    const vec3_t<TComponent> u(MTL::Cross(s, f));

    mat4x4_t<TComponent> result(1);
    result[0][0] = s.x;
    result[1][0] = s.y;
    result[2][0] = s.z;
    result[0][1] = u.x;
    result[1][1] = u.y;
    result[2][1] = u.z;
    result[0][2] = -f.x;
    result[1][2] = -f.y;
    result[2][2] = -f.z;
    result[3][0] = -MTL::Dot(s, eye);
    result[3][1] = -MTL::Dot(u, eye);
    result[3][2] = MTL::Dot(f, eye);
    return result;
  }

  /// @brief Constructs a left handed look at matrix.
  /// @tparam TComponent The underlying floating-point type of the matrix.
  /// @returns The look at matrix.
  template <IsFloatingPointT TComponent>
  NO_DISCARD constexpr auto LookAt_LH(const vec3_t<TComponent> &eye, const vec3_t<TComponent> &center,
                                      const vec3_t<TComponent> &up) noexcept -> mat4x4_t<TComponent>
  {
    const vec3_t<TComponent> f(MTL::Normalize(center - eye));
    const vec3_t<TComponent> s(MTL::Normalize(MTL::Cross(up, f)));
    const vec3_t<TComponent> u(MTL::Cross(f, s));

    mat4x4_t<TComponent> result(1);
    result[0][0] = s.x;
    result[1][0] = s.y;
    result[2][0] = s.z;
    result[0][1] = u.x;
    result[1][1] = u.y;
    result[2][1] = u.z;
    result[0][2] = f.x;
    result[1][2] = f.y;
    result[2][2] = f.z;
    result[3][0] = -MTL::Dot(s, eye);
    result[3][1] = -MTL::Dot(u, eye);
    result[3][2] = -MTL::Dot(f, eye);
    return result;
  }

  /// @brief
  /// @tparam TComponent The underlying floating-point type of the matrix.
  /// @returns
  template <IsFloatingPointT TComponent>
  NO_DISCARD constexpr auto LookAt(const vec3_t<TComponent> &eye, const vec3_t<TComponent> &center,
                                   const vec3_t<TComponent> &up) noexcept -> mat4x4_t<TComponent>
  {
#if KRYS_MATRIX_HANDEDNESS == KRYS_MATRIX_HANDEDNESS_LH
    return LookAt_LH(eye, center, up);
#else
    return LookAt_RH(eye, center, up);
#endif
  }
}