#pragma once

#include "Maths/Maths.h"
#include "Events/Events.h"

namespace Krys
{
  class Camera
  {
  protected:
    Vec3 m_CameraPosition;
    float m_ZNear, m_ZFar;
    Mat4 m_View, m_Projection, m_ViewProjection;

    Camera(Vec3 cameraPosition, float zNear, float zFar) noexcept
        : m_CameraPosition(cameraPosition), m_ZNear(zNear), m_ZFar(zFar),
          m_View(Mat4(1.0f)), m_Projection(Mat4(1.0f)), m_ViewProjection(Mat4(1.0f)) {}

  public:
    const Vec3 &GetPosition() const noexcept
    {
      return m_CameraPosition;
    }

    void SetPosition(Vec3 position) noexcept
    {
      m_CameraPosition = position;
      CalculateViewMatrix();
      CalculateViewProjectionMatrix();
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

    virtual void OnUpdate(float dt) noexcept = 0;
    virtual void OnEvent(Event &event) noexcept = 0;

  protected:
    virtual void CalculateViewMatrix() noexcept = 0;
    virtual void CalculateProjectionMatrix() noexcept = 0;

    void CalculateViewProjectionMatrix() noexcept
    {
      m_ViewProjection = m_Projection * m_View;
    }
  };
}