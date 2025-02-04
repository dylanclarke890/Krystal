#pragma once

#include "Base/Attributes.hpp"
#include "Graphics/Cameras/Camera.hpp"
#include "Graphics/Colour.hpp"
#include "Graphics/Lights/Light.hpp"

namespace Krys::Gfx
{
  /// @brief A directional light. This is a light infinitely far away from the scene.
  /// @note A light may be constructed to cast shadows, this will cause extra render passes to be created
  /// which can impact performance (depending on scene complexity).
  class DirectionalLight : public Light
  {
  public:
    /// @brief Construct a directional light.
    /// @param handle The handle of the light.
    /// @param colour The colour of the light.
    /// @param direction The direction of the light.
    /// @param castsShadows Whether this light casts shadows.
    DirectionalLight(LightHandle handle, const Colour &colour, const Vec3 &direction, bool castsShadows = false) noexcept;

    /// @brief Construct a directional light.
    /// @param direction The direction of the light.
    /// @param castsShadows Whether this light casts shadows.
    DirectionalLight(LightHandle handle, const Vec3 &direction, bool castsShadows = false) noexcept;

    /// @brief Get the colour data of the light.
    NO_DISCARD Vec4 GetColourData() const noexcept override;

    /// @brief Get the attenuation data of the light.
    /// @note This is not used for directional lights, returns (1, 1, 1).
    NO_DISCARD Vec3 GetAttentuation() const noexcept override;

    /// @brief Gets the raw data for the lights world space property e.g. position or direction.
    NO_DISCARD Vec4 GetWorldSpaceData() const noexcept override;

    /// @brief Set the direction of the light.
    /// @param direction The new direction of the light.
    void SetDirection(const Vec4 &direction) noexcept;

    /// @brief Get the direction of the light.
    NO_DISCARD Vec4 GetDirection() const noexcept;

    /// @brief Set the colour of the light.
    NO_DISCARD const Colour &GetColour() const noexcept;

    /// @brief Get the colour of the light.
    void SetColour(const Colour &colour) noexcept;

    /// @brief Get the shadow camera of the light.
    NO_DISCARD const Camera &GetShadowCamera() const noexcept;

    /// @brief Get a boolean indicating whether the light casts shadows.
    NO_DISCARD bool CastsShadows() const noexcept;

  private:
    Colour _colour;
    Vec4 _direction;
    bool _castsShadows;
    Camera _shadowCamera;
  };
}