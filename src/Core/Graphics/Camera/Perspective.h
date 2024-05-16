#pragma once

#include "Graphics/Camera/Camera.h"
#include "Input/Input.h"
#include "Events/MouseEvents.h"
#include "Misc/Controller.h"

namespace Krys
{
  class PerspectiveCamera : public Camera
  {
    friend class PerspectiveCameraController;

  private:
    Vec3 Front, Up;
    float Yaw, Pitch;
    float FovAngle, AspectRatio;

  public:
    PerspectiveCamera(int width, int height, float fovAngle,
                      float zNear = 0.1f, float zFar = 100.0f) noexcept
        : Camera(Vec3(0.0f, 0.0f, 1.0f), zNear, zFar),
          Front(Vec3(0.0f)), Up(Vec3(0.0f, 1.0f, 0.0f)),
          Yaw(0), Pitch(0),
          FovAngle(fovAngle), AspectRatio(static_cast<float>(width) / static_cast<float>(height))
    {
      CalculateCameraVectors();
      CalculateViewMatrix();
      CalculateProjectionMatrix();
      CalculateViewProjectionMatrix();
    }

    PerspectiveCamera(float aspectRatio, float fovAngle,
                      float zNear = 0.1f, float zFar = 100.0f) noexcept
        : Camera(Vec3(0.0f, 0.0f, 1.0f), zNear, zFar),
          Front(Vec3(0.0f)), Up(Vec3(0.0f, 1.0f, 0.0f)),
          Yaw(0), Pitch(0),
          FovAngle(fovAngle), AspectRatio(aspectRatio)
    {
      CalculateCameraVectors();
      CalculateViewMatrix();
      CalculateProjectionMatrix();
      CalculateViewProjectionMatrix();
    }

    void SetPitch(float pitchAngle) noexcept
    {
      Pitch = pitchAngle;
      CalculateCameraVectors();
      CalculateViewMatrix();
      CalculateViewProjectionMatrix();
    }

    void SetYaw(float yawAngle) noexcept
    {
      Yaw = yawAngle;
      CalculateCameraVectors();
      CalculateViewMatrix();
      CalculateViewProjectionMatrix();
    }

  private:
#pragma region Calcs

    void CalculateCameraVectors() noexcept
    {
      Vec3 front;
      front.x = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
      front.y = sin(glm::radians(Pitch));
      front.z = -cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));

      Front = glm::normalize(front);
    }

    void CalculateViewMatrix() noexcept
    {
      View = glm::lookAt(Position, Position + Front, Up);
    }

    void CalculateProjectionMatrix() noexcept
    {
      Projection = glm::perspective(glm::radians(FovAngle), AspectRatio, ZNear, ZFar);
    }

#pragma endregion Calcs
  };

  class PerspectiveCameraController : public Controller
  {
  private:
    Ref<PerspectiveCamera> Camera;
    Vec2 LastMousePosition;
    bool IsLeftMouseButtonPressed;
    float MovementSensitivity;
    float Speed;

  public:
    PerspectiveCameraController(Ref<PerspectiveCamera> camera) noexcept
        : Camera(camera), LastMousePosition(0.0f), IsLeftMouseButtonPressed(false),
          MovementSensitivity(0.1f), Speed(5.0f) {}

    void OnUpdate(float dt) noexcept
    {
      bool recalc = false;
      float speed = Speed * dt;
      auto &cam = *Camera;

      if (Input::IsKeyPressed(KeyCode::W))
      {
        cam.Position += speed * cam.Front;
        recalc = true;
      }

      if (Input::IsKeyPressed(KeyCode::S))
      {
        recalc = true;
        cam.Position -= speed * cam.Front;
      }

      if (Input::IsKeyPressed(KeyCode::D))
      {
        recalc = true;
        cam.Position += glm::normalize(glm::cross(cam.Front, cam.Up)) * speed;
      }

      if (Input::IsKeyPressed(KeyCode::A))
      {
        recalc = true;
        cam.Position -= glm::normalize(glm::cross(cam.Front, cam.Up)) * speed;
      }

      if (recalc)
      {
        cam.CalculateViewMatrix();
        cam.CalculateViewProjectionMatrix();
      }
    }

    void OnEvent(Event &event) noexcept
    {
      EventDispatcher dispatcher(event);
      dispatcher.Dispatch<MouseButtonPressedEvent>(KRYS_BIND_EVENT_FN(PerspectiveCameraController::OnMouseButtonPressedEvent));
      dispatcher.Dispatch<MouseButtonReleasedEvent>(KRYS_BIND_EVENT_FN(PerspectiveCameraController::OnMouseButtonReleasedEvent));
      dispatcher.Dispatch<MouseScrollEvent>(KRYS_BIND_EVENT_FN(PerspectiveCameraController::OnMouseScrollEvent));
      dispatcher.Dispatch<MouseMoveEvent>(KRYS_BIND_EVENT_FN(PerspectiveCameraController::OnMouseMoveEvent));
    }

    void SetSpeed(float speed) noexcept
    {
      Speed = speed;
    }

  private:
#pragma region Events

    bool OnMouseButtonPressedEvent(MouseButtonPressedEvent &event)
    {
      if (event.Button == MouseButton::Left)
      {
        IsLeftMouseButtonPressed = true;
        LastMousePosition = {event.X, event.Y};
        return true;
      }
      return false;
    }

    bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent &event)
    {
      if (event.Button == MouseButton::Left)
      {
        IsLeftMouseButtonPressed = false;
      }

      return false;
    }

    bool OnMouseScrollEvent(MouseScrollEvent &event) noexcept
    {
      auto &cam = *Camera;
      cam.FovAngle -= static_cast<float>(event.DeltaZ);
      cam.FovAngle = Clamp(cam.FovAngle, 1.0f, 45.0f);

      cam.CalculateProjectionMatrix();
      cam.CalculateViewProjectionMatrix();

      return true;
    }

    bool OnMouseMoveEvent(MouseMoveEvent &event) noexcept
    {
      if (!IsLeftMouseButtonPressed)
        return false;

      Vec2 position = Vec2(static_cast<float>(event.X), static_cast<float>(event.Y));

      float deltaX = position.x - LastMousePosition.x;
      float deltaY = LastMousePosition.y - position.y;
      deltaX *= MovementSensitivity;
      deltaY *= MovementSensitivity;

      auto &cam = *Camera;
      cam.Yaw += deltaX;
      cam.Pitch += deltaY;

      cam.Pitch = Clamp(cam.Pitch, -89.0f, 89.0f);
      LastMousePosition = position;

      cam.CalculateCameraVectors();
      cam.CalculateViewMatrix();
      cam.CalculateProjectionMatrix();
      cam.CalculateViewProjectionMatrix();

      return true;
    }

#pragma endregion Events
  };
}