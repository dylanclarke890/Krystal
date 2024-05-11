#pragma once

#include "Graphics/Camera/Camera.h"
#include "Input/Input.h"
#include "Misc/Time.h"

namespace Krys
{
  class PerspectiveCamera : public Camera
  {
  private:
    Vec3 m_CameraFront;
    Vec3 m_CameraUp;

    float m_CameraSpeed = 5.0f;
    float m_Yaw = -90.0f;
    float m_Pitch = 0.0f;

  public:
    PerspectiveCamera(float fovAngle, float aspectRatio, float zNear, float zFar)
    {
      m_CameraPosition = Vec3(0.0f, 0.0f, 3.0f);
      m_CameraFront = Vec3(0.0f, 0.0f, -1.0f);
      m_CameraUp = Vec3(0.0f, 1.0f, 0.0f);

      m_Projection = glm::perspective(glm::radians(fovAngle), aspectRatio, zNear, zFar);

      Vec3 direction = Vec3(0.0f);
      direction.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
      direction.y = sin(glm::radians(m_Pitch));
      direction.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));

      RecalculateViewMatrix();
    }

    void OnUpdate(float dt) noexcept
    {
      float speed = m_CameraSpeed * dt;
      if (Input::IsKeyPressed(KeyCode::UpArrow) || Input::IsKeyPressed(KeyCode::W))
        m_CameraPosition += speed * m_CameraFront;
      if (Input::IsKeyPressed(KeyCode::DownArrow) || Input::IsKeyPressed(KeyCode::S))
        m_CameraPosition -= speed * m_CameraFront;
      if (Input::IsKeyPressed(KeyCode::LeftArrow) || Input::IsKeyPressed(KeyCode::A))
        m_CameraPosition -= glm::normalize(glm::cross(m_CameraFront, m_CameraUp)) * speed;
      if (Input::IsKeyPressed(KeyCode::RightArrow) || Input::IsKeyPressed(KeyCode::D))
        m_CameraPosition += glm::normalize(glm::cross(m_CameraFront, m_CameraUp)) * speed;

      // const float radius = 10.0f;
      // m_CameraPosition.x = sin(Time::GetElapsedSecs()) * radius;
      // m_CameraPosition.z = cos(Time::GetElapsedSecs()) * radius;

      RecalculateViewMatrix();
    }

    void SetPosition(Vec3 position)
    {
      m_CameraPosition = position;
      RecalculateViewMatrix();
    }

  private:
    void RecalculateViewMatrix() noexcept
    {
      m_View = glm::lookAt(m_CameraPosition, m_CameraPosition + m_CameraFront, m_CameraUp);
      RecalculateViewProjectionMatrix();
    }
  };
}