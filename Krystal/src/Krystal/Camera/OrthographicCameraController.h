#pragma once

#include "OrthographicCamera.h"
#include "Krystal/Core/TimeStep.h"
#include "Krystal/Events/ApplicationEvent.h"
#include "Krystal/Events/MouseEvent.h"

namespace Krys
{
  class OrthographicCameraController
  {
  private:
    float m_AspectRatio, m_ZoomLevel;
    OrthographicCamera m_Camera;
    
    bool m_CanRotate;
    glm::vec3 m_CameraPosition;
    float m_CameraRotation;
    float m_CameraTranslationSpeed, m_CameraRotationSpeed;

  public:
    OrthographicCameraController(float aspectRatio, bool canRotate = false);

    void OnUpdate(TimeStep ts);
    void OnEvent(Event& e);

    OrthographicCamera& GetCamera() { return m_Camera; }
    const OrthographicCamera& GetCamera() const { return m_Camera; }

  private:
    bool OnMouseScrolled(MouseScrolledEvent& e);
    bool OnWindowResized(WindowResizeEvent& e);
  };
}
