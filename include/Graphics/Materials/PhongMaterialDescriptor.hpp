#pragma once

#include "Base/Types.hpp"
#include "Graphics/Colour.hpp"

namespace Krys::Gfx
{
  struct PhongMaterialDescriptor
  {
    constexpr PhongMaterialDescriptor() noexcept = default;

    constexpr PhongMaterialDescriptor(const Colour &ambient, const Colour &diffuse, const Colour &specular,
                            float shininess) noexcept
        : Ambient(ambient), Diffuse(diffuse), Specular(specular), Shininess(shininess)
    {
    }

    constexpr PhongMaterialDescriptor(const string &ambientMap, const string &diffuseMap,
                                      const string &specularMap, float shininess) noexcept
        : AmbientMap(ambientMap), DiffuseMap(diffuseMap), SpecularMap(specularMap), Shininess(shininess)
    {
    }

    Colour Ambient;
    Colour Diffuse;
    Colour Specular;
    Colour Emissive;

    string AmbientMap;
    string DiffuseMap;
    string SpecularMap;
    string EmissiveMap;

    float Shininess {32};

    string NormalMap;
  };
}