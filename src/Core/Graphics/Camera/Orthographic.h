#pragma once

#include "Maths/Maths.h"

namespace Krys
{
  class OrthographicCamera
  {
  private:
    Mat4 m_View;
    Mat4 m_Projection;
    Mat4 m_ViewProjection;

    Vec3 m_Position;
    float m_Rotation;

  public:
    OrthographicCamera(float left, float right, float bottom, float top)
        : m_View(1.0f),
          m_Projection(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)),
          m_Position(0.0f),
          m_Rotation(0.0f)
    {
      RecalculateViewProjectionMatrix();
    }

    void SetProjection(float left, float right, float bottom, float top)
    {
      m_Projection = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
      RecalculateViewProjectionMatrix();
    }

    void SetPosition(const Vec3 &position)
    {
      m_Position = position;
      RecalculateViewMatrix();
    }

    const Vec3 &GetPosition() const
    {
      return m_Position;
    }

    void SetRotation(float rotation)
    {
      m_Rotation = rotation;
      RecalculateViewMatrix();
    }

    float GetRotation() const
    {
      return m_Rotation;
    }

    const Mat4 &GetViewMatrix() const
    {
      return m_View;
    }

    const Mat4 &GetProjectionMatrix() const
    {
      return m_Projection;
    }

    const Mat4 &GetViewProjectionMatrix() const
    {
      return m_ViewProjection;
    }

  private:
    void RecalculateViewMatrix()
    {
      Mat4 rotation = glm::rotate(Mat4(1.0f), glm::radians(m_Rotation), Vec3(0, 0, 1));
      Mat4 transform = glm::translate(Mat4(1.0f), m_Position) * rotation;

      m_View = glm::inverse(transform);
      RecalculateViewProjectionMatrix();
    }

    void RecalculateViewProjectionMatrix()
    {
      m_ViewProjection = m_Projection * m_View;
    }
  };
}