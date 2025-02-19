#pragma once

#include "Base/Attributes.hpp"
#include "Graphics/Colour.hpp"
#include "Graphics/Handles.hpp"
#include "Graphics/Materials/Material.hpp"
#include "MTL/Vectors/Vec3.hpp"
#include "MTL/Vectors/Vec4.hpp"

namespace Krys::Gfx
{
  struct PhongMaterialData
  {
    Vec3 Ambient;
    int AmbientTexture;
    Vec3 Diffuse;
    int DiffuseTexture;
    Vec3 Specular;
    int SpecularTexture;
    Vec3 Emission;
    int EmissionTexture;
    float Shininess;
    float Padding[3];
  };

  class PhongMaterial : public Material
  {
  public:
    PhongMaterial(MaterialHandle handle, ProgramHandle program) noexcept;

    ~PhongMaterial() noexcept override = default;

    void SetAmbientMap(TextureHandle map) noexcept;

    NO_DISCARD TextureHandle GetAmbientMap() const noexcept;

    void SetAmbient(const Colour &ambient) noexcept;

    NO_DISCARD Colour GetAmbient() const noexcept;

    void SetDiffuseMap(TextureHandle map) noexcept;

    NO_DISCARD TextureHandle GetDiffuseMap() const noexcept;

    void SetDiffuse(const Colour &diffuse) noexcept;

    NO_DISCARD Colour GetDiffuse() const noexcept;

    void SetSpecularMap(TextureHandle map) noexcept;

    NO_DISCARD TextureHandle GetSpecularMap() const noexcept;

    void SetSpecular(const Colour &specular) noexcept;

    NO_DISCARD Colour GetSpecular() const noexcept;

    void SetEmissionMap(TextureHandle map) noexcept;

    NO_DISCARD TextureHandle GetEmissionMap() const noexcept;

    void SetEmission(const Colour &emission) noexcept;

    NO_DISCARD Colour GetEmission() const noexcept;

    void SetShininess(float shininess) noexcept;

    NO_DISCARD float GetShininess() const noexcept;

  protected:
    TextureHandle _ambientMap, _diffuseMap, _specularMap, _emissionMap;
    Colour _ambient, _diffuse, _specular, _emission;
    float _shininess;
  };
}