#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Krys
{
  typedef glm::vec4 Vec4;
  typedef glm::ivec4 Vec4i;

  typedef glm::vec3 Vec3;
  typedef glm::ivec3 Vec3i;

  typedef glm::vec2 Vec2;
  typedef glm::ivec2 Vec2i;

  typedef glm::mat3 Mat3;
  typedef glm::mat4 Mat4;

  constexpr float PI32 = 3.1415927f;
  constexpr double PI64 = 3.141592653589793;

  /// @brief Mat4 Identity Matrix.
  constexpr Mat4 MAT4_I = Mat4(1.0f);

  /// @brief Mat3 Identity Matrix.
  constexpr Mat3 MAT3_I = Mat3(1.0f);

  constexpr Vec3 ROTATE_AXIS_X = Vec3(1.0f, 0.0f, 0.0f);
  constexpr Vec3 ROTATE_AXIS_Y = Vec3(0.0f, 1.0f, 0.0f);
  constexpr Vec3 ROTATE_AXIS_Z = Vec3(0.0f, 0.0f, 1.0f);

  inline constexpr float DegToRad(float degrees) noexcept
  {
    constexpr float ratio = PI32 * 2.0f / 360.0f;
    return degrees * ratio;
  }

  inline constexpr float Clamp(float value, float min, float max) noexcept
  {
    if (value < min)
      return min;

    if (value > max)
      return max;

    return value;
  }

  struct RectBounds
  {
    float Left, Right, Bottom, Top;

    RectBounds() = default;
    constexpr RectBounds(float left, float right, float bottom, float top)
        : Left(left), Right(right), Bottom(bottom), Top(top) {}

    constexpr float GetWidth() { return Right - Left; }
    constexpr float GetHeight() { return Top - Bottom; }
  };
}