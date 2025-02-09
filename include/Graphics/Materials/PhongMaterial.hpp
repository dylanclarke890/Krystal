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
    int AmbientTexture;
    int DiffuseTexture;
    int SpecularTexture;
    int EmissionTexture;
    float Shininess{32};
    float Padding[3];
  };

  class PhongMaterial : public Material
  {
  public:
    PhongMaterial(MaterialHandle handle, ProgramHandle program) noexcept;

    PhongMaterial(MaterialHandle handle, ProgramHandle program, TextureHandle ambientTexture) noexcept;

    PhongMaterial(MaterialHandle handle, ProgramHandle program, TextureHandle ambientTexture,
                  TextureHandle diffuseTexture, TextureHandle specularTexture, float shininess) noexcept;

    ~PhongMaterial() noexcept override = default;

    void SetAmbientTexture(TextureHandle texture) noexcept;

    NO_DISCARD TextureHandle GetAmbientTexture() const noexcept;

    void SetDiffuseTexture(TextureHandle texture) noexcept;

    NO_DISCARD TextureHandle GetDiffuseTexture() const noexcept;

    void SetSpecularTexture(TextureHandle texture) noexcept;

    NO_DISCARD TextureHandle GetSpecularTexture() const noexcept;

    void SetEmissionTexture(TextureHandle texture) noexcept;

    NO_DISCARD TextureHandle GetEmissionTexture() const noexcept;

    void SetShininess(float shininess) noexcept;

    NO_DISCARD float GetShininess() const noexcept;

  protected:
    TextureHandle _ambientTexture, _diffuseTexture, _specularTexture, _emissionTexture;
    float _shininess;
  };
}