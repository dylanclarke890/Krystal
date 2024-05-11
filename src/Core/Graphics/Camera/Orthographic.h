#pragma once

#include "Graphics/Camera/Camera.h"

namespace Krys
{
  class OrthographicCamera : public Camera
  {
  private:
    float m_Rotation;

  public:
    OrthographicCamera(const RectBounds &bounds, float zNear, float zFar)
        : m_Rotation(0.0f)
    {
      m_CameraPosition = Vec3(0.0f);
      m_View = Mat4(1.0f);
      m_Projection = glm::ortho(bounds.Left, bounds.Right, bounds.Bottom, bounds.Top, zNear, zFar);
      CalculateViewProjectionMatrix();
    }

    void SetProjection(const RectBounds &bounds, float zNear, float zFar) noexcept
    {
      m_Projection = glm::ortho(bounds.Left, bounds.Right, bounds.Bottom, bounds.Top, zNear, zFar);
      CalculateViewProjectionMatrix();
    }

    void SetPosition(const Vec3 &position) noexcept
    {
      m_CameraPosition = position;
      CalculateViewMatrix();
    }

    void SetRotation(float rotation) noexcept
    {
      m_Rotation = rotation;
      CalculateViewMatrix();
    }

    float GetRotation() const noexcept
    {
      return m_Rotation;
    }

  private:
    void CalculateViewMatrix() noexcept
    {
      Mat4 rotation = glm::rotate(Mat4(1.0f), glm::radians(m_Rotation), Vec3(0, 0, 1));
      Mat4 transform = glm::translate(Mat4(1.0f), m_CameraPosition) * rotation;

      m_View = glm::inverse(transform);
      CalculateViewProjectionMatrix();
    }
  };
}