#include "Graphics/Lights/PointLight.hpp"
#include "Graphics/Colours.hpp"

namespace Krys::Gfx
{
  PointLight::PointLight(const Vec3 &position, const Colour &colour) noexcept
      : _position(Vec4(position, 1.0f)), _colour(colour), _attenuation({0.0f, 0.0f, 0.0f}),
        _shadowCameras(Array<Camera, 6>({Camera(CameraType::Perspective, 90u, 90u, 1'000u),
                                         Camera(CameraType::Perspective, 90u, 90u, 1'000u),
                                         Camera(CameraType::Perspective, 90u, 90u, 1'000u),
                                         Camera(CameraType::Perspective, 90u, 90u, 1'000u),
                                         Camera(CameraType::Perspective, 90u, 90u, 1'000u),
                                         Camera(CameraType::Perspective, 90u, 90u, 1'000u)}))
  {
  }

  PointLight::PointLight(const Vec3 &position) noexcept : PointLight(position, Colours::White)
  {
  }

  LightType PointLight::GetType() const noexcept
  {
    return LightType::Point;
  }

  Vec4 PointLight::GetColourData() const noexcept
  {
    return {_colour.r, _colour.g, _colour.b, _colour.a};
  }

  Vec3 PointLight::GetAttentuation() const noexcept
  {
    return _attenuation;
  }

  Vec4 PointLight::GetWorldSpaceData() const noexcept
  {
    return _position;
  }

  Vec3 PointLight::GetPosition() const noexcept
  {
    return {_position.x, _position.y, _position.z};
  }

  void PointLight::SetPosition(const Vec3 &position) noexcept
  {
    _position = Vec4(position, 1.0f);
  }

  const Colour &PointLight::GetColour() const noexcept
  {
    return _colour;
  }

  void PointLight::SetColour(const Colour &colour) noexcept
  {
    _colour = colour;
  }
}