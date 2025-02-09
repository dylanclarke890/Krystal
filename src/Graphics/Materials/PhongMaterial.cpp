#include "Graphics/Materials/PhongMaterial.hpp"

namespace Krys::Gfx
{
  PhongMaterial::PhongMaterial(MaterialHandle handle, ProgramHandle program) noexcept
      : Material(handle, program, MaterialType::Phong), _ambientTexture(), _diffuseTexture(),
        _specularTexture(), _shininess(0.0f)
  {
  }

  PhongMaterial::PhongMaterial(MaterialHandle handle, ProgramHandle program,
                               TextureHandle ambientTexture) noexcept
      : Material(handle, program, MaterialType::Phong), _ambientTexture(ambientTexture), _diffuseTexture(),
        _specularTexture(), _shininess(0.0f)
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