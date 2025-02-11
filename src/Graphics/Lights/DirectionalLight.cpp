#include "Graphics/Lights/DirectionalLight.hpp"

namespace Krys::Gfx
{
  DirectionalLight::DirectionalLight(LightHandle handle, const Colour &intensity,
                                     const Vec3 &direction) noexcept
      : Light(handle, LightType::Directional, intensity), _direction(direction)
  {
  }

  DirectionalLight::DirectionalLight(LightHandle handle, const Vec3 &direction) noexcept
      : Light(handle, LightType::Directional), _direction(direction)
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

  LightData DirectionalLight::GetData() const noexcept
  {
    LightData data {};
    data.Intensity = GetIntensityData();
    data.Direction = GetDirection();
    data.Type = GetType();
    data.Position = Vec3 {0.0f}; // Directional lights have no position.
    return data;
  }
}