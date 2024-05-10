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
}