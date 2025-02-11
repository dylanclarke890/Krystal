#include "Graphics/Materials/PhongMaterial.hpp"

namespace Krys::Gfx
{
  PhongMaterial::PhongMaterial(MaterialHandle handle, ProgramHandle program) noexcept
      : Material(handle, program, MaterialType::Phong), _ambientTexture(), _diffuseTexture(),
        _specularTexture(), _shininess(32.0f)
  {
  }

  PhongMaterial::PhongMaterial(MaterialHandle handle, ProgramHandle program,
                               TextureHandle ambientTexture) noexcept
      : Material(handle, program, MaterialType::Phong), _ambientTexture(ambientTexture), _diffuseTexture(),
        _specularTexture(), _shininess(32.0f)
  {
  }

  PhongMaterial::PhongMaterial(MaterialHandle handle, ProgramHandle program, TextureHandle ambientTexture,
                               TextureHandle diffuseTexture, TextureHandle specularTexture,
                               float shininess) noexcept
      : Material(handle, program, MaterialType::Phong), _ambientTexture(ambientTexture),
        _diffuseTexture(diffuseTexture), _specularTexture(specularTexture), _shininess(shininess)
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

  void PhongMaterial::SetDiffuseTexture(TextureHandle texture) noexcept
  {
    _diffuseTexture = texture;
    _isDirty = true;
  }

  TextureHandle PhongMaterial::GetDiffuseTexture() const noexcept
  {
    return _diffuseTexture;
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

  void PhongMaterial::SetEmissionTexture(TextureHandle texture) noexcept
  {
    _emissionTexture = texture;
    _isDirty = true;
  }

  TextureHandle PhongMaterial::GetEmissionTexture() const noexcept
  {
    return _emissionTexture;
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