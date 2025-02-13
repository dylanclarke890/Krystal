#include "Graphics/Lights/SpotLight.hpp"

namespace Krys::Gfx
{
  SpotLight::SpotLight(LightHandle handle, const Colour &intensity, const Vec3 &position,
                       const Vec3 &direction, const Vec3 &attenuation, float innerCutoff,
                       float outerCutoff) noexcept
      : Light(handle, LightType::Spot, intensity), _position(position), _direction(direction),
        _attenuation(attenuation), _innerCutoff(innerCutoff), _outerCutoff(outerCutoff)
  {
  }

  void SpotLight::SetPosition(const Vec3 &position) noexcept
  {
    _position = position;
    _dirty = true;
  }

  void SpotLight::SetDirection(const Vec3 &direction) noexcept
  {
    _direction = direction;
    _dirty = true;
  }

  void SpotLight::SetAttenuation(const Vec3 &attenuation) noexcept
  {
    _attenuation = attenuation;
    _dirty = true;
  }

  void SpotLight::SetInnerCutoff(float angle) noexcept
  {
    _innerCutoff = angle;
    _dirty = true;
  }

  void SpotLight::SetOuterCutoff(float angle) noexcept
  {
    _outerCutoff = angle;
    _dirty = true;
  }

  Vec3 SpotLight::GetPosition() const noexcept
  {
    return _position;
  }

  Vec3 SpotLight::GetDirection() const noexcept
  {
    return _direction;
  }

  Vec3 SpotLight::GetAttenuation() const noexcept
  {
    return _attenuation;
  }

  float SpotLight::GetInnerCutoff() const noexcept
  {
    return _innerCutoff;
  }

  float SpotLight::GetOuterCutoff() const noexcept
  {
    return _outerCutoff;
  }

  LightData SpotLight::GetData() const noexcept
  {
    LightData data;
    data.Intensity = GetIntensityData();
    data.Position = _position;
    data.Direction = _direction;
    data.Attenuation = _attenuation;
    data.Type = _type;
    data.InnerCutoff = _innerCutoff;
    data.OuterCutoff = _outerCutoff;
    return data;
  }
}