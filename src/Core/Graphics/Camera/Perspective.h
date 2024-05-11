#pragma once

#include "Maths/Maths.h"
#include "Misc/Time.h"

namespace Krys
{
  class PerspectiveCamera
  {
  private:
    Vec3 m_CameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
    Vec3 m_CameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    Vec3 m_CameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    float m_CameraSpeed;

  public:
    PerspectiveCamera(Vec3 cameraPosition, Vec3 cameraFront, Vec3 cameraUp)
        : m_CameraPosition(cameraPosition), m_CameraFront(cameraFront), m_CameraUp(cameraUp), m_CameraSpeed(5.0f) {}

    void OnUpdate()
    {
    }
  };
}