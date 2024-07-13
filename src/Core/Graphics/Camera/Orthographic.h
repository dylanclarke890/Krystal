#pragma once

#include "Graphics/Camera/Camera.h"
#include "Input/Input.h"
#include "Events/MouseEvents.h"
#include "Misc/Controller.h"

namespace Krys
{
  // TODO: we need to handle perspective division if we use this camera with our current shaders (is this right? I really don't know)
  class OrthographicCamera : public Camera
  {
    friend class OrthographicCameraController;

  private:
    float Rotation;
    RectBounds Bounds;

  public:
    OrthographicCamera(int width, int height, float zNear = 0.0f, float zFar = 100.0f) noexcept
        : Camera(Vec3(0.0f), zNear, zFar), Rotation(0.0f), Bounds({})
    {
      Bounds.Right = static_cast<float>(width);
      Bounds.Bottom = static_cast<float>(height);

      CalculateViewMatrix();
      CalculateProjectionMatrix();
      CalculateViewProjectionMatrix();
    }

    OrthographicCamera(const RectBounds &bounds, float zNear, float zFar) noexcept
        : Camera(Vec3(0.0f), zNear, zFar), Rotation(0.0f), Bounds(bounds)
    {
      CalculateViewMatrix();
      CalculateProjectionMatrix();
      CalculateViewProjectionMatrix();
    }

    void SetProjection(const RectBounds &bounds, float zNear, float zFar) noexcept
    {
      Bounds = bounds;
      CalculateProjectionMatrix();
      CalculateViewProjectionMatrix();
    }

    void SetRotation(float rotation) noexcept
    {
      Rotation = rotation;
      CalculateViewMatrix();
      CalculateViewProjectionMatrix();
    }

    float GetRotation() const noexcept
    {
      return Rotation;
    }

  protected:
    void CalculateProjectionMatrix() noexcept override
    {
      Projection = glm::ortho(Bounds.Left, Bounds.Right, Bounds.Bottom, Bounds.Top, ZNear, ZFar);
    }

    void CalculateViewMatrix() noexcept override
    {
      Mat4 view = glm::translate(MAT4_I, Position) * glm::rotate(MAT4_I, glm::radians(Rotation), ROTATE_AXIS_Z);
      View = glm::inverse(view);
    }
  };

  class OrthographicCameraController : public Controller
  {

  private:
    Ref<OrthographicCamera> Camera;
    Vec2 LastMousePosition;
    bool IsLeftMouseButtonPressed;
    float MovementSensitivity;
    float MovementSpeed, RotationSpeed;

  public:
    OrthographicCameraController(Ref<OrthographicCamera> camera) noexcept
        : Camera(camera), LastMousePosition(0.0f),
          IsLeftMouseButtonPressed(false), MovementSensitivity(1.0f),
          MovementSpeed(100.0f), RotationSpeed(30.0f) {}

    void OnUpdate(float dt) noexcept override
    {
      auto &cam = *Camera;

      float rotationSpeed = RotationSpeed * dt;
      bool recalcView = false;
      if (Input::IsKeyPressed(KeyCode::Q))
      {
        cam.Rotation -= rotationSpeed;
        recalcView = true;
      }

      if (Input::IsKeyPressed(KeyCode::E))
      {
        cam.Rotation += rotationSpeed;
        recalcView = true;
      }

      float movementSpeed = MovementSpeed * dt;
      bool recalcProjection = false;
      if (Input::IsKeyPressed(KeyCode::W))
      {
        cam.Bounds.Top -= movementSpeed;
        cam.Bounds.Bottom -= movementSpeed;
        recalcProjection = true;
      }
      if (Input::IsKeyPressed(KeyCode::S))
      {
        cam.Bounds.Top += movementSpeed;
        cam.Bounds.Bottom += movementSpeed;
        recalcProjection = true;
      }
      if (Input::IsKeyPressed(KeyCode::D))
      {
        cam.Bounds.Right += movementSpeed;
        cam.Bounds.Left += movementSpeed;
        recalcProjection = true;
      }
      if (Input::IsKeyPressed(KeyCode::A))
      {
        cam.Bounds.Right -= movementSpeed;
        cam.Bounds.Left -= movementSpeed;
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
      cam.Bounds.Left -= deltaX;
      cam.Bounds.Right -= deltaX;
      cam.Bounds.Top += deltaY;
      cam.Bounds.Bottom += deltaY;

      LastMousePosition = position;

      cam.CalculateViewMatrix();
      cam.CalculateProjectionMatrix();
      cam.CalculateViewProjectionMatrix();

      return true;
    }
  };
}