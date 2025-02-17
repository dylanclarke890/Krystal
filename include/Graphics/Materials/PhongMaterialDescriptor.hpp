#pragma once

#include "Graphics/Colour.hpp"
#include "Graphics/Handles.hpp"

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

    constexpr PhongMaterialDescriptor(TextureHandle ambientMap, TextureHandle diffuseMap,
                                      TextureHandle specularMap, float shininess) noexcept
        : AmbientMap(ambientMap), DiffuseMap(diffuseMap), SpecularMap(specularMap), Shininess(shininess)
    {
    }

    Colour Ambient;
    Colour Diffuse;
    Colour Specular;
    Colour Emissive;

    TextureHandle AmbientMap;
    TextureHandle DiffuseMap;
    TextureHandle SpecularMap;
    TextureHandle EmissiveMap;

    float Shininess {32};

    TextureHandle NormalMap;
  };
}