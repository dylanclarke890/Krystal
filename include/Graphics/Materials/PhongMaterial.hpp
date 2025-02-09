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
    Vec3 AmbientColour;
    float Padding0{0};
    Vec3 DiffuseColour;
    float Padding1{0};
    Vec3 SpecularColour;
    float Shininess{32};

    int AmbientTexture;
    int DiffuseTexture;
    int SpecularTexture;
    int Padding2{0};
  };

  class PhongMaterial : public Material
  {
  public:
    PhongMaterial(MaterialHandle handle, ProgramHandle program) noexcept;

    PhongMaterial(MaterialHandle handle, ProgramHandle program, TextureHandle ambientTexture) noexcept;

    ~PhongMaterial() noexcept override = default;

    void SetAmbientTexture(TextureHandle texture) noexcept;

    NO_DISCARD TextureHandle GetAmbientTexture() const noexcept;

    void SetDiffuseTexture(TextureHandle texture) noexcept;

    NO_DISCARD TextureHandle GetDiffuseTexture() const noexcept;

    void SetSpecularTexture(TextureHandle texture) noexcept;

    NO_DISCARD TextureHandle GetSpecularTexture() const noexcept;

    void SetShininess(float shininess) noexcept;

    NO_DISCARD float GetShininess() const noexcept;

  protected:
    TextureHandle _ambientTexture, _diffuseTexture, _specularTexture;
    float _shininess;
  };
}