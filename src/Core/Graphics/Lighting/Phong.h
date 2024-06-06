#pragma once

#include "Maths/Maths.h"

namespace Krys
{
  struct PhongDirectionalLight
  {
    Vec3 Ambient;
    Vec3 Diffuse;
    Vec3 Specular;

    bool Enabled;
    float Intensity;

    Vec3 Direction;
  };

  struct PhongPointLight
  {
    Vec3 Ambient;
    Vec3 Diffuse;
    Vec3 Specular;

    float Constant;
    float Linear;
    float Quadratic;

    bool Enabled;
    float Intensity;

    Vec3 Position;
  };

  struct PhongSpotLight
  {
    Vec3 Ambient;
    Vec3 Diffuse;
    Vec3 Specular;

    float Constant;
    float Linear;
    float Quadratic;

    bool Enabled;
    float Intensity;

    Vec3 Direction;
    Vec3 Position;

    float InnerCutoff;
    float OuterCutoff;
  };
}