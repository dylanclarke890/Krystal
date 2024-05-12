#pragma once

#include "Graphics/Camera/Camera.h"

namespace Krys
{
  class OrthographicCamera : public Camera
  {
  private:
    float m_Rotation;
    RectBounds m_Bounds;

  public:
    OrthographicCamera(const RectBounds &bounds, float zNear, float zFar) noexcept
        : Camera(Vec3(0.0f), zNear, zFar), m_Rotation(0.0f), m_Bounds(bounds)
    {
      CalculateViewMatrix();
      CalculateProjectionMatrix();
      CalculateViewProjectionMatrix();
    }

    void SetProjection(const RectBounds &bounds, float zNear, float zFar) noexcept
    {
      m_Bounds = bounds;
      CalculateProjectionMatrix();
      CalculateViewProjectionMatrix();
    }

    void SetRotation(float rotation) noexcept
    {
      m_Rotation = rotation;
      CalculateViewMatrix();
      CalculateViewProjectionMatrix();
    }

    float GetRotation() const noexcept
    {
      return m_Rotation;
    }

    void OnUpdate(float dt) noexcept override {}
    void OnEvent(Event &event) noexcept override {}

  protected:
    void CalculateProjectionMatrix() noexcept override
    {
      m_Projection = glm::ortho(m_Bounds.Left, m_Bounds.Right, m_Bounds.Bottom, m_Bounds.Top, m_ZNear, m_ZFar);
    }

    void CalculateViewMatrix() noexcept override
    {
      Mat4 rotation = glm::rotate(Mat4(1.0f), glm::radians(m_Rotation), Vec3(0, 0, 1));
      Mat4 transform = glm::translate(Mat4(1.0f), m_CameraPosition) * rotation;
      m_View = glm::inverse(transform);
    }
  };
}