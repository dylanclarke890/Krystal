#pragma once

#include "Maths/Maths.h"
#include "Events/Events.h"

namespace Krys
{
  class Camera
  {
  protected:
    Vec3 Position;
    float ZNear, ZFar;
    Mat4 View, Projection, ViewProjection;

    Camera(Vec3 position, float zNear, float zFar) noexcept
        : Position(position), ZNear(zNear), ZFar(zFar),
          View(MAT4_I), Projection(MAT4_I), ViewProjection(MAT4_I) {}

  public:
    const Vec3 &GetPosition() const noexcept
    {
      return Position;
    }

    void SetPosition(const Vec3 &position) noexcept
    {
      Position = position;
      CalculateViewMatrix();
      CalculateViewProjectionMatrix();
    }

    const Mat4 &GetView() const noexcept
    {
      return View;
    }

    const Mat4 &GetProjection() const noexcept
    {
      return Projection;
    }

    const Mat4 &GetViewProjection() const noexcept
    {
      return ViewProjection;
    }

  protected:
    virtual void CalculateViewMatrix() noexcept = 0;
    virtual void CalculateProjectionMatrix() noexcept = 0;

    void CalculateViewProjectionMatrix() noexcept
    {
      ViewProjection = Projection * View;
    }
  };
}