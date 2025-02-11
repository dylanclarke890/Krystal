#include "Graphics/Lights/PointLight.hpp"
#include "Graphics/Colours.hpp"

namespace Krys::Gfx
{
  PointLight::PointLight(LightHandle handle, const Colour &intensity, const Vec3 &position) noexcept
      : Light(handle, LightType::Point, intensity), _position(position),
        _attenuation(Vec3 {1.0f, 0.09f, 0.032f})

  {
  }

  PointLight::PointLight(LightHandle handle, const Vec3 &position) noexcept
      : Light(handle, LightType::Point), _position(position), _attenuation(Vec3 {1.0f, 0.09f, 0.032f})
  {
  }

  const Vec3 &PointLight::GetPosition() const noexcept
  {
    return _position;
  }

  void PointLight::SetPosition(const Vec3 &position) noexcept
  {
    _position = position;
    _dirty = true;
  }

  void PointLight::SetAttenuation(const Vec3 &attenuation) noexcept
  {
    _attenuation = attenuation;
    _dirty = true;
  }

  const Vec3 &PointLight::GetAttenuation() const noexcept
  {
    return _attenuation;
  }

  LightData PointLight::GetData() const noexcept
  {
    LightData data;
    data.Position = GetPosition();
    data.Intensity = GetIntensityData();
    data.Attenuation = GetAttenuation();
    data.Type = GetType();
    data.Direction = Vec3 {0.0f}; // Point lights have no direction.
    return data;
  }
}