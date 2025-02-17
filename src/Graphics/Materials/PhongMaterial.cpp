#include "Graphics/Materials/PhongMaterial.hpp"
#include "Graphics/Colours.hpp"

namespace Krys::Gfx
{
  PhongMaterial::PhongMaterial(MaterialHandle handle, ProgramHandle program) noexcept
      : Material(handle, program, MaterialType::Phong), _ambientMap(), _diffuseMap(), _specularMap(),
        _shininess(32.0f), _ambient(Colours::White), _diffuse(Colours::White), _specular(Colours::White),
        _emission(Colours::Black)
  {
  }

  void PhongMaterial::SetAmbientMap(TextureHandle map) noexcept
  {
    _ambientMap = map;
    _isDirty = true;
  }

  TextureHandle PhongMaterial::GetAmbientMap() const noexcept
  {
    return _ambientMap;
  }

  void PhongMaterial::SetAmbient(const Colour &ambient) noexcept
  {
    _ambient = ambient;
    _isDirty = true;
  }

  Colour PhongMaterial::GetAmbient() const noexcept
  {
    return _ambient;
  }

  void PhongMaterial::SetDiffuseMap(TextureHandle map) noexcept
  {
    _diffuseMap = map;
    _isDirty = true;
  }

  TextureHandle PhongMaterial::GetDiffuseMap() const noexcept
  {
    return _diffuseMap;
  }

  void PhongMaterial::SetDiffuse(const Colour &diffuse) noexcept
  {
    _diffuse = diffuse;
    _isDirty = true;
  }

  Colour PhongMaterial::GetDiffuse() const noexcept
  {
    return _diffuse;
  }

  void PhongMaterial::SetSpecularMap(TextureHandle map) noexcept
  {
    _specularMap = map;
    _isDirty = true;
  }

  TextureHandle PhongMaterial::GetSpecularMap() const noexcept
  {
    return _specularMap;
  }

  void PhongMaterial::SetSpecular(const Colour &specular) noexcept
  {
    _specular = specular;
    _isDirty = true;
  }

  Colour PhongMaterial::GetSpecular() const noexcept
  {
    return _specular;
  }

  void PhongMaterial::SetEmissionMap(TextureHandle map) noexcept
  {
    _emissionMap = map;
    _isDirty = true;
  }

  TextureHandle PhongMaterial::GetEmissionMap() const noexcept
  {
    return _emissionMap;
  }

  void PhongMaterial::SetEmission(const Colour &emission) noexcept
  {
    _emission = emission;
    _isDirty = true;
  }

  Colour PhongMaterial::GetEmission() const noexcept
  {
    return _emission;
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