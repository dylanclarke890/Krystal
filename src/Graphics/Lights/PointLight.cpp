#include "Graphics/Lights/PointLight.hpp"
#include "Graphics/Colours.hpp"

namespace Krys::Gfx
{
  PointLight::PointLight(LightHandle handle, const Colour &intensity, const Vec3 &position) noexcept
      : Light(handle, LightType::Point, intensity), _position(position)

  {
  }

  PointLight::PointLight(LightHandle handle, const Vec3 &position) noexcept
      : Light(handle, LightType::Point), _position(position)
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

  LightData PointLight::GetData() const noexcept
  {
    LightData data;
    data.Position = GetPosition();
    data.Intensity = GetIntensityData();
    data.Type = GetType();
    data.Direction = Vec3 {0.0f}; // Point lights have no direction.
    return data;
  }
}