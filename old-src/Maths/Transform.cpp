#include "Maths/Transform.h"

namespace Krys::Maths
{
  constexpr Vec3 DEFAULT_TRANSLATION = Vec3(0.0f);
  constexpr Vec3 DEFAULT_SCALE = Vec3(1.0f);
  constexpr Vec3 DEFAULT_ROTATION = Vec3(0.0f);

  Transform::Transform() noexcept
      : _translation(DEFAULT_TRANSLATION), _scale(DEFAULT_SCALE), _eulerRotation(DEFAULT_ROTATION), _matrix(MAT4_I)
  {
  }

  Transform::Transform(const Vec3 &translation) noexcept
      : _translation(translation), _scale(DEFAULT_SCALE), _eulerRotation(DEFAULT_ROTATION), _matrix(MAT4_I)
  {
  }

  Transform::Transform(const Vec3 &translation, const Vec3 &scale) noexcept
      : _translation(translation), _scale(scale), _eulerRotation(DEFAULT_ROTATION), _matrix(MAT4_I)
  {
  }

  Transform::Transform(const Vec3 &translation, const Vec3 &scale, const Vec3 &rotation) noexcept
      : _translation(translation), _scale(scale), _eulerRotation(rotation), _matrix(MAT4_I)
  {
  }

  NO_DISCARD const Mat4 &Transform::GetMatrix() noexcept
  {
    if (_dirty)
      ComputeMatrix();

    return _matrix;
  }

  NO_DISCARD const Vec3 &Transform::GetTranslation() const noexcept
  {
    return _translation;
  }

  NO_DISCARD const Vec3 &Transform::GetScale() const noexcept
  {
    return _scale;
  }
  NO_DISCARD const Vec3 &Transform::GetEulerRotation() const noexcept
  {
    return _eulerRotation;
  }

  void Transform::SetTranslation(const Vec3 &translation) noexcept
  {
    _translation = translation;
    _dirty = true;
  }

  void Transform::SetScale(const Vec3 &scale) noexcept
  {
    _scale = scale;
    _dirty = true;
  }

  void Transform::SetEulerRotation(const Vec3 &rotation) noexcept
  {
    _eulerRotation = rotation;
    _dirty = true;
  }

  void Transform::ComputeMatrix() noexcept
  {
    Mat4 matrix = glm::translate(MAT4_I, _translation);

    if (_eulerRotation.x)
      matrix *= glm::rotate(MAT4_I, glm::radians(_eulerRotation.x), ROTATE_AXIS_X);
    if (_eulerRotation.y)
      matrix *= glm::rotate(MAT4_I, glm::radians(_eulerRotation.y), ROTATE_AXIS_Y);
    if (_eulerRotation.z)
      matrix *= glm::rotate(MAT4_I, glm::radians(_eulerRotation.z), ROTATE_AXIS_Z);

    _matrix = matrix * glm::scale(MAT4_I, _scale);
    _dirty = false;
  }
}