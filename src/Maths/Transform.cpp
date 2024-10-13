#include "Maths/Transform.h"

namespace Krys::Maths
{
  constexpr Vec3 DEFAULT_TRANSLATION = Vec3(0.0f);
  constexpr Vec3 DEFAULT_SCALE = Vec3(1.0f);
  constexpr Vec3 DEFAULT_ROTATION = Vec3(0.0f);

  Transform::Transform() noexcept
      : Translation(DEFAULT_TRANSLATION), Scale(DEFAULT_SCALE), EulerRotation(DEFAULT_ROTATION)
  {
  }

  Transform::Transform(const Vec3 &translation) noexcept
      : Translation(translation), Scale(DEFAULT_SCALE), EulerRotation(DEFAULT_ROTATION)
  {
  }

  Transform::Transform(const Vec3 &translation, const Vec3 &scale) noexcept
      : Translation(translation), Scale(scale), EulerRotation(DEFAULT_ROTATION)
  {
  }

  Transform::Transform(const Vec3 &translation, const Vec3 &scale, const Vec3 &rotation) noexcept
      : Translation(translation), Scale(scale), EulerRotation(rotation)
  {
  }

  NO_DISCARD const Mat4 &Transform::GetMatrix() noexcept
  {
    if (Dirty)
      ComputeMatrix();

    return Matrix;
  }

  NO_DISCARD const Vec3 &Transform::GetTranslation() const noexcept
  {
    return Translation;
  }

  NO_DISCARD const Vec3 &Transform::GetScale() const noexcept
  {
    return Scale;
  }
  NO_DISCARD const Vec3 &Transform::GetEulerRotation() const noexcept
  {
    return EulerRotation;
  }

  void Transform::SetTranslation(const Vec3 &translation) noexcept
  {
    Translation = translation;
    Dirty = true;
  }

  void Transform::SetScale(const Vec3 &scale) noexcept
  {
    Scale = scale;
    Dirty = true;
  }

  void Transform::SetEulerRotation(const Vec3 &rotation) noexcept
  {
    EulerRotation = rotation;
    Dirty = true;
  }

  void Transform::ComputeMatrix() noexcept
  {
    Mat4 matrix = glm::translate(MAT4_I, Translation);

    if (EulerRotation.x)
      matrix *= glm::rotate(MAT4_I, glm::radians(EulerRotation.x), ROTATE_AXIS_X);
    if (EulerRotation.y)
      matrix *= glm::rotate(MAT4_I, glm::radians(EulerRotation.y), ROTATE_AXIS_Y);
    if (EulerRotation.z)
      matrix *= glm::rotate(MAT4_I, glm::radians(EulerRotation.z), ROTATE_AXIS_Z);

    Matrix = matrix * glm::scale(MAT4_I, Scale);
    Dirty = false;
  }
}