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

    PhongMaterial(MaterialHandle handle, ProgramHandle program, const Vec3 &ambientColour) noexcept;
    PhongMaterial(MaterialHandle handle, ProgramHandle program, TextureHandle ambientTexture) noexcept;

    ~PhongMaterial() noexcept override = default;

    void SetAmbientTexture(TextureHandle texture) noexcept;

    NO_DISCARD TextureHandle GetAmbientTexture() const noexcept;

    void SetAmbientColour(const Vec3 &colour) noexcept;

    void SetAmbientColour(const Colour &colour) noexcept;

    NO_DISCARD const Vec3 &GetAmbientColour() const noexcept;

    void SetDiffuseTexture(TextureHandle texture) noexcept;

    NO_DISCARD TextureHandle GetDiffuseTexture() const noexcept;

    void SetDiffuseColour(const Vec3 &colour) noexcept;

    void SetDiffuseColour(const Colour &colour) noexcept;

    NO_DISCARD const Vec3 &GetDiffuseColour() const noexcept;

    void SetSpecularTexture(TextureHandle texture) noexcept;

    NO_DISCARD TextureHandle GetSpecularTexture() const noexcept;

    void SetSpecularColour(const Vec3 &colour) noexcept;

    void SetSpecularColour(const Colour &colour) noexcept;

    NO_DISCARD const Vec3 &GetSpecularColour() const noexcept;

    void SetShininess(float shininess) noexcept;

    NO_DISCARD float GetShininess() const noexcept;

    NO_DISCARD PhongMaterialData GetBufferData() const noexcept;

  protected:
    TextureHandle _ambientTexture, _diffuseTexture, _specularTexture;
    Vec3 _ambientColour, _diffuseColour, _specularColour;
    float _shininess;
  };
}