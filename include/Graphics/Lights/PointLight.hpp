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
    /// @param intensity The intensity of the light.
    /// @param position The position of the light.
    PointLight(LightHandle handle, const Colour &intensity, const Vec3 &position) noexcept;

    /// @brief Construct a point light.
    /// @param handle The handle of the light.
    /// @param position The position of the light.
    PointLight(LightHandle handle, const Vec3 &position) noexcept;

    /// @brief Get the position of the light.
    NO_DISCARD const Vec3 &GetPosition() const noexcept;

    /// @brief Set the position of the light.
    /// @param position The new position of the light.
    void SetPosition(const Vec3 &position) noexcept;

    /// @brief Set the attenuation of the light
    /// @param attenuation The new attenuation of the light. `x` is the constant attenuation, `y` is the
    /// linear attenuation, `z` is the quadratic attenuation.
    void SetAttenuation(const Vec3 &attenuation) noexcept;

    /// @brief Get the attenuation of the light.
    NO_DISCARD const Vec3 &GetAttenuation() const noexcept;

    /// @brief Get the data of the light.
    /// @note Some lights may not have all the data, in which case the missing data will be zeroed out.
    NO_DISCARD LightData GetData() const noexcept override;

  private:
    Vec3 _position;
    Vec3 _attenuation;
  };
}