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

    /// @brief Get the data of the light.
    /// @note Some lights may not have all the data, in which case the missing data will be zeroed out.
    NO_DISCARD LightData GetData() const noexcept override;

  private:
    Vec3 _direction;
  };
}