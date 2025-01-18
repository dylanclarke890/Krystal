#pragma once

#include "Graphics/Camera/Camera.h"
#include "Input/Input.h"
#include "Events/MouseEvents.h"
#include "Misc/Controller.h"
#include "Maths/Vector.h"
#include "Maths/Algorithms.h"

namespace Krys::Gfx
{
  using namespace Krys::Maths;

  class PerspectiveCamera : public Camera
  {
    friend class PerspectiveCameraController;

  private:
    Vec3 _front, _up;
    float _yaw, _pitch;
    float _fovAngle, _aspectRatio;

  public:
    PerspectiveCamera(int width, int height, float fovAngle,
                      float zNear = 0.1f, float zFar = 100.0f) noexcept
        : Camera(Vec3(0.0f, 0.0f, 1.0f), zNear, zFar),
          _front(Vec3(0.0f)), _up(Vec3(0.0f, 1.0f, 0.0f)),
          _yaw(0), _pitch(0),
          _fovAngle(fovAngle), _aspectRatio(static_cast<float>(width) / static_cast<float>(height))
    {
      CalculateCameraVectors();
      CalculateViewMatrix();
      CalculateProjectionMatrix();
      CalculateViewProjectionMatrix();
    }

    PerspectiveCamera(float aspectRatio, float fovAngle,
                      float zNear = 0.1f, float zFar = 100.0f) noexcept
        : Camera(Vec3(0.0f, 0.0f, 1.0f), zNear, zFar),
          _front(Vec3(0.0f)), _up(Vec3(0.0f, 1.0f, 0.0f)),
          _yaw(0), _pitch(0),
          _fovAngle(fovAngle), _aspectRatio(aspectRatio)
    {
      CalculateCameraVectors();
      CalculateViewMatrix();
      CalculateProjectionMatrix();
      CalculateViewProjectionMatrix();
    }

    Vec3 GetFront() const noexcept
    {
      return _front;
    }

    void SetPitch(float pitchAngle) noexcept
    {
      _pitch = pitchAngle;
      CalculateCameraVectors();
      CalculateViewMatrix();
      CalculateViewProjectionMatrix();
    }

    void SetYaw(float yawAngle) noexcept
    {
      _yaw = yawAngle;
      CalculateCameraVectors();
      CalculateViewMatrix();
      CalculateViewProjectionMatrix();
    }

  private:
#pragma region Calcs

    void CalculateCameraVectors() noexcept
    {
      Vec3 front;
      front.x = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
      front.y = sin(glm::radians(_pitch));
      front.z = -cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));

      _front = glm::normalize(front);
    }

    void CalculateViewMatrix() noexcept
    {
      _view = glm::lookAt(_position, _position + _front, _up);
    }

    void CalculateProjectionMatrix() noexcept
    {
      _projection = glm::perspective(glm::radians(_fovAngle), _aspectRatio, _near, _far);
    }

#pragma endregion Calcs
  };

  class PerspectiveCameraController : public Controller
  {
  private:
    Ref<PerspectiveCamera> _camera;
    Vec2 _lastMousePosition;
    bool _isLeftMouseButtonPressed;
    float _movementSensitivity;
    float _speed;

  public:
    PerspectiveCameraController(Ref<PerspectiveCamera> camera) noexcept
        : _camera(camera), _lastMousePosition(0.0f), _isLeftMouseButtonPressed(false),
          _movementSensitivity(0.1f), _speed(5.0f) {}

    void OnUpdate(float dt) noexcept
    {
      bool recalc = false;
      float speed = _speed * dt;
      auto &cam = *_camera;

      if (Input::IsKeyPressed(KeyCode::W))
      {
        cam._position += speed * cam._front;
        recalc = true;
      }

      if (Input::IsKeyPressed(KeyCode::S))
      {
        recalc = true;
        cam._position -= speed * cam._front;
      }

      if (Input::IsKeyPressed(KeyCode::D))
      {
        recalc = true;
        cam._position += glm::normalize(glm::cross(cam._front, cam._up)) * speed;
      }

      if (Input::IsKeyPressed(KeyCode::A))
      {
        recalc = true;
        cam._position -= glm::normalize(glm::cross(cam._front, cam._up)) * speed;
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
      _speed = speed;
    }

  private:
#pragma region Events

    bool OnMouseButtonPressedEvent(MouseButtonPressedEvent &event)
    {
      if (event.Button == MouseButton::Left)
      {
        _isLeftMouseButtonPressed = true;
        _lastMousePosition = {event.X, event.Y};
        return true;
      }
      return false;
    }

    bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent &event)
    {
      if (event.Button == MouseButton::Left)
      {
        _isLeftMouseButtonPressed = false;
      }

      return false;
    }

    bool OnMouseScrollEvent(MouseScrollEvent &event) noexcept
    {
      auto &cam = *_camera;
      cam._fovAngle -= static_cast<float>(event.DeltaZ);
      cam._fovAngle = Clamp(cam._fovAngle, 1.0f, 45.0f);

      cam.CalculateProjectionMatrix();
      cam.CalculateViewProjectionMatrix();

      return true;
    }

    bool OnMouseMoveEvent(MouseMoveEvent &event) noexcept
    {
      if (!_isLeftMouseButtonPressed)
        return false;

      Vec2 position = Vec2(static_cast<float>(event.X), static_cast<float>(event.Y));

      float deltaX = position.x - _lastMousePosition.x;
      float deltaY = _lastMousePosition.y - position.y;
      deltaX *= _movementSensitivity;
      deltaY *= _movementSensitivity;

      auto &cam = *_camera;
      cam._yaw += deltaX;
      cam._pitch += deltaY;

      cam._pitch = Clamp(cam._pitch, -89.0f, 89.0f);
      _lastMousePosition = position;

      cam.CalculateCameraVectors();
      cam.CalculateViewMatrix();
      cam.CalculateProjectionMatrix();
      cam.CalculateViewProjectionMatrix();

      return true;
    }

#pragma endregion Events
  };
}