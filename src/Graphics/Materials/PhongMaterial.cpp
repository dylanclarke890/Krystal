#include "Graphics/Materials/PhongMaterial.hpp"

namespace Krys::Gfx
{
  PhongMaterial::PhongMaterial(MaterialHandle handle, ProgramHandle program) noexcept
      : Material(handle, program, MaterialType::Phong), _ambientTexture(), _diffuseTexture(),
        _specularTexture(), _ambientColour(0.0f), _diffuseColour(0.0f), _specularColour(0.0f),
        _shininess(0.0f)
  {
  }

  PhongMaterial::PhongMaterial(MaterialHandle handle, ProgramHandle program,
                               const Vec3 &ambientColour) noexcept
      : Material(handle, program, MaterialType::Phong), _ambientTexture(), _diffuseTexture(),
        _specularTexture(), _ambientColour(ambientColour), _diffuseColour(0.0f), _specularColour(0.0f),
        _shininess(0.0f)
  {
  }

  PhongMaterial::PhongMaterial(MaterialHandle handle, ProgramHandle program,
                               TextureHandle ambientTexture) noexcept
      : Material(handle, program, MaterialType::Phong), _ambientTexture(ambientTexture), _diffuseTexture(),
        _specularTexture(), _ambientColour(0.0f), _diffuseColour(0.0f), _specularColour(0.0f),
        _shininess(0.0f)
  {
  }

  void PhongMaterial::SetAmbientTexture(TextureHandle texture) noexcept
  {
    _ambientTexture = texture;
    _isDirty = true;
  }

  TextureHandle PhongMaterial::GetAmbientTexture() const noexcept
  {
    return _ambientTexture;
  }

  void PhongMaterial::SetAmbientColour(const Vec3 &colour) noexcept
  {
    _ambientColour = colour;
    _isDirty = true;
  }

  void PhongMaterial::SetAmbientColour(const Colour &colour) noexcept
  {
    _ambientColour = Vec3(colour.r, colour.g, colour.b);
    _isDirty = true;
  }

  const Vec3 &PhongMaterial::GetAmbientColour() const noexcept
  {
    return _ambientColour;
  }

  void PhongMaterial::SetDiffuseTexture(TextureHandle texture) noexcept
  {
    _diffuseTexture = texture;
    _isDirty = true;
  }

  TextureHandle PhongMaterial::GetDiffuseTexture() const noexcept
  {
    return _diffuseTexture;
  }

  void PhongMaterial::SetDiffuseColour(const Vec3 &colour) noexcept
  {
    _diffuseColour = colour;
    _isDirty = true;
  }

  void PhongMaterial::SetDiffuseColour(const Colour &colour) noexcept
  {
    _diffuseColour = Vec3(colour.r, colour.g, colour.b);
    _isDirty = true;
  }

  const Vec3 &PhongMaterial::GetDiffuseColour() const noexcept
  {
    return _diffuseColour;
  }

  void PhongMaterial::SetSpecularTexture(TextureHandle texture) noexcept
  {
    _specularTexture = texture;
    _isDirty = true;
  }

  TextureHandle PhongMaterial::GetSpecularTexture() const noexcept
  {
    return _specularTexture;
  }

  void PhongMaterial::SetSpecularColour(const Vec3 &colour) noexcept
  {
    _specularColour = colour;
    _isDirty = true;
  }

  void PhongMaterial::SetSpecularColour(const Colour &colour) noexcept
  {
    _specularColour = Vec3(colour.r, colour.g, colour.b);
    _isDirty = true;
  }

  const Vec3 &PhongMaterial::GetSpecularColour() const noexcept
  {
    return _specularColour;
  }

  void PhongMaterial::SetShininess(float shininess) noexcept
  {
    _shininess = shininess;
    _isDirty = true;
  }

  float PhongMaterial::GetShininess() const noexcept
  {
    return _shininess;
  }
}