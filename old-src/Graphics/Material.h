#pragma once

#include "Types.h"
#include "Textures/Texture.h"
#include "Shaders/Shader.h"
#include "Maths/Vector.h"

namespace Krys::Gfx
{
  using namespace Krys::Maths;

  const uint32 MATERIAL_DIFFUSE_MAP_SET = 1;
  const uint32 MATERIAL_SPECULAR_MAP_SET = 1 << 1;
  const uint32 MATERIAL_EMISSION_MAP_SET = 1 << 2;
  const uint32 MATERIAL_NORMAL_MAP_SET = 1 << 3;
  const uint32 MATERIAL_DISPLACEMENT_MAP_SET = 1 << 4;

  struct Material
  {
    uint32 Id;
    Vec3 AmbientColor{1.0f}, DiffuseColor{1.0f}, SpecularColor{1.0f};
    Ref<Texture> DiffuseMap, SpecularMap, EmissionMap, NormalMap, DisplacementMap;
    Vec3 Tint = Vec3(1.0f);
    float Shininess = 32.0f;
    Ref<Shader> Shader;

    NO_DISCARD uint32 GetAvailableTextures() const noexcept
    {
      uint32 flags = 0;

      if (DiffuseMap)
        flags |= MATERIAL_DIFFUSE_MAP_SET;

      if (SpecularMap)
        flags |= MATERIAL_SPECULAR_MAP_SET;

      if (EmissionMap)
        flags |= MATERIAL_EMISSION_MAP_SET;

      if (NormalMap)
        flags |= MATERIAL_NORMAL_MAP_SET;

      if (DisplacementMap)
        flags |= MATERIAL_DISPLACEMENT_MAP_SET;

      return flags;
    }
  };
}