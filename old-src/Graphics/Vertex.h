#pragma once

#include "Maths/Vector.h"

namespace Krys::Gfx
{
  using namespace Krys::Maths;

  struct Vertex
  {
    Vec3 Position;
    Vec3 Normal;
    Vec4 Color;
    Vec2 TextureCoords;
    Vec3 Tangent;
  };
}