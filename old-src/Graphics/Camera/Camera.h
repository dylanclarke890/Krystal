#pragma once

#include "Maths/Vector.h"
#include "Events/Events.h"

namespace Krys::Gfx
{
  using namespace Krys::Maths;

  class Camera
  {
  protected:
    Vec3 _position;
    float _near, _far;
    Mat4 _view, _projection, _viewProjection;

    Camera(Vec3 position, float zNear, float zFar) noexcept
        : _position(position), _near(zNear), _far(zFar),
          _view(MAT4_I), _projection(MAT4_I), _viewProjection(MAT4_I) {}

  public:
    const Vec3 &GetPosition() const noexcept
    {
      return _position;
    }

    void SetPosition(const Vec3 &position) noexcept
    {
      _position = position;
      CalculateViewMatrix();
      CalculateViewProjectionMatrix();
    }

    const Mat4 &GetView() const noexcept
    {
      return _view;
    }

    const Mat4 &GetProjection() const noexcept
    {
      return _projection;
    }

    const Mat4 &GetViewProjection() const noexcept
    {
      return _viewProjection;
    }

  protected:
    virtual void CalculateViewMatrix() noexcept = 0;
    virtual void CalculateProjectionMatrix() noexcept = 0;

    void CalculateViewProjectionMatrix() noexcept
    {
      _viewProjection = _projection * _view;
    }
  };
}