#include "krys-pch.h"
#include "Krystal/Renderer/OrthographicCameraController.h"

#include "Krystal/Core/Input.h"
#include "Krystal/Core/KeyCodes.h"

namespace Krys
{
  OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool canRotate)
    : m_AspectRatio(aspectRatio), m_ZoomLevel(1.0f),
      m_Bounds({ -m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel }),
      m_Camera(m_Bounds.Left, m_Bounds.Right, m_Bounds.Bottom, m_Bounds.Top),
      m_CanRotate(canRotate), m_CameraRotation(0.0f), m_CameraPosition(0.0f),
      m_CameraRotationSpeed(5.0f), m_CameraTranslationSpeed(10.0f)
  {
  }
  
  void OrthographicCameraController::OnUpdate(TimeStep ts)
  {
    KRYS_PROFILE_FUNCTION();

    if (Input::IsKeyPressed(KeyCode::A))
    {
      m_CameraPosition.x -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
      m_CameraPosition.y -= sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
    }
    else if (Input::IsKeyPressed(KeyCode::D))
    {
      m_CameraPosition.x += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
      m_CameraPosition.y += sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
    }

    if (Input::IsKeyPressed(KeyCode::W))
    {
      m_CameraPosition.x += -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
      m_CameraPosition.y += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
    }
    else if (Input::IsKeyPressed(KeyCode::S))
    {
      m_CameraPosition.x -= -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
      m_CameraPosition.y -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
    }

    if (m_CanRotate)
    {
      if (Input::IsKeyPressed(KeyCode::Q))
        m_CameraRotation += m_CameraRotationSpeed * ts;
      else if (Input::IsKeyPressed(KeyCode::E))
        m_CameraRotation -= m_CameraRotationSpeed * ts;
      
      if (m_CameraRotation > 180.0f)
        m_CameraRotation -= 360.0f;
      else if (m_CameraRotation <= -180.0f)
        m_CameraRotation += 360.0f;

      m_Camera.SetRotation(m_CameraRotation);
    }

    m_Camera.SetPosition(m_CameraPosition);

    m_CameraTranslationSpeed = m_ZoomLevel;
  }
  
  void OrthographicCameraController::OnEvent(Event& e)
  {
    KRYS_PROFILE_FUNCTION();

    EventDispatcher dispatcher(e);

    dispatcher.Dispatch<MouseScrolledEvent>(KRYS_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
    dispatcher.Dispatch<WindowResizeEvent>(KRYS_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
  }
  
  bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
  {
    KRYS_PROFILE_FUNCTION();

    m_ZoomLevel -= e.GetYOffset() * 0.5f;
    m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
    m_Bounds = { -m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel };
    m_Camera.SetProjection(m_Bounds.Left, m_Bounds.Right, m_Bounds.Bottom, m_Bounds.Top);

    return false;
  }

  bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
  {
    KRYS_PROFILE_FUNCTION();

    m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
    m_Bounds = { -m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel };
    m_Camera.SetProjection(m_Bounds.Left, m_Bounds.Right, m_Bounds.Bottom, m_Bounds.Top);

    return false;
  }
}