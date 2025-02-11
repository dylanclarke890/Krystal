#pragma once

#include "Base/Attributes.hpp"
#include "Graphics/Colour.hpp"
#include "Graphics/Lights/Light.hpp"
#include "MTL/Vectors/Vec3.hpp"

namespace Krys::Gfx
{
  /// @brief A directional light. This is a light infinitely far away from the scene.
  class DirectionalLight : public Light
  {
  public:
    /// @brief Construct a directional light.
    /// @param handle The handle of the light.
    /// @param intensity The intensity of the light.
    /// @param direction The direction of the light.
    DirectionalLight(LightHandle handle, const Colour &intensity, const Vec3 &direction) noexcept;

    /// @brief Construct a directional light.
    /// @param handle The handle of the light.
    /// @param direction The direction of the light.
    DirectionalLight(LightHandle handle, const Vec3 &direction) noexcept;

    /// @brief Set the direction of the light.
    /// @param direction The new direction of the light.
    void SetDirection(const Vec3 &direction) noexcept;

    /// @brief Get the direction of the light.
    NO_DISCARD const Vec3 &GetDirection() const noexcept;

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
    Vec3 _direction;
    Vec3 _attenuation;
  };
}