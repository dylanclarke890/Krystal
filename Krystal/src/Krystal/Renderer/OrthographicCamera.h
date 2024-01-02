#pragma once

#include <glm/glm.hpp>

namespace Krys
{
  class OrthographicCamera
  {
  private:
    glm::mat4 m_ProjectionMatrix;
    glm::mat4 m_ViewMatrix;
    glm::mat4 m_ViewProjectionMatrix;

    glm::vec3 m_Position;
    float m_Rotation;
  public:
    OrthographicCamera(float left, float right, float bottom, float top);
    void SetProjection(float left, float right, float bottom, float top);

    void SetPosition(const glm::vec3& position);
    inline const glm::vec3& GetPosition() const { return m_Position; }

    void SetRotation(float rotation);
    inline float GetRotation() const { return m_Rotation; }

    inline const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
    inline const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
    inline const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

  private:
    void RecalculateViewMatrix();
    inline void RecalculateViewProjectionMatrix();
  };
}