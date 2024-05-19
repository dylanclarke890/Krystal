#pragma once

#include "Graphics/Texture2D.h"
#include "Maths/Maths.h"

namespace Krys
{
  class Material
  {
  public:
    Ref<Texture2D> Diffuse;
    Ref<Texture2D> Specular;
    Ref<Texture2D> Emission;
    Vec4 Tint;
    float Shininess;

    Material(Ref<Texture2D> texture, Ref<Texture2D> specularMap = nullptr, Ref<Texture2D> emissionMap = nullptr)
        : Diffuse(texture), Specular(specularMap), Emission(emissionMap), Tint(1.0f), Shininess(0.0f) {}
  };
}