#pragma once

#include "Graphics/Cameras/Camera.hpp"
#include "Graphics/Colour.hpp"
#include "Graphics/Lights/Light.hpp"

namespace Krys::Gfx
{
  /// @brief Represents a point light in the scene. This light has a position and emits light in all
  /// directions.
  class PointLight : public Light
  {
  public:
    /// @brief Construct a point light.
    /// @param handle The handle of the light.
    /// @param position The position of the light.
    PointLight(LightHandle handle, const Vec3 &position) noexcept;

    /// @brief Construct a point light.
    /// @param handle The handle of the light.
    /// @param position The position of the light.
    /// @param colour The colour of the light.
    PointLight(LightHandle handle, const Vec3 &position, const Colour &colour) noexcept;

    /// @brief Get the colour data of the light.
    NO_DISCARD Vec4 GetColourData() const noexcept override;

    /// @brief Get the attenuation data of the light.
    NO_DISCARD Vec3 GetAttentuation() const noexcept override;

    /// @brief Gets the raw data for the lights world space property e.g. position or direction.
    NO_DISCARD Vec4 GetWorldSpaceData() const noexcept override;

    /// @brief Get the position of the light.
    NO_DISCARD Vec3 GetPosition() const noexcept;

    /// @brief Set the position of the light.
    /// @param position The new position of the light.
    void SetPosition(const Vec3 &position) noexcept;

    /// @brief Get the colour of the light.
    NO_DISCARD const Colour &GetColour() const noexcept;

    /// @brief Set the colour of the light.
    void SetColour(const Colour &colour) noexcept;

  private:
    Vec4 _position;
    Colour _colour;
    Vec3 _attenuation;
    bool _castsShadows;
    Array<Camera, 6> _shadowCameras;
  };
}