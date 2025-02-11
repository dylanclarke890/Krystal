#include "Graphics/Lights/Light.hpp"

namespace Krys::Gfx
{
  Light::Light(LightHandle handle, LightType type, const Colour &intensity) noexcept
      : _handle(handle), _type(type), _intensity(intensity)
  {
  }

  LightHandle Light::GetHandle() const noexcept
  {
    return _handle;
  }

  LightType Light::GetType() const noexcept
  {
    return _type;
  }

  const Colour &Light::GetIntensity() const noexcept
  {
    return _intensity;
  }

  void Light::SetIntensity(const Colour &intensity) noexcept
  {
    _intensity = intensity;
    _dirty = true;
  }

  Vec3 Light::GetIntensityData() const noexcept
  {
    return Vec3 {_intensity.r, _intensity.g, _intensity.b};
  }

  bool Light::IsDirty() const noexcept
  {
    return _dirty;
  }

  void Light::ClearIsDirtyFlag() noexcept
  {
    _dirty = false;
  }
}