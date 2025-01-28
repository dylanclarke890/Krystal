#pragma once

#include "Graphics/Colour.hpp"
#include "Graphics/Lights/Light.hpp"

namespace Krys::Gfx
{
  /// @brief An ambient light. This is a light that is present everywhere in the scene.
  /// @note This light does not have a position or direction.
  class AmbientLight : public Light
  {
  public:
    /// @brief Construct an ambient light.
    /// @param handle The handle of the light.
    /// @param colour The colour of the light.
    AmbientLight(LightHandle handle, const Colour &colour) noexcept;

    /// @brief Get the type of light.
    NO_DISCARD LightType GetType() const noexcept override;

    /// @brief Get the colour data of the light.
    NO_DISCARD Vec4 GetColourData() const noexcept override;

    /// @brief Get the attenuation data of the light.
    /// @note This is not used for ambient lights, returns (0, 0, 0).
    NO_DISCARD Vec3 GetAttentuation() const noexcept override;

    /// @brief Gets the raw data for the lights world space property e.g. position or direction.
    /// @note This is not used for ambient lights, returns (0, 0, 0, 0).
    NO_DISCARD Vec4 GetWorldSpaceData() const noexcept override;

    /// @brief Get the colour of the light.
    NO_DISCARD const Colour &GetColour() const noexcept;

    /// @brief Set the colour of the light.
    void SetColour(const Colour &colour) noexcept;

  private:
    Colour _colour;
  };
}