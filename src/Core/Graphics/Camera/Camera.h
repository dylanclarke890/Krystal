#pragma once

#include "Maths/Maths.h"
#include "Events/Events.h"

namespace Krys
{
  class Camera
  {
  protected:
    Vec3 m_CameraPosition = Vec3(0.0f);

    Mat4 m_View = Mat4(1.0f);
    Mat4 m_Projection = Mat4(1.0f);
    Mat4 m_ViewProjection = Mat4(1.0f);

  public:
    const Vec3 &GetPosition() const noexcept
    {
      return m_CameraPosition;
    }

    const Mat4 &GetView() const noexcept
    {
      return m_View;
    }

    const Mat4 &GetProjection() const noexcept
    {
      return m_Projection;
    }

    const Mat4 &GetViewProjection() const noexcept
    {
      return m_ViewProjection;
    }

    virtual void OnUpdate(float dt) {}
    virtual void OnEvent(Event &event) {}

  protected:
    void CalculateViewProjectionMatrix() noexcept
    {
      m_ViewProjection = m_Projection * m_View;
    }
  };
}