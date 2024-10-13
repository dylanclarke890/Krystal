#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Core.h"

namespace Krys::Maths
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
}