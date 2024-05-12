#pragma once

#include "Graphics/Camera/Camera.h"
#include "Input/Input.h"
#include "Misc/Time.h"
#include "Events/MouseEvents.h"

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

    bool m_MoveCamera;
    Vec2 m_LastMousePosition;
    float m_MovementSensitivity;

  public:
    PerspectiveCamera(float fovAngle, float aspectRatio, float zNear, float zFar) noexcept
        : Camera(Vec3(0.0f), zNear, zFar),
          m_CameraFront(Vec3(0.0f, 0.0f, -1.0f)), m_CameraUp(Vec3(0.0f, 1.0f, 0.0f)),
          m_CameraSpeed(5.0f), m_Yaw(0), m_Pitch(0),
          m_FovAngle(fovAngle), m_AspectRatio(aspectRatio),
          m_MoveCamera(false), m_LastMousePosition(0.0f), m_MovementSensitivity(0.1f)
    {
      CalculateCameraVectors();
      CalculateViewMatrix();
      CalculateProjectionMatrix();
      CalculateViewProjectionMatrix();
    }

    void SetPitch(float pitchAngle) noexcept
    {
      m_Pitch = pitchAngle;
      CalculateCameraVectors();
      CalculateViewMatrix();
      CalculateViewProjectionMatrix();
    }

    void SetYaw(float yawAngle) noexcept
    {
      m_Yaw = yawAngle;
      CalculateCameraVectors();
      CalculateViewMatrix();
      CalculateViewProjectionMatrix();
    }

    void SetSpeed(float speed) noexcept
    {
      m_CameraSpeed = speed;
    }

    void OnUpdate(float dt) noexcept override
    {
      bool recalc = false;
      float speed = m_CameraSpeed * dt;

      if (Input::IsKeyPressed(KeyCode::W))
      {
        m_CameraPosition += speed * m_CameraFront;
        recalc = true;
      }

      if (Input::IsKeyPressed(KeyCode::S))
      {
        recalc = true;
        m_CameraPosition -= speed * m_CameraFront;
      }

      if (Input::IsKeyPressed(KeyCode::A))
      {
        recalc = true;
        m_CameraPosition -= glm::normalize(glm::cross(m_CameraFront, m_CameraUp)) * speed;
      }

      if (Input::IsKeyPressed(KeyCode::D))
      {
        recalc = true;
        m_CameraPosition += glm::normalize(glm::cross(m_CameraFront, m_CameraUp)) * speed;
      }

      if (recalc)
      {
        CalculateViewMatrix();
        CalculateViewProjectionMatrix();
      }
    }

    void OnEvent(Event &event) noexcept override
    {
      EventDispatcher dispatcher(event);
      dispatcher.Dispatch<MouseButtonPressedEvent>(KRYS_BIND_EVENT_FN(PerspectiveCamera::OnMouseButtonPressedEvent));
      dispatcher.Dispatch<MouseButtonReleasedEvent>(KRYS_BIND_EVENT_FN(PerspectiveCamera::OnMouseButtonReleasedEvent));
      dispatcher.Dispatch<MouseScrollEvent>(KRYS_BIND_EVENT_FN(PerspectiveCamera::OnMouseScrollEvent));
      dispatcher.Dispatch<MouseMoveEvent>(KRYS_BIND_EVENT_FN(PerspectiveCamera::OnMouseMoveEvent));
    }

  private:
#pragma region Calcs

    void CalculateCameraVectors() noexcept
    {
      Vec3 front;
      front.x = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
      front.y = sin(glm::radians(m_Pitch));
      front.z = -cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));

      m_CameraFront = glm::normalize(front);
    }

    void CalculateViewMatrix() noexcept
    {
      m_View = glm::lookAt(m_CameraPosition, m_CameraPosition + m_CameraFront, m_CameraUp);
    }

    void CalculateProjectionMatrix() noexcept
    {
      m_Projection = glm::perspective(glm::radians(m_FovAngle), m_AspectRatio, m_ZNear, m_ZFar);
    }

#pragma endregion Calcs

#pragma region Events

    bool OnMouseScrollEvent(MouseScrollEvent &event) noexcept
    {
      m_FovAngle -= static_cast<float>(event.DeltaZ);
      m_FovAngle = Clamp(m_FovAngle, 1.0f, 45.0f);

      CalculateProjectionMatrix();
      CalculateViewProjectionMatrix();

      return true;
    }

    bool OnMouseButtonPressedEvent(MouseButtonPressedEvent &event) noexcept
    {
      if (event.Button == MouseButton::Left)
      {
        m_MoveCamera = true;
        m_LastMousePosition = {event.X, event.Y};
        return true;
      }

      return false;
    }

    bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent &event) noexcept
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
        return false;

      Vec2 position = Vec2(static_cast<float>(event.X), static_cast<float>(event.Y));

      float deltaX = position.x - m_LastMousePosition.x;
      float deltaY = m_LastMousePosition.y - position.y;
      deltaX *= m_MovementSensitivity;
      deltaY *= m_MovementSensitivity;

      m_Yaw += deltaX;
      m_Pitch += deltaY;

      m_Pitch = Clamp(m_Pitch, -89.0f, 89.0f);
      m_LastMousePosition = position;

      CalculateCameraVectors();
      CalculateViewMatrix();
      CalculateProjectionMatrix();
      CalculateViewProjectionMatrix();

      return true;
    }

#pragma endregion Events
  };
}