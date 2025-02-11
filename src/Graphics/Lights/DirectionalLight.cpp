#include "Graphics/Lights/DirectionalLight.hpp"

namespace Krys::Gfx
{
  DirectionalLight::DirectionalLight(LightHandle handle, const Colour &intensity,
                                     const Vec3 &direction) noexcept
      : Light(handle, LightType::Directional, intensity), _direction(direction),
        _attenuation(Vec3 {1.0f, 0.09f, 0.032f})
  {
  }

  DirectionalLight::DirectionalLight(LightHandle handle, const Vec3 &direction) noexcept
      : Light(handle, LightType::Directional), _direction(direction), _attenuation(Vec3 {1.0f, 0.09f, 0.032f})
  {
  }

  void DirectionalLight::SetDirection(const Vec3 &direction) noexcept
  {
    _direction = direction;
    _dirty = true;
  }

  const Vec3 &DirectionalLight::GetDirection() const noexcept
  {
    return _direction;
  }

  void DirectionalLight::SetAttenuation(const Vec3 &attenuation) noexcept
  {
    _attenuation = attenuation;
    _dirty = true;
  }

  const Vec3 &DirectionalLight::GetAttenuation() const noexcept
  {
    return _attenuation;
  }

  LightData DirectionalLight::GetData() const noexcept
  {
    LightData data {};
    data.Intensity = GetIntensityData();
    data.Direction = GetDirection();
    data.Attenuation = GetAttenuation();
    data.Type = GetType();
    data.Position = Vec3 {0.0f}; // Directional lights have no position.
    return data;
  }
}