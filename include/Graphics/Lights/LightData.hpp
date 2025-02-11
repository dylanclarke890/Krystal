#pragma once

#include "MTL/Vectors/Vec3.hpp"
#include "Graphics/Lights/LightType.hpp"

namespace Krys::Gfx
{
  struct LightData
  {
    Vec3 Intensity;
    float Padding0{0.0f};
    Vec3 Position;
    float Padding1 {0.0f};
    Vec3 Direction;
    float Padding2{0.0f};
    LightType Type;
    float Padding3[3]{0.0f};
  };
}