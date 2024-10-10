#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Krys
{
  typedef glm::vec2 Vec2;
  typedef glm::vec3 Vec3;
  typedef glm::vec4 Vec4;

  typedef glm::ivec2 Vec2i;
  typedef glm::ivec3 Vec3i;
  typedef glm::ivec4 Vec4i;

  typedef glm::mat2 Mat2;
  typedef glm::mat3 Mat3;
  typedef glm::mat4 Mat4;

  /// @brief Mat3 Identity Matrix.
  constexpr Mat3 MAT3_I = Mat3(1.0f);

  /// @brief Mat4 Identity Matrix.
  constexpr Mat4 MAT4_I = Mat4(1.0f);

  constexpr Vec3 ROTATE_AXIS_X = Vec3(1.0f, 0.0f, 0.0f);
  constexpr Vec3 ROTATE_AXIS_Y = Vec3(0.0f, 1.0f, 0.0f);
  constexpr Vec3 ROTATE_AXIS_Z = Vec3(0.0f, 0.0f, 1.0f);

  constexpr float PI32 = 3.1415927f;
  constexpr double PI64 = 3.141592653589793;

  inline constexpr float DegToRad(float degrees) noexcept
  {
    constexpr float ratio = PI32 * 2.0f / 360.0f;
    return degrees * ratio;
  }

  template <typename T>
  REQUIRES(std::is_integral_v<T> || std::is_floating_point_v<T>)
  constexpr T Max(const T &a, const T &b) noexcept
  {
    return a > b ? a : b;
  }

  template <typename T>
  REQUIRES(std::is_integral_v<T> || std::is_floating_point_v<T>)
  constexpr T Min(const T &a, const T &b) noexcept
  {
    return a < b ? a : b;
  }

  template <typename T>
  REQUIRES(std::is_integral_v<T> || std::is_floating_point_v<T>)
  constexpr T Clamp(const T &value, const T &min, const T &max) noexcept
  {
    return Min<T>(Max<T>(value, min), max);
  }

  template <typename T>
  REQUIRES(std::is_integral_v<T> || std::is_floating_point_v<T>)
  struct BoundingBox
  {
    T Left, Right, Bottom, Top;

    BoundingBox() noexcept = default;
    constexpr BoundingBox(T left, T right, T bottom, T top) noexcept
        : Left(left), Right(right), Bottom(bottom), Top(top) {}

    constexpr T GetWidth() const noexcept { return Right - Left; }
    constexpr T GetHeight() const noexcept { return Top - Bottom; }
  };
}