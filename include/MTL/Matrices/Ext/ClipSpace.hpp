#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Common/Abs.hpp"
#include "MTL/Matrices/Base.hpp"
#include "MTL/Matrices/Mat4x4.hpp"
#include "MTL/Trigonometric/Cos.hpp"
#include "MTL/Trigonometric/Sin.hpp"
#include "MTL/Trigonometric/Tan.hpp"

#include <limits>

namespace Krys::MTL
{
#pragma region Ortho

  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr mat4x4_t<TComponent> Ortho_LH_ZO(TComponent left, TComponent right, TComponent bottom,
                                                        TComponent top, TComponent zNear, TComponent zFar)
  {
    mat4x4_t<TComponent> result(1);

    result[0][0] = TComponent(2) / (right - left);
    result[1][1] = TComponent(2) / (top - bottom);
    result[2][2] = TComponent(1) / (zFar - zNear);
    result[3][0] = -(right + left) / (right - left);
    result[3][1] = -(top + bottom) / (top - bottom);
    result[3][2] = -zNear / (zFar - zNear);

    return result;
  }

  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr mat4x4_t<TComponent> Ortho_LH_NO(TComponent left, TComponent right, TComponent bottom,
                                                        TComponent top, TComponent zNear, TComponent zFar)
  {
    mat4x4_t<TComponent> result(1);

    result[0][0] = TComponent(2) / (right - left);
    result[1][1] = TComponent(2) / (top - bottom);
    result[2][2] = TComponent(2) / (zFar - zNear);
    result[3][0] = -(right + left) / (right - left);
    result[3][1] = -(top + bottom) / (top - bottom);
    result[3][2] = -(zFar + zNear) / (zFar - zNear);

    return result;
  }

  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr mat4x4_t<TComponent> Ortho_LH(TComponent left, TComponent right, TComponent bottom,
                                                     TComponent top, TComponent zNear, TComponent zFar)
  {
#if KRYS_MATRIX_DEPTH_RANGE == KRYS_MATRIX_DEPTH_RANGE_ZERO_TO_ONE
    return Ortho_LH_ZO(left, right, bottom, top, zNear, zFar);
#else
    return Ortho_LH_NO(left, right, bottom, top, zNear, zFar);
#endif
  }

  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr mat4x4_t<TComponent> Ortho_RH_ZO(TComponent left, TComponent right, TComponent bottom,
                                                        TComponent top, TComponent zNear, TComponent zFar)
  {
    mat4x4_t<TComponent> result(1);

    result[0][0] = TComponent(2) / (right - left);
    result[1][1] = TComponent(2) / (top - bottom);
    result[2][2] = -TComponent(1) / (zFar - zNear);
    result[3][0] = -(right + left) / (right - left);
    result[3][1] = -(top + bottom) / (top - bottom);
    result[3][2] = -zNear / (zFar - zNear);

    return result;
  }

  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr mat4x4_t<TComponent> Ortho_RH_NO(TComponent left, TComponent right, TComponent bottom,
                                                        TComponent top, TComponent zNear, TComponent zFar)
  {
    mat4x4_t<TComponent> result(1);

    result[0][0] = TComponent(2) / (right - left);
    result[1][1] = TComponent(2) / (top - bottom);
    result[2][2] = -TComponent(2) / (zFar - zNear);
    result[3][0] = -(right + left) / (right - left);
    result[3][1] = -(top + bottom) / (top - bottom);
    result[3][2] = -(zFar + zNear) / (zFar - zNear);

    return result;
  }

  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr mat4x4_t<TComponent> Ortho_RH(TComponent left, TComponent right, TComponent bottom,
                                                     TComponent top, TComponent zNear, TComponent zFar)
  {
#if KRYS_MATRIX_DEPTH_RANGE == KRYS_MATRIX_DEPTH_RANGE_ZERO_TO_ONE
    return Ortho_RH_ZO(left, right, bottom, top, zNear, zFar);
#else
    return Ortho_RH_NO(left, right, bottom, top, zNear, zFar);
#endif
  }

  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr mat4x4_t<TComponent> Ortho_NO(TComponent left, TComponent right, TComponent bottom,
                                                     TComponent top, TComponent zNear, TComponent zFar)
  {
#if KRYS_MATRIX_HANDEDNESS == KRYS_MATRIX_HANDEDNESS_LH
    return Ortho_LH_NO(left, right, bottom, top, zNear, zFar);
#else
    return Ortho_RH_NO(left, right, bottom, top, zNear, zFar);
#endif
  }

  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr mat4x4_t<TComponent> Ortho_ZO(TComponent left, TComponent right, TComponent bottom,
                                                     TComponent top, TComponent zNear, TComponent zFar)
  {
#if KRYS_MATRIX_HANDEDNESS == KRYS_MATRIX_HANDEDNESS_LH
    return Ortho_LH_ZO(left, right, bottom, top, zNear, zFar);
#else
    return Ortho_RH_XO(left, right, bottom, top, zNear, zFar);
#endif
  }

  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr mat4x4_t<TComponent> Ortho(TComponent left, TComponent right, TComponent bottom,
                                                  TComponent top)
  {
    mat4x4_t<TComponent> result(TComponent(1));

    result[0][0] = TComponent(2) / (right - left);
    result[1][1] = TComponent(2) / (top - bottom);
    result[2][2] = -TComponent(1);
    result[3][0] = -(right + left) / (right - left);
    result[3][1] = -(top + bottom) / (top - bottom);

    return result;
  }

  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr mat4x4_t<TComponent> Ortho(TComponent left, TComponent right, TComponent bottom,
                                                  TComponent top, TComponent zNear, TComponent zFar)
  {
#if KRYS_MATRIX_HANDEDNESS == KRYS_MATRIX_HANDEDNESS_LH
    return Ortho_LH(left, right, top, bottom, zNear, zFar);
#else
    return Ortho_RH(left, right, top, bottom, zNear, zFar);
#endif
  }

  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr mat4x4_t<TComponent> Ortho(TComponent width, TComponent height, TComponent depth)
  {
    const auto right = width;
    const auto left = -right;
    const auto top = height;
    const auto bottom = -top;
    const auto farPlane = depth;
    const auto nearPlane = -farPlane;

    return Ortho(left, right, bottom, top, nearPlane, farPlane);
  }

#pragma endregion Ortho

#pragma region Frustum

  template <typename TComponent>
  NO_DISCARD constexpr mat4x4_t<TComponent> Frustum_LH_ZO(TComponent left, TComponent right,
                                                          TComponent bottom, TComponent top,
                                                          TComponent nearVal, TComponent farVal)
  {
    mat4x4_t<TComponent> result(0);
    result[0][0] = (TComponent(2) * nearVal) / (right - left);
    result[1][1] = (TComponent(2) * nearVal) / (top - bottom);
    result[2][0] = -(right + left) / (right - left);
    result[2][1] = -(top + bottom) / (top - bottom);
    result[2][2] = farVal / (farVal - nearVal);
    result[2][3] = TComponent(1);
    result[3][2] = -(farVal * nearVal) / (farVal - nearVal);
    return result;
  }

  template <typename TComponent>
  NO_DISCARD constexpr mat4x4_t<TComponent> Frustum_LH_NO(TComponent left, TComponent right,
                                                          TComponent bottom, TComponent top,
                                                          TComponent nearVal, TComponent farVal)
  {
    mat4x4_t<TComponent> result(0);
    result[0][0] = (TComponent(2) * nearVal) / (right - left);
    result[1][1] = (TComponent(2) * nearVal) / (top - bottom);
    result[2][0] = -(right + left) / (right - left);
    result[2][1] = -(top + bottom) / (top - bottom);
    result[2][2] = (farVal + nearVal) / (farVal - nearVal);
    result[2][3] = TComponent(1);
    result[3][2] = -(TComponent(2) * farVal * nearVal) / (farVal - nearVal);
    return result;
  }

  template <typename TComponent>
  NO_DISCARD constexpr mat4x4_t<TComponent> Frustum_RH_ZO(TComponent left, TComponent right,
                                                          TComponent bottom, TComponent top,
                                                          TComponent nearVal, TComponent farVal)
  {
    mat4x4_t<TComponent> result(0);
    result[0][0] = (TComponent(2) * nearVal) / (right - left);
    result[1][1] = (TComponent(2) * nearVal) / (top - bottom);
    result[2][0] = (right + left) / (right - left);
    result[2][1] = (top + bottom) / (top - bottom);
    result[2][2] = farVal / (nearVal - farVal);
    result[2][3] = TComponent(-1);
    result[3][2] = -(farVal * nearVal) / (farVal - nearVal);
    return result;
  }

  template <typename TComponent>
  NO_DISCARD constexpr mat4x4_t<TComponent> Frustum_RH_NO(TComponent left, TComponent right,
                                                          TComponent bottom, TComponent top,
                                                          TComponent nearVal, TComponent farVal)
  {
    mat4x4_t<TComponent> result(0);
    result[0][0] = (TComponent(2) * nearVal) / (right - left);
    result[1][1] = (TComponent(2) * nearVal) / (top - bottom);
    result[2][0] = (right + left) / (right - left);
    result[2][1] = (top + bottom) / (top - bottom);
    result[2][2] = -(farVal + nearVal) / (farVal - nearVal);
    result[2][3] = TComponent(-1);
    result[3][2] = -(TComponent(2) * farVal * nearVal) / (farVal - nearVal);
    return result;
  }

  template <typename TComponent>
  NO_DISCARD constexpr mat4x4_t<TComponent> Frustum_ZO(TComponent left, TComponent right, TComponent bottom,
                                                       TComponent top, TComponent nearVal, TComponent farVal)
  {
#if KRYS_MATRIX_HANDEDNESS == KRYS_MATRIX_HANDEDNESS_LH
    return Frustum_LH_ZO(left, right, bottom, top, nearVal, farVal);
#else
    return Frustum_RH_ZO(left, right, bottom, top, nearVal, farVal);
#endif
  }

  template <typename TComponent>
  NO_DISCARD constexpr mat4x4_t<TComponent> Frustum_NO(TComponent left, TComponent right, TComponent bottom,
                                                       TComponent top, TComponent nearVal, TComponent farVal)
  {
#if KRYS_MATRIX_HANDEDNESS == KRYS_MATRIX_HANDEDNESS_LH
    return Frustum_LH_NO(left, right, bottom, top, nearVal, farVal);
#else
    return Frustum_RH_NO(left, right, bottom, top, nearVal, farVal);
#endif
  }

  template <typename TComponent>
  NO_DISCARD constexpr mat4x4_t<TComponent> Frustum_LH(TComponent left, TComponent right, TComponent bottom,
                                                       TComponent top, TComponent nearVal, TComponent farVal)
  {
#if KRYS_MATRIX_DEPTH_RANGE == KRYS_MATRIX_DEPTH_RANGE_ZERO_TO_ONE
    return Frustum_LH_ZO(left, right, bottom, top, nearVal, farVal);
#else
    return Frustum_LH_NO(left, right, bottom, top, nearVal, farVal);
#endif
  }

  template <typename TComponent>
  NO_DISCARD constexpr mat4x4_t<TComponent> Frustum_RH(TComponent left, TComponent right, TComponent bottom,
                                                       TComponent top, TComponent nearVal, TComponent farVal)
  {
#if KRYS_MATRIX_DEPTH_RANGE == KRYS_MATRIX_DEPTH_RANGE_ZERO_TO_ONE
    return Frustum_RH_ZO(left, right, bottom, top, nearVal, farVal);
#else
    return Frustum_RH_NO(left, right, bottom, top, nearVal, farVal);
#endif
  }

  template <typename TComponent>
  NO_DISCARD constexpr mat4x4_t<TComponent> Frustum(TComponent left, TComponent right, TComponent bottom,
                                                    TComponent top, TComponent nearVal, TComponent farVal)
  {
#if KRYS_MATRIX_HANDEDNESS == KRYS_MATRIX_HANDEDNESS_LH
    return Frustum_LH(left, right, bottom, top, nearVal, farVal);
#else
    return Frustum_RH(left, right, bottom, top, nearVal, farVal);
#endif
  }

#pragma endregion Frustum

#pragma region Perspective

  template <typename TComponent>
  NO_DISCARD constexpr mat4x4_t<TComponent> Perspective_RH_ZO(TComponent fovy, TComponent aspect,
                                                              TComponent zNear, TComponent zFar)
  {
    KRYS_ASSERT(MTL::Abs(aspect - std::numeric_limits<TComponent>::epsilon()) > TComponent(0),
                "Aspect is invalid");

    const TComponent tanHalfFovy = Tan(fovy / TComponent(2));

    mat4x4_t<TComponent> result(TComponent(0));
    result[0][0] = TComponent(1) / (aspect * tanHalfFovy);
    result[1][1] = TComponent(1) / (tanHalfFovy);
    result[2][2] = zFar / (zNear - zFar);
    result[2][3] = -TComponent(1);
    result[3][2] = -(zFar * zNear) / (zFar - zNear);
    return result;
  }

  template <typename TComponent>
  NO_DISCARD constexpr mat4x4_t<TComponent> Perspective_RH_NO(TComponent fovy, TComponent aspect,
                                                              TComponent zNear, TComponent zFar)
  {
    KRYS_ASSERT(MTL::Abs(aspect - std::numeric_limits<TComponent>::epsilon()) > TComponent(0),
                "Aspect is invalid");

    const TComponent tanHalfFovy = Tan(fovy / TComponent(2));

    mat4x4_t<TComponent> result(TComponent(0));
    result[0][0] = TComponent(1) / (aspect * tanHalfFovy);
    result[1][1] = TComponent(1) / (tanHalfFovy);
    result[2][2] = -(zFar + zNear) / (zFar - zNear);
    result[2][3] = -TComponent(1);
    result[3][2] = -(TComponent(2) * zFar * zNear) / (zFar - zNear);
    return result;
  }

  template <typename TComponent>
  NO_DISCARD constexpr mat4x4_t<TComponent> Perspective_LH_ZO(TComponent fovy, TComponent aspect,
                                                              TComponent zNear, TComponent zFar)
  {
    KRYS_ASSERT(MTL::Abs(aspect - std::numeric_limits<TComponent>::epsilon()) > TComponent(0),
                "Aspect is invalid");

    const TComponent tanHalfFovy = Tan(fovy / TComponent(2));

    mat4x4_t<TComponent> result(TComponent(0));
    result[0][0] = TComponent(1) / (aspect * tanHalfFovy);
    result[1][1] = TComponent(1) / (tanHalfFovy);
    result[2][2] = zFar / (zFar - zNear);
    result[2][3] = TComponent(1);
    result[3][2] = -(zFar * zNear) / (zFar - zNear);
    return result;
  }

  template <typename TComponent>
  NO_DISCARD constexpr mat4x4_t<TComponent> Perspective_LH_NO(TComponent fovy, TComponent aspect,
                                                              TComponent zNear, TComponent zFar)
  {
    KRYS_ASSERT(MTL::Abs(aspect - std::numeric_limits<TComponent>::epsilon()) > TComponent(0),
                "Aspect is invalid");

    const TComponent tanHalfFovy = Tan(fovy / TComponent(2));

    mat4x4_t<TComponent> result(TComponent(0));
    result[0][0] = TComponent(1) / (aspect * tanHalfFovy);
    result[1][1] = TComponent(1) / (tanHalfFovy);
    result[2][2] = (zFar + zNear) / (zFar - zNear);
    result[2][3] = TComponent(1);
    result[3][2] = -(TComponent(2) * zFar * zNear) / (zFar - zNear);
    return result;
  }

  template <typename TComponent>
  NO_DISCARD constexpr mat4x4_t<TComponent> Perspective_ZO(TComponent fovy, TComponent aspect,
                                                           TComponent zNear, TComponent zFar)
  {
#if KRYS_MATRIX_HANDEDNESS == KRYS_MATRIX_HANDEDNESS_LH
    return Perspective_LH_ZO(fovy, aspect, zNear, zFar);
#else
    return Perspective_RH_ZO(fovy, aspect, zNear, zFar);
#endif
  }

  template <typename TComponent>
  NO_DISCARD constexpr mat4x4_t<TComponent> Perspective_NO(TComponent fovy, TComponent aspect,
                                                           TComponent zNear, TComponent zFar)
  {
#if KRYS_MATRIX_HANDEDNESS == KRYS_MATRIX_HANDEDNESS_LH
    return Perspective_LH_NO(fovy, aspect, zNear, zFar);
#else
    return Perspective_RH_NO(fovy, aspect, zNear, zFar);
#endif
  }

  template <typename TComponent>
  NO_DISCARD constexpr mat4x4_t<TComponent> Perspective_LH(TComponent fovy, TComponent aspect,
                                                           TComponent zNear, TComponent zFar)
  {
#if KRYS_MATRIX_DEPTH_RANGE == KRYS_MATRIX_DEPTH_RANGE_ZERO_TO_ONE
    return Perspective_LH_ZO(fovy, aspect, zNear, zFar);
#else
    return Perspective_LH_NO(fovy, aspect, zNear, zFar);
#endif
  }

  template <typename TComponent>
  NO_DISCARD constexpr mat4x4_t<TComponent> Perspective_RH(TComponent fovy, TComponent aspect,
                                                           TComponent zNear, TComponent zFar)
  {
#if KRYS_MATRIX_DEPTH_RANGE == KRYS_MATRIX_DEPTH_RANGE_ZERO_TO_ONE
    return Perspective_RH_ZO(fovy, aspect, zNear, zFar);
#else
    return Perspective_RH_NO(fovy, aspect, zNear, zFar);
#endif
  }

  template <typename TComponent>
  NO_DISCARD constexpr mat4x4_t<TComponent> Perspective(TComponent fovy, TComponent aspect, TComponent zNear,
                                                        TComponent zFar)
  {
#if KRYS_MATRIX_HANDEDNESS == KRYS_MATRIX_HANDEDNESS_LH
    return Perspective_LH(fovy, aspect, zNear, zFar);
#else
    return Perspective_RH(fovy, aspect, zNear, zFar);
#endif
  }

  template <typename TComponent>
  NO_DISCARD constexpr mat4x4_t<TComponent> Perspective(TComponent fovy, TComponent width, TComponent height,
                                                        TComponent zNear, TComponent zFar)
  {
    return Perspective(fovy, width / height, zNear, zFar);
  }

#pragma endregion Perspective

#pragma region PerspectiveFov

  template <typename TComponent>
  NO_DISCARD constexpr mat4x4_t<TComponent> PerspectiveFov_RH_ZO(TComponent fov, TComponent width,
                                                                 TComponent height, TComponent zNear,
                                                                 TComponent zFar)
  {
    KRYS_ASSERT(width > TComponent(0), "Invalid width {0}", width);
    KRYS_ASSERT(height > TComponent(0), "Invalid height {0}", height);
    KRYS_ASSERT(fov > TComponent(0), "Invalid fov {0}", fov);

    const TComponent rad = fov;
    const TComponent h = Cos(TComponent(0.5) * rad) / Sin(TComponent(0.5) * rad);
    const TComponent w = h * height / width; /// todo max(width , Height) / min(width , Height)?

    mat4x4_t<TComponent> result(TComponent(0));

    result[0][0] = w;
    result[1][1] = h;
    result[2][2] = zFar / (zNear - zFar);
    result[2][3] = -TComponent(1);
    result[3][2] = -(zFar * zNear) / (zFar - zNear);

    return result;
  }

  template <typename TComponent>
  NO_DISCARD constexpr mat4x4_t<TComponent> PerspectiveFov_RH_NO(TComponent fov, TComponent width,
                                                                 TComponent height, TComponent zNear,
                                                                 TComponent zFar)
  {
    KRYS_ASSERT(width > TComponent(0), "Invalid width {0}", width);
    KRYS_ASSERT(height > TComponent(0), "Invalid height {0}", height);
    KRYS_ASSERT(fov > TComponent(0), "Invalid fov {0}", fov);

    const TComponent rad = fov;
    const TComponent h = Cos(TComponent(0.5) * rad) / Sin(TComponent(0.5) * rad);
    const TComponent w = h * height / width; /// todo max(width , Height) / min(width , Height)?

    mat4x4_t<TComponent> result(TComponent(0));

    result[0][0] = w;
    result[1][1] = h;
    result[2][2] = -(zFar + zNear) / (zFar - zNear);
    result[2][3] = -TComponent(1);
    result[3][2] = -(TComponent(2) * zFar * zNear) / (zFar - zNear);

    return result;
  }

  template <typename TComponent>
  NO_DISCARD constexpr mat4x4_t<TComponent> PerspectiveFov_LH_ZO(TComponent fov, TComponent width,
                                                                 TComponent height, TComponent zNear,
                                                                 TComponent zFar)
  {
    KRYS_ASSERT(width > TComponent(0), "Invalid width {0}", width);
    KRYS_ASSERT(height > TComponent(0), "Invalid height {0}", height);
    KRYS_ASSERT(fov > TComponent(0), "Invalid fov {0}", fov);

    const TComponent rad = fov;
    const TComponent h = Cos(TComponent(0.5) * rad) / Sin(TComponent(0.5) * rad);
    const TComponent w = h * height / width; /// todo max(width , Height) / min(width , Height)?

    mat4x4_t<TComponent> result(TComponent(0));

    result[0][0] = w;
    result[1][1] = h;
    result[2][2] = zFar / (zFar - zNear);
    result[2][3] = TComponent(1);
    result[3][2] = -(zFar * zNear) / (zFar - zNear);

    return result;
  }

  template <typename TComponent>
  NO_DISCARD constexpr mat4x4_t<TComponent> PerspectiveFov_LH_NO(TComponent fov, TComponent width,
                                                                 TComponent height, TComponent zNear,
                                                                 TComponent zFar)
  {
    KRYS_ASSERT(width > TComponent(0), "Invalid width {0}", width);
    KRYS_ASSERT(height > TComponent(0), "Invalid height {0}", height);
    KRYS_ASSERT(fov > TComponent(0), "Invalid fov {0}", fov);

    const TComponent rad = fov;
    const TComponent h = Cos(TComponent(0.5) * rad) / Sin(TComponent(0.5) * rad);
    const TComponent w = h * height / width; /// todo max(width , Height) / min(width , Height)?

    mat4x4_t<TComponent> result(TComponent(0));

    result[0][0] = w;
    result[1][1] = h;
    result[2][2] = (zFar + zNear) / (zFar - zNear);
    result[2][3] = TComponent(1);
    result[3][2] = -(TComponent(2) * zFar * zNear) / (zFar - zNear);

    return result;
  }

  template <typename TComponent>
  NO_DISCARD constexpr mat4x4_t<TComponent>
    PerspectiveFov_ZO(TComponent fov, TComponent width, TComponent height, TComponent zNear, TComponent zFar)
  {
#if KRYS_MATRIX_HANDEDNESS == KRYS_MATRIX_HANDEDNESS_LH
    return PerspectiveFov_LH_ZO(fov, width, height, zNear, zFar);
#else
    return PerspectiveFov_RH_ZO(fov, width, height, zNear, zFar);
#endif
  }

  template <typename TComponent>
  NO_DISCARD constexpr mat4x4_t<TComponent>
    PerspectiveFov_NO(TComponent fov, TComponent width, TComponent height, TComponent zNear, TComponent zFar)
  {
#if KRYS_MATRIX_HANDEDNESS == KRYS_MATRIX_HANDEDNESS_LH
    return PerspectiveFov_LH_NO(fov, width, height, zNear, zFar);
#else
    return PerspectiveFov_RH_NO(fov, width, height, zNear, zFar);
#endif
  }

  template <typename TComponent>
  NO_DISCARD constexpr mat4x4_t<TComponent>
    PerspectiveFov_LH(TComponent fov, TComponent width, TComponent height, TComponent zNear, TComponent zFar)
  {
#if KRYS_MATRIX_DEPTH_RANGE == KRYS_MATRIX_DEPTH_RANGE_ZERO_TO_ONE
    return PerspectiveFov_LH_ZO(fov, width, height, zNear, zFar);
#else
    return PerspectiveFov_LH_NO(fov, width, height, zNear, zFar);
#endif
  }

  template <typename TComponent>
  NO_DISCARD constexpr mat4x4_t<TComponent>
    PerspectiveFov_RH(TComponent fov, TComponent width, TComponent height, TComponent zNear, TComponent zFar)
  {
#if KRYS_MATRIX_DEPTH_RANGE == KRYS_MATRIX_DEPTH_RANGE_ZERO_TO_ONE
    return PerspectiveFov_RH_ZO(fov, width, height, zNear, zFar);
#else
    return PerspectiveFov_RH_NO(fov, width, height, zNear, zFar);
#endif
  }

  template <typename TComponent>
  NO_DISCARD constexpr mat4x4_t<TComponent>
    PerspectiveFov(TComponent fov, TComponent width, TComponent height, TComponent zNear, TComponent zFar)
  {
#if KRYS_MATRIX_HANDEDNESS == KRYS_MATRIX_HANDEDNESS_LH
    return PerspectiveFov_LH(fov, width, height, zNear, zFar);
#else
    return PerspectiveFov_RH(fov, width, height, zNear, zFar);
#endif
  }

#pragma endregion PerspectiveFov

#pragma region InfinitePerspective

  template <typename TComponent>
  NO_DISCARD constexpr mat4x4_t<TComponent> InfinitePerspective_RH_NO(TComponent fovy, TComponent aspect,
                                                                      TComponent zNear)
  {
    const TComponent range = Tan(fovy / TComponent(2)) * zNear;
    const TComponent left = -range * aspect;
    const TComponent right = range * aspect;
    const TComponent bottom = -range;
    const TComponent top = range;

    mat4x4_t<TComponent> result(TComponent(0));

    result[0][0] = (TComponent(2) * zNear) / (right - left);
    result[1][1] = (TComponent(2) * zNear) / (top - bottom);
    result[2][2] = -TComponent(1);
    result[2][3] = -TComponent(1);
    result[3][2] = -TComponent(2) * zNear;

    return result;
  }

  template <typename TComponent>
  NO_DISCARD constexpr mat4x4_t<TComponent> InfinitePerspective_RH_ZO(TComponent fovy, TComponent aspect,
                                                                      TComponent zNear)
  {
    const TComponent range = Tan(fovy / TComponent(2)) * zNear;
    const TComponent left = -range * aspect;
    const TComponent right = range * aspect;
    const TComponent bottom = -range;
    const TComponent top = range;

    mat4x4_t<TComponent> result(TComponent(0));

    result[0][0] = (TComponent(2) * zNear) / (right - left);
    result[1][1] = (TComponent(2) * zNear) / (top - bottom);
    result[2][2] = -TComponent(1);
    result[2][3] = -TComponent(1);
    result[3][2] = -zNear;

    return result;
  }

  template <typename TComponent>
  NO_DISCARD constexpr mat4x4_t<TComponent> InfinitePerspective_LH_NO(TComponent fovy, TComponent aspect,
                                                                      TComponent zNear)
  {
    const TComponent range = Tan(fovy / TComponent(2)) * zNear;
    const TComponent left = -range * aspect;
    const TComponent right = range * aspect;
    const TComponent bottom = -range;
    const TComponent top = range;

    mat4x4_t<TComponent> result(TComponent(0));

    result[0][0] = (TComponent(2) * zNear) / (right - left);
    result[1][1] = (TComponent(2) * zNear) / (top - bottom);
    result[2][2] = TComponent(1);
    result[2][3] = TComponent(1);
    result[3][2] = -TComponent(2) * zNear;

    return result;
  }

  template <typename TComponent>
  NO_DISCARD constexpr mat4x4_t<TComponent> InfinitePerspective_LH_ZO(TComponent fovy, TComponent aspect,
                                                                      TComponent zNear)
  {
    const TComponent range = Tan(fovy / TComponent(2)) * zNear;
    const TComponent left = -range * aspect;
    const TComponent right = range * aspect;
    const TComponent bottom = -range;
    const TComponent top = range;

    mat4x4_t<TComponent> result(TComponent(0));

    result[0][0] = (TComponent(2) * zNear) / (right - left);
    result[1][1] = (TComponent(2) * zNear) / (top - bottom);
    result[2][2] = TComponent(1);
    result[2][3] = TComponent(1);
    result[3][2] = -zNear;

    return result;
  }

#pragma endregion InfinitePerspective
}