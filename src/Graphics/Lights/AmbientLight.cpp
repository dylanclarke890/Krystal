#include "Graphics/Lights/AmbientLight.hpp"

namespace Krys::Gfx
{
  AmbientLight::AmbientLight(LightHandle handle, const Colour &colour) noexcept
      : Light(handle, LightType::Ambient), _colour(colour)
  {
  }

  Vec4 AmbientLight::GetColourData() const noexcept
  {
    return Vec4(_colour.r, _colour.g, _colour.b, _colour.a);
  }

  Vec3 AmbientLight::GetAttentuation() const noexcept
  {
    return Vec3(0.0f, 0.0f, 0.0f);
  }

  Vec4 AmbientLight::GetWorldSpaceData() const noexcept
  {
    return Vec4(0.0f, 0.0f, 0.0f, 0.0f);
  }

  const Colour &AmbientLight::GetColour() const noexcept
  {
    return _colour;
  }

  void AmbientLight::SetColour(const Colour &colour) noexcept
  {
    _colour = colour;
  }
}