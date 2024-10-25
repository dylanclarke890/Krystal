#pragma once

#include "Maths/Vector.h"
#include "Types.h"

namespace Krys::Maths
{
  class Transform
  {
  private:
    bool _dirty = true;
    Vec3 _translation, _scale, _eulerRotation;
    Mat4 _matrix;

  public:
    Transform() noexcept;
    Transform(const Vec3 &translation) noexcept;
    Transform(const Vec3 &translation, const Vec3 &scale) noexcept;
    Transform(const Vec3 &translation, const Vec3 &scale, const Vec3 &rotation) noexcept;

    NO_DISCARD const Mat4 &GetMatrix() noexcept;
    NO_DISCARD const Vec3 &GetTranslation() const noexcept;
    NO_DISCARD const Vec3 &GetScale() const noexcept;
    NO_DISCARD const Vec3 &GetEulerRotation() const noexcept;

    void SetTranslation(const Vec3 &translation) noexcept;
    void SetScale(const Vec3 &scale) noexcept;
    void SetEulerRotation(const Vec3 &rotation) noexcept;

  private:
    void ComputeMatrix() noexcept;
  };
}