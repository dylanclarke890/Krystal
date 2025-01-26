#pragma once

#include "Base/Types.hpp"
#include "Graphics/Lights/LightType.hpp"
#include "MTL/Vectors/Vec3.hpp"
#include "MTL/Vectors/Vec4.hpp"

namespace Krys::Gfx
{
  /// @brief Represents a light in the scene.
  class Light
  {
  public:
    virtual ~Light() = default;

    /// @brief Gets the type of light.
    NO_DISCARD virtual LightType GetType() const noexcept = 0;

    /// @brief Get the colour data of the light.
    NO_DISCARD virtual Vec4 GetColourData() const noexcept = 0;

    /// @brief Get the attenuation data of the light.
    NO_DISCARD virtual Vec3 GetAttentuation() const noexcept = 0;

    /// @brief Gets the raw data for the lights world space property e.g. position or direction.
    NO_DISCARD virtual Vec4 GetWorldSpaceData() const noexcept = 0;
  };
}