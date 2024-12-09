#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Matrices/Base.hpp"
#include "MTL/Matrices/Mat4x4.hpp"

namespace Krys::MTL
{
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

  template <typename TComponent>
  NO_DISCARD constexpr mat4x4_t<TComponent> Perspective_RH_ZO(TComponent fovy, TComponent aspect,
                                                              TComponent zNear, TComponent zFar)
  {
    KRYS_ASSERT(MTL::Abs(aspect - std::numeric_limits<TComponent>::epsilon()) > TComponent(0),
                "Aspect is invalid", 0);

    const TComponent tanHalfFovy = tan(fovy / TComponent(2));

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
                "Aspect is invalid", 0);

    const TComponent tanHalfFovy = tan(fovy / TComponent(2));

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
                "Aspect is invalid", 0);

    const TComponent tanHalfFovy = tan(fovy / TComponent(2));

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
                "Aspect is invalid", 0);

    const TComponent tanHalfFovy = tan(fovy / TComponent(2));

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
}