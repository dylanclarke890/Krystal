#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Common/Constants.hpp"
#include "MTL/Matrices/Mat3x3.hpp"
#include "MTL/Matrices/Mat3x4.hpp"
#include "MTL/Matrices/Mat4x4.hpp"
#include "MTL/Trigonometric/Acos.hpp"
#include "MTL/Trigonometric/Asin.hpp"
#include "MTL/Trigonometric/Atan2.hpp"
#include "MTL/Vectors/Vec3.hpp"

namespace Krys::Impl
{
  template <typename Matrix, IsArithmeticT TComponent>
  NO_DISCARD constexpr vec3_t<TComponent> ExtractEulerXYX(const Matrix &m) noexcept
  {
    if (m[0][0] < MTL::One<TComponent>())
    {
      if (m[0][0] > -MTL::One<TComponent>())
        return {MTL::Acos(m[0][0]), MTL::Atan2(m[1][0], -m[2][0]), MTL::Atan2(m[0][1], m[0][2])};
      else
        // Not a unique solution.
        return {MTL::Pi<TComponent>(), -MTL::Atan2(-m[1][2], m[1][1]), MTL::Zero<TComponent>()};
    }

    return {MTL::Zero<TComponent>(), MTL::Atan2(-m[1][2], m[1][1]), MTL::Zero<TComponent>()};
  }

  template <typename Matrix, IsArithmeticT TComponent>
  NO_DISCARD constexpr vec3_t<TComponent> ExtractEulerXZX(const Matrix &m) noexcept
  {
    if (m[0][0] < MTL::One<TComponent>())
    {
      if (m[0][0] > -MTL::One<TComponent>())
        return {MTL::Acos(m[0][0]), MTL::Atan2(m[2][0], m[1][0]), MTL::Atan2(m[0][2], -m[0][1])};
      else
        return {MTL::Pi<TComponent>(), -MTL::Atan2(m[2][1], m[2][2]), MTL::Zero<TComponent>()};
    }

    return {MTL::Zero<TComponent>(), MTL::Atan2(m[2][1], m[2][2]), MTL::Zero<TComponent>()};
  }

  template <typename Matrix, IsArithmeticT TComponent>
  NO_DISCARD constexpr vec3_t<TComponent> ExtractEulerXYZ(const Matrix &m) noexcept
  {
    if (m[0][2] < MTL::One<TComponent>())
    {
      if (m[0][2] > -MTL::One<TComponent>())
        return {MTL::Asin(m[0][2]), MTL::Atan2(-m[1][2], m[2][2]), MTL::Atan2(-m[0][1], m[0][0])};
      else
        // Not a unique solution: z - x = atan2(m[1][0], m[1][1]);
        return {-MTL::HalfPi<TComponent>(), -MTL::Atan2(m[1][0], m[1][1]), MTL::Zero<TComponent>()};
    }

    return {MTL::HalfPi<TComponent>(), MTL::Atan2(m[1][0], m[1][1]), MTL::Zero<TComponent>()};
  }

  template <typename Matrix, IsArithmeticT TComponent>
  NO_DISCARD constexpr vec3_t<TComponent> ExtractEulerYXY(const Matrix &m) noexcept
  {
    if (m[1][1] < MTL::One<TComponent>())
    {
      if (m[1][1] > -MTL::One<TComponent>())
        return {MTL::Acos(m[1][1]), MTL::Atan2(m[0][1], m[2][1]), MTL::Atan2(m[1][0], -m[1][2])};
      else
        // Not a unique solution.
        return {MTL::Pi<TComponent>(), -MTL::Atan2(m[0][2], m[0][0]), MTL::Zero<TComponent>()};
    }

    // Not a unique solution.
    return {MTL::Zero<TComponent>(), MTL::Atan2(m[0][2], m[0][0]), MTL::Zero<TComponent>()};
  }

  template <typename Matrix, IsArithmeticT TComponent>
  NO_DISCARD constexpr vec3_t<TComponent> ExtractEulerYZY(const Matrix &m) noexcept
  {
    if (m[1][1] < MTL::One<TComponent>())
    {
      if (m[1][1] > -MTL::One<TComponent>())
        return {MTL::Acos(m[1][1]), MTL::Atan2(m[2][1], -m[0][1]), MTL::Atan2(m[1][2], m[1][0])};
      else
        return {MTL::Pi<TComponent>(), -MTL::Atan2(-m[2][0], m[2][2]), MTL::Zero<TComponent>()};
    }

    // Not a unique solution.
    return {MTL::Zero<TComponent>(), MTL::Atan2(-m[2][0], m[2][2]), MTL::Zero<TComponent>()};
  }

  template <typename Matrix, IsArithmeticT TComponent>
  NO_DISCARD constexpr vec3_t<TComponent> ExtractEulerZXZ(const Matrix &m) noexcept
  {
    if (m[2][2] < MTL::One<TComponent>())
    {
      if (m[2][2] > -MTL::One<TComponent>())
        return {MTL::Acos(m[2][2]), MTL::Atan2(m[0][2], -m[1][2]), MTL::Atan2(m[2][0], m[2][1])};
      else
        return {MTL::Pi<TComponent>(), -MTL::Atan2(-m[0][1], m[0][0]), MTL::Zero<TComponent>()};
    }

    return {MTL::Zero<TComponent>(), MTL::Atan2(-m[0][1], m[0][0]), MTL::Zero<TComponent>()};
  }

  template <typename Matrix, IsArithmeticT TComponent>
  NO_DISCARD constexpr vec3_t<TComponent> ExtractEulerZYZ(const Matrix &m) noexcept
  {
    if (m[2][2] < MTL::One<TComponent>())
    {
      if (m[2][2] > -MTL::One<TComponent>())
        return {MTL::Acos(m[2][2]), MTL::Atan2(m[1][2], m[0][2]), MTL::Atan2(m[2][1], -m[2][0])};
      else
        return {MTL::Pi<TComponent>(), -MTL::Atan2(m[1][0], m[1][1]), MTL::Zero<TComponent>()};
    }

    return {MTL::Zero<TComponent>(), MTL::Atan2(m[1][0], m[1][1]), MTL::Zero<TComponent>()};
  }

  template <typename Matrix, IsArithmeticT TComponent>
  NO_DISCARD constexpr vec3_t<TComponent> ExtractEulerXZY(const Matrix &m) noexcept
  {
    if (m[0][1] < MTL::One<TComponent>())
    {
      if (m[0][1] > -MTL::One<TComponent>())
        return {MTL::Asin(-m[0][1]), MTL::Atan2(m[2][1], m[1][1]), MTL::Atan2(m[0][2], m[0][0])};
      else
        // Not a unique solution: y - x = atan2(-m[2][0], m[2][2]);
        return {MTL::HalfPi<TComponent>(), -MTL::Atan2(-m[2][0], m[2][2]), MTL::Zero<TComponent>()};
    }

    // Not a unique solution: y + x = atan2(-m[2][0], m[2][2]);
    return {-MTL::HalfPi<TComponent>(), MTL::Atan2(-m[2][0], m[2][2]), MTL::Zero<TComponent>()};
  }

  template <typename Matrix, IsArithmeticT TComponent>
  NO_DISCARD constexpr vec3_t<TComponent> ExtractEulerYXZ(const Matrix &m) noexcept
  {
    if (m[1][2] < MTL::One<TComponent>())
    {
      if (m[1][2] > -MTL::One<TComponent>())
      {
        return {MTL::Asin(-m[1][2]), MTL::Atan2(m[0][2], m[2][2]), MTL::Atan2(m[1][0], m[1][1])};
      }
      else
        return {MTL::HalfPi<TComponent>(), -MTL::Atan2(-m[0][1], m[0][0]), MTL::Zero<TComponent>()};
    }

    return {-MTL::HalfPi<TComponent>(), MTL::Atan2(-m[0][1], m[0][0]), MTL::Zero<TComponent>()};
  }

  template <typename Matrix, IsArithmeticT TComponent>
  NO_DISCARD constexpr vec3_t<TComponent> ExtractEulerYZX(const Matrix &m) noexcept
  {
    if (m[1][0] < MTL::One<TComponent>())
    {
      if (m[1][0] > -MTL::One<TComponent>())
        return {MTL::Asin(m[1][0]), MTL::Atan2(-m[2][0], m[0][0]), MTL::Atan2(-m[1][2], m[1][1])};
      else
        return {-MTL::HalfPi<TComponent>(), -MTL::Atan2(m[2][1], m[2][2]), MTL::Zero<TComponent>()};
    }

    return {MTL::HalfPi<TComponent>(), MTL::Atan2(m[2][1], m[2][2]), MTL::Zero<TComponent>()};
  }

  template <typename Matrix, IsArithmeticT TComponent>
  NO_DISCARD constexpr vec3_t<TComponent> ExtractEulerZXY(const Matrix &m) noexcept
  {
    if (m[2][1] < MTL::One<TComponent>())
    {
      if (m[2][1] > -MTL::One<TComponent>())
        return {MTL::Asin(m[2][1]), MTL::Atan2(-m[0][1], m[1][1]), MTL::Atan2(-m[2][0], m[2][2])};
      else
        return {-MTL::HalfPi<TComponent>(), -MTL::Atan2(m[0][2], m[0][0]), MTL::Zero<TComponent>()};
    }

    return {MTL::HalfPi<TComponent>(), MTL::Atan2(m[0][2], m[0][0]), MTL::Zero<TComponent>()};
  }

  template <typename Matrix, IsArithmeticT TComponent>
  NO_DISCARD constexpr vec3_t<TComponent> ExtractEulerZYX(const Matrix &m) noexcept
  {
    if (m[2][0] < MTL::One<TComponent>())
    {
      if (m[2][0] > -MTL::One<TComponent>())
        return {MTL::Asin(-m[2][0]), MTL::Atan2(m[1][0], m[0][0]), MTL::Atan2(m[2][1], m[2][2])};
      else
        return {MTL::HalfPi<TComponent>(), -MTL::Atan2(-m[1][2], m[1][1]), MTL::Zero<TComponent>()};
    }

    return {-MTL::HalfPi<TComponent>(), MTL::Atan2(-m[1][2], m[1][1]), MTL::Zero<TComponent>()};
  }
}

namespace Krys::MTL
{

#pragma region XYX

  /// @brief Converts the given matrix to Euler angles using the XYX convention.
  /// @tparam TComponent the component type of the matrix.
  /// @param m the matrix.
  /// @return A vector of Euler angles around the X, Y, and X axes.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr vec3_t<TComponent> ToEulerXYX(const mat3x3_t<TComponent> &m) noexcept
  {
    return Impl::ExtractEulerXYX<mat3x3_t<TComponent>, TComponent>(m);
  }

  /// @brief Converts the given matrix to Euler angles using the XYX convention.
  /// @tparam TComponent the component type of the matrix.
  /// @param m the matrix.
  /// @return A vector of Euler angles around the X, Y, and X axes.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr vec3_t<TComponent> ToEulerXYX(const mat3x4_t<TComponent> &m) noexcept
  {
    return Impl::ExtractEulerXYX<mat3x4_t<TComponent>, TComponent>(m);
  }

  /// @brief Converts the given matrix to Euler angles using the XYX convention.
  /// @tparam TComponent the component type of the matrix.
  /// @param m the matrix.
  /// @return A vector of Euler angles around the X, Y, and X axes.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr vec3_t<TComponent> ToEulerXYX(const mat4x4_t<TComponent> &m) noexcept
  {
    return Impl::ExtractEulerXYX<mat4x4_t<TComponent>, TComponent>(m);
  }

#pragma endregion XYX

#pragma region XZX

  /// @brief Converts the given matrix to Euler angles using the XZX convention.
  /// @tparam TComponent the component type of the matrix.
  /// @param m the matrix.
  /// @return A vector of Euler angles around the X, Z, and X axes.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr vec3_t<TComponent> ToEulerXZX(const mat3x3_t<TComponent> &m) noexcept
  {
    return Impl::ExtractEulerXZX<mat3x3_t<TComponent>, TComponent>(m);
  }

  /// @brief Converts the given matrix to Euler angles using the XZX convention.
  /// @tparam TComponent the component type of the matrix.
  /// @param m the matrix.
  /// @return A vector of Euler angles around the X, Z, and X axes.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr vec3_t<TComponent> ToEulerXZX(const mat3x4_t<TComponent> &m) noexcept
  {
    return Impl::ExtractEulerXZX<mat3x4_t<TComponent>, TComponent>(m);
  }

  /// @brief Converts the given matrix to Euler angles using the XZX convention.
  /// @tparam TComponent the component type of the matrix.
  /// @param m the matrix.
  /// @return A vector of Euler angles around the X, Z, and X axes.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr vec3_t<TComponent> ToEulerXZX(const mat4x4_t<TComponent> &m) noexcept
  {
    return Impl::ExtractEulerXZX<mat4x4_t<TComponent>, TComponent>(m);
  }

#pragma endregion XZX

#pragma region XYZ

  /// @brief Converts the given matrix to Euler angles using the XYZ convention.
  /// @tparam TComponent the component type of the matrix.
  /// @param m the matrix.
  /// @return A vector of Euler angles around the X, Y, and Z axes.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr vec3_t<TComponent> ToEulerXYZ(const mat3x3_t<TComponent> &m) noexcept
  {
    return Impl::ExtractEulerXYZ<mat3x3_t<TComponent>, TComponent>(m);
  }

  /// @brief Converts the given matrix to Euler angles using the XYZ convention.
  /// @tparam TComponent the component type of the matrix.
  /// @param m the matrix.
  /// @return A vector of Euler angles around the X, Y, and Z axes.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr vec3_t<TComponent> ToEulerXYZ(const mat3x4_t<TComponent> &m) noexcept
  {
    return Impl::ExtractEulerXYZ<mat3x4_t<TComponent>, TComponent>(m);
  }

  /// @brief Converts the given matrix to Euler angles using the XYZ convention.
  /// @tparam TComponent the component type of the matrix.
  /// @param m the matrix.
  /// @return A vector of Euler angles around the X, Y, and Z axes.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr vec3_t<TComponent> ToEulerXYZ(const mat4x4_t<TComponent> &m) noexcept
  {
    return Impl::ExtractEulerXYZ<mat4x4_t<TComponent>, TComponent>(m);
  }

#pragma endregion XYZ

#pragma region YXY

  /// @brief Converts the given matrix to Euler angles using the YXY convention.
  /// @tparam TComponent the component type of the matrix.
  /// @param m the matrix.
  /// @return A vector of Euler angles around the Y, X, and Y axes.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr vec3_t<TComponent> ToEulerYXY(const mat3x3_t<TComponent> &m) noexcept
  {
    return Impl::ExtractEulerYXY<mat3x3_t<TComponent>, TComponent>(m);
  }

  /// @brief Converts the given matrix to Euler angles using the YXY convention.
  /// @tparam TComponent the component type of the matrix.
  /// @param m the matrix.
  /// @return A vector of Euler angles around the Y, X, and Y axes.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr vec3_t<TComponent> ToEulerYXY(const mat3x4_t<TComponent> &m) noexcept
  {
    return Impl::ExtractEulerYXY<mat3x4_t<TComponent>, TComponent>(m);
  }

  /// @brief Converts the given matrix to Euler angles using the YXY convention.
  /// @tparam TComponent the component type of the matrix.
  /// @param m the matrix.
  /// @return A vector of Euler angles around the Y, X, and Y axes.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr vec3_t<TComponent> ToEulerYXY(const mat4x4_t<TComponent> &m) noexcept
  {
    return Impl::ExtractEulerYXY<mat4x4_t<TComponent>, TComponent>(m);
  }

#pragma endregion YXY

#pragma region YZY

  /// @brief Converts the given matrix to Euler angles using the YZY convention.
  /// @tparam TComponent the component type of the matrix.
  /// @param m the matrix.
  /// @return A vector of Euler angles around the Y, Z, and Y axes.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr vec3_t<TComponent> ToEulerYZY(const mat3x3_t<TComponent> &m) noexcept
  {
    return Impl::ExtractEulerYZY<mat3x3_t<TComponent>, TComponent>(m);
  }

  /// @brief Converts the given matrix to Euler angles using the YZY convention.
  /// @tparam TComponent the component type of the matrix.
  /// @param m the matrix.
  /// @return A vector of Euler angles around the Y, Z, and Y axes.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr vec3_t<TComponent> ToEulerYZY(const mat3x4_t<TComponent> &m) noexcept
  {
    return Impl::ExtractEulerYZY<mat3x4_t<TComponent>, TComponent>(m);
  }

  /// @brief Converts the given matrix to Euler angles using the YZY convention.
  /// @tparam TComponent the component type of the matrix.
  /// @param m the matrix.
  /// @return A vector of Euler angles around the Y, Z, and Y axes.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr vec3_t<TComponent> ToEulerYZY(const mat4x4_t<TComponent> &m) noexcept
  {
    return Impl::ExtractEulerYZY<mat4x4_t<TComponent>, TComponent>(m);
  }

#pragma endregion YZY

#pragma region ZXZ

  /// @brief Converts the given matrix to Euler angles using the ZXZ convention.
  /// @tparam TComponent the component type of the matrix.
  /// @param m the matrix.
  /// @return A vector of Euler angles around the Z, X, and Z axes.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr vec3_t<TComponent> ToEulerZXZ(const mat3x3_t<TComponent> &m) noexcept
  {
    return Impl::ExtractEulerZXZ<mat3x3_t<TComponent>, TComponent>(m);
  }

  /// @brief Converts the given matrix to Euler angles using the ZXZ convention.
  /// @tparam TComponent the component type of the matrix.
  /// @param m the matrix.
  /// @return A vector of Euler angles around the Z, X, and Z axes.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr vec3_t<TComponent> ToEulerZXZ(const mat3x4_t<TComponent> &m) noexcept
  {
    return Impl::ExtractEulerZXZ<mat3x4_t<TComponent>, TComponent>(m);
  }

  /// @brief Converts the given matrix to Euler angles using the ZXZ convention.
  /// @tparam TComponent the component type of the matrix.
  /// @param m the matrix.
  /// @return A vector of Euler angles around the Z, X, and Z axes.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr vec3_t<TComponent> ToEulerZXZ(const mat4x4_t<TComponent> &m) noexcept
  {
    return Impl::ExtractEulerZXZ<mat4x4_t<TComponent>, TComponent>(m);
  }

#pragma endregion ZXZ

#pragma region ZYZ

  /// @brief Converts the given matrix to Euler angles using the ZYZ convention.
  /// @tparam TComponent the component type of the matrix.
  /// @param m the matrix.
  /// @return A vector of Euler angles around the Z, Y, and Z axes.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr vec3_t<TComponent> ToEulerZYZ(const mat3x3_t<TComponent> &m) noexcept
  {
    return Impl::ExtractEulerZYZ<mat3x3_t<TComponent>, TComponent>(m);
  }

  /// @brief Converts the given matrix to Euler angles using the ZYZ convention.
  /// @tparam TComponent the component type of the matrix.
  /// @param m the matrix.
  /// @return A vector of Euler angles around the Z, Y, and Z axes.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr vec3_t<TComponent> ToEulerZYZ(const mat3x4_t<TComponent> &m) noexcept
  {
    return Impl::ExtractEulerZYZ<mat3x4_t<TComponent>, TComponent>(m);
  }

  /// @brief Converts the given matrix to Euler angles using the ZYZ convention.
  /// @tparam TComponent the component type of the matrix.
  /// @param m the matrix.
  /// @return A vector of Euler angles around the Z, Y, and Z axes.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr vec3_t<TComponent> ToEulerZYZ(const mat4x4_t<TComponent> &m) noexcept
  {
    return Impl::ExtractEulerZYZ<mat4x4_t<TComponent>, TComponent>(m);
  }

#pragma endregion ZYZ

#pragma region XZY

  /// @brief Converts the given matrix to Euler angles using the XZY convention.
  /// @tparam TComponent the component type of the matrix.
  /// @param m the matrix.
  /// @return A vector of Euler angles around the X, Z, and Y axes.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr vec3_t<TComponent> ToEulerXZY(const mat3x3_t<TComponent> &m) noexcept
  {
    return Impl::ExtractEulerXZY<mat3x3_t<TComponent>, TComponent>(m);
  }

  /// @brief Converts the given matrix to Euler angles using the XZY convention.
  /// @tparam TComponent the component type of the matrix.
  /// @param m the matrix.
  /// @return A vector of Euler angles around the X, Z, and Y axes.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr vec3_t<TComponent> ToEulerXZY(const mat3x4_t<TComponent> &m) noexcept
  {
    return Impl::ExtractEulerXZY<mat3x4_t<TComponent>, TComponent>(m);
  }

  /// @brief Converts the given matrix to Euler angles using the XZY convention.
  /// @tparam TComponent the component type of the matrix.
  /// @param m the matrix.
  /// @return A vector of Euler angles around the X, Z, and Y axes.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr vec3_t<TComponent> ToEulerXZY(const mat4x4_t<TComponent> &m) noexcept
  {
    return Impl::ExtractEulerXZY<mat4x4_t<TComponent>, TComponent>(m);
  }

#pragma endregion XZY

#pragma region YXZ

  /// @brief Converts the given matrix to Euler angles using the YXZ convention.
  /// @tparam TComponent the component type of the matrix.
  /// @param m the matrix.
  /// @return A vector of Euler angles around the Y, X, and Z axes.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr vec3_t<TComponent> ToEulerYXZ(const mat3x3_t<TComponent> &m) noexcept
  {
    return Impl::ExtractEulerYXZ<mat3x3_t<TComponent>, TComponent>(m);
  }

  /// @brief Converts the given matrix to Euler angles using the YXZ convention.
  /// @tparam TComponent the component type of the matrix.
  /// @param m the matrix.
  /// @return A vector of Euler angles around the Y, X, and Z axes.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr vec3_t<TComponent> ToEulerYXZ(const mat3x4_t<TComponent> &m) noexcept
  {
    return Impl::ExtractEulerYXZ<mat3x4_t<TComponent>, TComponent>(m);
  }

  /// @brief Converts the given matrix to Euler angles using the YXZ convention.
  /// @tparam TComponent the component type of the matrix.
  /// @param m the matrix.
  /// @return A vector of Euler angles around the Y, X, and Z axes.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr vec3_t<TComponent> ToEulerYXZ(const mat4x4_t<TComponent> &m) noexcept
  {
    return Impl::ExtractEulerYXZ<mat4x4_t<TComponent>, TComponent>(m);
  }

#pragma endregion YXZ

#pragma region YZX

  /// @brief Converts the given matrix to Euler angles using the YZX convention.
  /// @tparam TComponent the component type of the matrix.
  /// @param m the matrix.
  /// @return A vector of Euler angles around the Y, Z and X axes.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr vec3_t<TComponent> ToEulerYZX(const mat3x3_t<TComponent> &m) noexcept
  {
    return Impl::ExtractEulerYZX<mat3x3_t<TComponent>, TComponent>(m);
  }

  /// @brief Converts the given matrix to Euler angles using the YZX convention.
  /// @tparam TComponent the component type of the matrix.
  /// @param m the matrix.
  /// @return A vector of Euler angles around the Y, Z and X axes.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr vec3_t<TComponent> ToEulerYZX(const mat3x4_t<TComponent> &m) noexcept
  {
    return Impl::ExtractEulerYZX<mat3x4_t<TComponent>, TComponent>(m);
  }

  /// @brief Converts the given matrix to Euler angles using the YZX convention.
  /// @tparam TComponent the component type of the matrix.
  /// @param m the matrix.
  /// @return A vector of Euler angles around the Y, Z and X axes.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr vec3_t<TComponent> ToEulerYZX(const mat4x4_t<TComponent> &m) noexcept
  {
    return Impl::ExtractEulerYZX<mat4x4_t<TComponent>, TComponent>(m);
  }

#pragma endregion YZX

#pragma region ZXY

  /// @brief Converts the given matrix to Euler angles using the ZXY convention.
  /// @tparam TComponent the component type of the matrix.
  /// @param m the matrix.
  /// @return A vector of Euler angles around the Z, X and Y axes.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr vec3_t<TComponent> ToEulerZXY(const mat3x3_t<TComponent> &m) noexcept
  {
    return Impl::ExtractEulerZXY<mat3x3_t<TComponent>, TComponent>(m);
  }

  /// @brief Converts the given matrix to Euler angles using the ZXY convention.
  /// @tparam TComponent the component type of the matrix.
  /// @param m the matrix.
  /// @return A vector of Euler angles around the Z, X and Y axes.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr vec3_t<TComponent> ToEulerZXY(const mat3x4_t<TComponent> &m) noexcept
  {
    return Impl::ExtractEulerZXY<mat3x4_t<TComponent>, TComponent>(m);
  }

  /// @brief Converts the given matrix to Euler angles using the ZXY convention.
  /// @tparam TComponent the component type of the matrix.
  /// @param m the matrix.
  /// @return A vector of Euler angles around the Z, X and Y axes.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr vec3_t<TComponent> ToEulerZXY(const mat4x4_t<TComponent> &m) noexcept
  {
    return Impl::ExtractEulerZXY<mat4x4_t<TComponent>, TComponent>(m);
  }

#pragma endregion ZXY

#pragma region ZYX

  /// @brief Converts the given matrix to Euler angles using the ZYX convention.
  /// @tparam TComponent the component type of the matrix.
  /// @param m the matrix.
  /// @return A vector of Euler angles around the Z, Y and X axes.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr vec3_t<TComponent> ToEulerZYX(const mat3x3_t<TComponent> &m) noexcept
  {
    return Impl::ExtractEulerZYX<mat3x3_t<TComponent>, TComponent>(m);
  }

  /// @brief Converts the given matrix to Euler angles using the ZYX convention.
  /// @tparam TComponent the component type of the matrix.
  /// @param m the matrix.
  /// @return A vector of Euler angles around the Z, Y and X axes.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr vec3_t<TComponent> ToEulerZYX(const mat3x4_t<TComponent> &m) noexcept
  {
    return Impl::ExtractEulerZYX<mat3x4_t<TComponent>, TComponent>(m);
  }

  /// @brief Converts the given matrix to Euler angles using the ZYX convention.
  /// @tparam TComponent the component type of the matrix.
  /// @param m the matrix.
  /// @return A vector of Euler angles around the Z, Y and X axes.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr vec3_t<TComponent> ToEulerZYX(const mat4x4_t<TComponent> &m) noexcept
  {
    return Impl::ExtractEulerZYX<mat4x4_t<TComponent>, TComponent>(m);
  }

#pragma endregion ZYX

}