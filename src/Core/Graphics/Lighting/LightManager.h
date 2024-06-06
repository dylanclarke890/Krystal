#pragma once

#include <unordered_map>

#include "Core.h"
#include "Phong.h"

namespace Krys
{
  class LightManager
  {
  private:
    std::unordered_map<string, PhongSpotLight> PhongSpotLights;
    std::unordered_map<string, PhongPointLight> PhongPointLights;
    std::unordered_map<string, PhongDirectionalLight> PhongDirectionalLights;

  public:
  };
}