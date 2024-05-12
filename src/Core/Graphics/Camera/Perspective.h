#pragma once

#include "Graphics/Camera/Camera.h"
#include "Input/Input.h"
#include "Misc/Time.h"
#include "Events/MouseEvent.h"

namespace Krys
{
  class PerspectiveCamera : public Camera
  {
  private:
    Vec3 m_CameraFront;
    Vec3 m_CameraUp;

    float m_CameraSpeed;
    float m_Yaw, m_Pitch;

    float m_FovAngle;
    float m_AspectRatio;
    float m_ZNear, m_ZFar;

    bool m_MoveCamera;
    Vec2 m_LastMousePosition;
    float m_MovementSensitivity;

  public:
    PerspectiveCamera(float fovAngle, float aspectRatio, float zNear, float zFar)
        : m_CameraFront(Vec3(0.0f, 0.0f, -1.0f)), m_CameraUp(Vec3(0.0f, 1.0f, 0.0f)),
          m_CameraSpeed(5.0f), m_Yaw(-90.0f), m_Pitch(0.0f),
          m_FovAngle(fovAngle), m_AspectRatio(aspectRatio),
          m_ZNear(zNear), m_ZFar(zFar),
          m_MoveCamera(false), m_LastMousePosition(0.0f), m_MovementSensitivity(0.1f)
    {
      m_CameraPosition = Vec3(0.0f, 0.0f, 3.0f);

      CalculateCameraVectors();

      CalculateViewMatrix();
      CalculateProjectionMatrix();
      CalculateViewProjectionMatrix();
    }

    void SetPosition(Vec3 position)
    {
      m_CameraPosition = position;
      CalculateViewMatrix();
    }

    void OnUpdate(float dt) noexcept override
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

      CalculateViewMatrix();
      CalculateViewProjectionMatrix();
    }

    void OnEvent(Event &event) override
    {
      EventDispatcher dispatcher(event);
      dispatcher.Dispatch<MouseButtonPressedEvent>(KRYS_BIND_EVENT_FN(PerspectiveCamera::OnMouseButtonPressedEvent));
      dispatcher.Dispatch<MouseButtonReleasedEvent>(KRYS_BIND_EVENT_FN(PerspectiveCamera::OnMouseButtonReleasedEvent));
      dispatcher.Dispatch<MouseScrollEvent>(KRYS_BIND_EVENT_FN(PerspectiveCamera::OnMouseScrollEvent));
      dispatcher.Dispatch<MouseMoveEvent>(KRYS_BIND_EVENT_FN(PerspectiveCamera::OnMouseMoveEvent));
    }

  private:
    void CalculateProjectionMatrix() noexcept
    {
      m_Projection = glm::perspective(glm::radians(m_FovAngle), m_AspectRatio, m_ZNear, m_ZFar);
    }

    void CalculateViewMatrix() noexcept
    {
      m_View = glm::lookAt(m_CameraPosition, m_CameraPosition + m_CameraFront, m_CameraUp);
    }

    void CalculateCameraVectors() noexcept
    {
      Vec3 front = Vec3(0.0f);
      front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
      front.y = sin(glm::radians(m_Pitch));
      front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));

      m_CameraFront = glm::normalize(front);
    }

    bool OnMouseScrollEvent(MouseScrollEvent &event) noexcept
    {
      KRYS_LOG("X: %d, Y: %d, Z: %d", event.X, event.Y, event.DeltaZ);

      m_FovAngle += static_cast<float>(event.DeltaZ);
      m_FovAngle = Clamp(m_FovAngle, 1.0f, 45.0f);

      CalculateProjectionMatrix();
      CalculateViewProjectionMatrix();

      return true;
    }

    bool OnMouseButtonPressedEvent(MouseButtonPressedEvent &event)
    {
      if (event.Button == MouseButton::Left)
      {
        m_MoveCamera = true;
        m_LastMousePosition = {event.X, event.Y};
        return true;
      }

      return false;
    }

    bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent &event)
    {
      if (event.Button == MouseButton::Left)
      {
        m_MoveCamera = false;
        return true;
      }

      return false;
    }

    bool OnMouseMoveEvent(MouseMoveEvent &event) noexcept
    {
      if (!m_MoveCamera)
      {
        return false;
      }

      Vec2 position = Vec2(static_cast<float>(event.X), static_cast<float>(event.Y));

      float deltaX = position.x - m_LastMousePosition.x;
      float deltaY = m_LastMousePosition.y - position.y;
      KRYS_LOG("Delta X: %f, Delta Y: %f", deltaX, deltaY);

      m_LastMousePosition = position;

      deltaX *= m_MovementSensitivity;
      deltaY *= m_MovementSensitivity;

      m_Yaw += deltaX;
      m_Pitch += deltaY;

      m_Pitch = Clamp(m_Pitch, -89.0f, 89.0f);

      CalculateCameraVectors();
      CalculateProjectionMatrix();
      CalculateViewProjectionMatrix();

      return true;
    }
  };
}