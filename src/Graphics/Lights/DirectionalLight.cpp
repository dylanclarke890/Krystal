#include "Graphics/Lights/DirectionalLight.hpp"
#include "Graphics/Colours.hpp"
#include "MTL/Matrices/Ext/Transformations.hpp"

namespace Krys::Gfx
{
  DirectionalLight::DirectionalLight(const Colour &colour, const Vec3 &direction, bool castsShadows) noexcept
      : _colour(colour), _direction(Vec4(direction, 0.0f)),
        _shadowCamera(CameraType::Orthographic, 100u, 100u, 1'000u), _castsShadows(castsShadows)
  {
    auto lookAt = MTL::LookAt(Vec3(0.0f), -direction, Vec3(0.0f, 1.0f, 0.0f));
    _shadowCamera.SetView(lookAt);
  }

  DirectionalLight::DirectionalLight(const Vec3 &direction, bool castsShadows) noexcept
      : DirectionalLight(Colours::White, direction, castsShadows)
  {
  }

  LightType DirectionalLight::GetType() const noexcept
  {
    return LightType::Directional;
  }

  Vec4 DirectionalLight::GetColourData() const noexcept
  {
    return {_colour.r, _colour.g, _colour.b, _colour.a};
  }

  Vec3 DirectionalLight::GetAttentuation() const noexcept
  {
    return Vec3(1.0f, 1.0f, 1.0f);
  }

  Vec4 DirectionalLight::GetWorldSpaceData() const noexcept
  {
    return _direction;
  }

  void DirectionalLight::SetDirection(const Vec4 &direction) noexcept
  {
    _direction = direction;
  }

  Vec4 DirectionalLight::GetDirection() const noexcept
  {
    return _direction;
  }

  const Colour &DirectionalLight::GetColour() const noexcept
  {
    return _colour;
  }

  void DirectionalLight::SetColour(const Colour &colour) noexcept
  {
    _colour = colour;
  }

  const Camera &DirectionalLight::GetShadowCamera() const noexcept
  {
    return _shadowCamera;
  }

  bool DirectionalLight::CastsShadows() const noexcept
  {
    return _castsShadows;
  }
}