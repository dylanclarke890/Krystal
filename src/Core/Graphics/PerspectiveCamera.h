#pragma once

#include "Maths/Maths.h"

namespace Krys
{
  class PerspectiveCamera
  {
  private:
  public:
    void A()
    {
      Vec3 cameraPos = Vec3(0.0f, 0.0f, 3.0f);
      Vec3 cameraTarget = Vec3(0.0f, 0.0f, 0.0f);
      Vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
      Vec3 up = Vec3(0.0f, 1.0f, 0.0f);
      Vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
      Vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
    }
  };
}