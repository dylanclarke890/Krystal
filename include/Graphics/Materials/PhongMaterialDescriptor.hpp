#pragma once

#include "Graphics/Colour.hpp"

namespace Krys::Gfx
{
  struct PhongMaterialDescriptor
  {
    Colour Ambient;
    Colour Diffuse;
    Colour Specular;
    float Shininess {32};
  };
}