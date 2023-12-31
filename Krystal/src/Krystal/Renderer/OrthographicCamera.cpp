#include "krys-pch.h"
#include "Krystal/Renderer/OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Krys
{
  OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
    : m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)),
      m_ViewMatrix(1.0f),
      m_Position(0.0f),
      m_Rotation(0.0f)
  {
    RecalculateViewProjectionMatrix();
  }

  void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
  {
    m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
    RecalculateViewProjectionMatrix();
  }

  void OrthographicCamera::SetRotation(float rotation)
  {
    m_Rotation = rotation;
    RecalculateViewMatrix();
  }

  void OrthographicCamera::SetPosition(const glm::vec3& position)
  {
    m_Position = position;
    RecalculateViewMatrix();
  }

  void OrthographicCamera::RecalculateViewMatrix()
  {
    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * rotation;

    m_ViewMatrix = glm::inverse(transform);
    RecalculateViewProjectionMatrix();
  }

  inline void OrthographicCamera::RecalculateViewProjectionMatrix()
  {
    m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix; // Order matters here.
  }
}