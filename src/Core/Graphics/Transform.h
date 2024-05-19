#pragma once

#include "Maths/Maths.h"

namespace Krys
{
  class Transform
  {
  public:
    Vec3 Position;
    Vec3 Size;
    Vec3 Rotation;

    Transform(Vec3 position, Vec3 size, Vec3 rotation = {}) noexcept
        : Position(position), Size(size), Rotation(rotation) {}

    Transform(Vec3 position, Vec3 size, float rotation) noexcept
        : Position(position), Size(size), Rotation({0.0f, 0.0f, rotation}) {}

    Transform(Vec2 position, Vec2 size, float rotation = 0.0f) noexcept
        : Position({position, 0.0f}), Size({size, 1.0f}), Rotation({0.0f, 0.0f, rotation}) {}

    Mat4 GetModel() const noexcept
    {
      Mat4 model = glm::translate(MAT4_I, Position);
      if (Rotation.x)
        model *= glm::rotate(MAT4_I, glm::radians(Rotation.x), ROTATE_AXIS_X);

      if (Rotation.y)
        model *= glm::rotate(MAT4_I, glm::radians(Rotation.y), ROTATE_AXIS_Y);

      if (Rotation.z)
        model *= glm::rotate(MAT4_I, glm::radians(Rotation.z), ROTATE_AXIS_Z);

      return model * glm::scale(MAT4_I, Size);
    }
  };
}