#pragma once

#include "Krystal/Core/TimeStep.h"

#include "Krystal/Events/ApplicationEvent.h"
#include "Krystal/Events/MouseEvent.h"

#include "Krystal/Renderer/OrthographicCamera.h"

namespace Krys
{
  struct OrthographicCameraBounds
  {
    float Left, Right;
    float Top, Bottom;

    inline float GetWidth() { return Right - Left; }
    inline float GetHeight() { return Top - Bottom; }
  };

  class OrthographicCameraController
  {
  private:
    float m_AspectRatio, m_ZoomLevel;
    OrthographicCameraBounds m_Bounds;
    OrthographicCamera m_Camera;
    glm::vec3 m_CameraPosition;

    bool m_CanRotate;
    // In degrees, anti-clockwise.
    float m_CameraRotation;
    float m_CameraTranslationSpeed, m_CameraRotationSpeed;

  public:
    OrthographicCameraController(float aspectRatio, bool canRotate = false);

    void OnUpdate(TimeStep ts);
    void OnEvent(Event& e);

    OrthographicCamera& GetCamera() { return m_Camera; }
    const OrthographicCamera& GetCamera() const { return m_Camera; }

    float GetZoomLevel() { return m_ZoomLevel; }
    void SetZoomLevel(float level) { m_ZoomLevel = level; }

    const OrthographicCameraBounds& GetBounds() { return m_Bounds; }
  private:
    bool OnMouseScrolled(MouseScrolledEvent& e);
    bool OnWindowResized(WindowResizeEvent& e);
  };
}
