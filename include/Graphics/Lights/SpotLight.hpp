#pragma once

#include "Base/Attributes.hpp"
#include "Graphics/Lights/Light.hpp"

namespace Krys::Gfx
{
  /// @brief Represents a spot light.
  class SpotLight : public Light
  {
  public:
    /// @brief Construct a spot light.
    /// @param handle The handle of the light.
    /// @param intensity The intensity of the light.
    /// @param position The position of the light.
    /// @param direction The direction of the light.
    /// @param attenuation The attenuation of the light.
    /// @param innerCutoff The inner cutoff angle in degrees.
    /// @param outerCutoff The outer cutoff angle in degrees.
    SpotLight(LightHandle handle, const Colour &intensity, const Vec3 &position, const Vec3 &direction,
              const Vec3 &attenuation = Vec3 {1.0f, 0.09f, 0.032f}, float innerCutoff = 12.5f,
              float outerCutoff = 17.5f) noexcept;

    /// @brief Sets the position of the light.
    /// @param position The position.
    void SetPosition(const Vec3 &position) noexcept;

    /// @brief Sets the direction of the light.
    /// @param direction The direction.
    void SetDirection(const Vec3 &direction) noexcept;

    /// @brief Sets the attenuation of the light.
    /// @param attenuation The attenuation.
    void SetAttenuation(const Vec3 &attenuation) noexcept;

    /// @brief Sets the inner cutoff angle.
    /// @param angle The angle in degrees.
    void SetInnerCutoff(float angle) noexcept;

    /// @brief Sets the outer cutoff angle.
    /// @param angle The angle in degrees.
    void SetOuterCutoff(float angle) noexcept;

    /// @brief Gets the position of the light.
    /// @return The position.
    NO_DISCARD Vec3 GetPosition() const noexcept;

    /// @brief Gets the direction of the light.
    /// @return The direction.
    NO_DISCARD Vec3 GetDirection() const noexcept;

    /// @brief Gets the attenuation of the light.
    /// @return The attenuation.
    NO_DISCARD Vec3 GetAttenuation() const noexcept;

    /// @brief Gets the inner cutoff angle.
    /// @return The angle in degrees.
    NO_DISCARD float GetInnerCutoff() const noexcept;

    /// @brief Gets the outer cutoff angle.
    /// @return The angle in degrees.
    NO_DISCARD float GetOuterCutoff() const noexcept;

    /// @brief Get the data of the light.
    /// @note Some lights may not have all the data, in which case the missing data will be zeroed out.
    NO_DISCARD LightData GetData() const noexcept override;

  private:
    Vec3 _position;
    Vec3 _direction;
    Vec3 _attenuation;
    float _innerCutoff;
    float _outerCutoff;
  };
}