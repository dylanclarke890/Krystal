#pragma once

#include "Graphics/Camera/Camera.h"
#include "Input/Input.h"
#include "Events/MouseEvents.h"
#include "Misc/Controller.h"
#include "Maths/Vector.h"
#include "Maths/BoundingBox.h"

namespace Krys::Graphics
{
  using namespace Krys::Maths;

  // TODO: we need to handle perspective division if we use this camera with our current shaders (is this right? I really don't know)
  class OrthographicCamera : public Camera
  {
    friend class OrthographicCameraController;

  private:
    float _rotation;
    BoundingBox<float> _bounds;

  public:
    OrthographicCamera(int width, int height, float zNear = 0.0f, float zFar = 100.0f) noexcept
        : Camera(Vec3(0.0f), zNear, zFar), _rotation(0.0f), _bounds({})
    {
      _bounds.Right = static_cast<float>(width);
      _bounds.Bottom = static_cast<float>(height);

      CalculateViewMatrix();
      CalculateProjectionMatrix();
      CalculateViewProjectionMatrix();
    }

    OrthographicCamera(const BoundingBox<float> &bounds, float zNear, float zFar) noexcept
        : Camera(Vec3(0.0f), zNear, zFar), _rotation(0.0f), _bounds(bounds)
    {
      CalculateViewMatrix();
      CalculateProjectionMatrix();
      CalculateViewProjectionMatrix();
    }

    void SetProjection(const BoundingBox<float> &bounds, float zNear, float zFar) noexcept
    {
      _bounds = bounds;
      CalculateProjectionMatrix();
      CalculateViewProjectionMatrix();
    }

    void SetRotation(float rotation) noexcept
    {
      _rotation = rotation;
      CalculateViewMatrix();
      CalculateViewProjectionMatrix();
    }

    float GetRotation() const noexcept
    {
      return _rotation;
    }

  protected:
    void CalculateProjectionMatrix() noexcept override
    {
      _projection = glm::ortho(_bounds.Left, _bounds.Right, _bounds.Bottom, _bounds.Top, _near, _far);
    }

    void CalculateViewMatrix() noexcept override
    {
      Mat4 view = glm::translate(MAT4_I, _position) * glm::rotate(MAT4_I, glm::radians(_rotation), ROTATE_AXIS_Z);
      _view = glm::inverse(view);
    }
  };

  class OrthographicCameraController : public Controller
  {

  private:
    Ref<OrthographicCamera> _camera;
    Vec2 _lastMousePosition;
    bool _isLeftMouseButtonPressed;
    float _movementSensitivity;
    float _movementSpeed, _rotationSpeed;

  public:
    OrthographicCameraController(Ref<OrthographicCamera> camera) noexcept
        : _camera(camera), _lastMousePosition(0.0f),
          _isLeftMouseButtonPressed(false), _movementSensitivity(1.0f),
          _movementSpeed(100.0f), _rotationSpeed(30.0f) {}

    void OnUpdate(float dt) noexcept override
    {
      auto &cam = *_camera;

      float rotationSpeed = _rotationSpeed * dt;
      bool recalcView = false;
      if (Input::IsKeyPressed(KeyCode::Q))
      {
        cam._rotation -= rotationSpeed;
        recalcView = true;
      }

      if (Input::IsKeyPressed(KeyCode::E))
      {
        cam._rotation += rotationSpeed;
        recalcView = true;
      }

      float movementSpeed = _movementSpeed * dt;
      bool recalcProjection = false;
      if (Input::IsKeyPressed(KeyCode::W))
      {
        cam._bounds.Top -= movementSpeed;
        cam._bounds.Bottom -= movementSpeed;
        recalcProjection = true;
      }
      if (Input::IsKeyPressed(KeyCode::S))
      {
        cam._bounds.Top += movementSpeed;
        cam._bounds.Bottom += movementSpeed;
        recalcProjection = true;
      }
      if (Input::IsKeyPressed(KeyCode::D))
      {
        cam._bounds.Right += movementSpeed;
        cam._bounds.Left += movementSpeed;
        recalcProjection = true;
      }
      if (Input::IsKeyPressed(KeyCode::A))
      {
        cam._bounds.Right -= movementSpeed;
        cam._bounds.Left -= movementSpeed;
        recalcProjection = true;
      }

      if (recalcView)
        cam.CalculateViewMatrix();

      if (recalcProjection)
        cam.CalculateProjectionMatrix();

      if (recalcView || recalcProjection)
        cam.CalculateViewProjectionMatrix();
    }

    void OnEvent(Event &event) noexcept override
    {
      EventDispatcher dispatcher(event);
      dispatcher.Dispatch<MouseButtonPressedEvent>(KRYS_BIND_EVENT_FN(OrthographicCameraController::OnMouseButtonPressedEvent));
      dispatcher.Dispatch<MouseButtonReleasedEvent>(KRYS_BIND_EVENT_FN(OrthographicCameraController::OnMouseButtonReleasedEvent));
      dispatcher.Dispatch<MouseMoveEvent>(KRYS_BIND_EVENT_FN(OrthographicCameraController::OnMouseMoveEvent));
    }

  private:
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
      cam._bounds.Left -= deltaX;
      cam._bounds.Right -= deltaX;
      cam._bounds.Top += deltaY;
      cam._bounds.Bottom += deltaY;

      _lastMousePosition = position;

      cam.CalculateViewMatrix();
      cam.CalculateProjectionMatrix();
      cam.CalculateViewProjectionMatrix();

      return true;
    }
  };
}