#pragma once

#include "Base/Types.hpp"
#include "Graphics/Handles.hpp"
#include "Graphics/Lights/LightData.hpp"
#include "Graphics/Lights/LightType.hpp"
#include "Graphics/Colour.hpp"

namespace Krys::Gfx
{
  /// @brief Represents a light in the scene.
  class Light
  {
  public:
    virtual ~Light() = default;

    /// @brief Gets the type of light.
    NO_DISCARD LightType GetType() const noexcept;

    /// @brief Get the handle of the light.
    NO_DISCARD LightHandle GetHandle() const noexcept;

    /// @brief Get the intensity of the light.
    NO_DISCARD const Colour &GetIntensity() const noexcept;

    /// @brief Set the intensity of the light.
    void SetIntensity(const Colour &intensity) noexcept;

    /// @brief Get the data of the light.
    /// @note Some lights may not have all the data, in which case the missing data will be zeroed out.
    virtual LightData GetData() const noexcept = 0;

    NO_DISCARD bool IsDirty() const noexcept;

    void ClearIsDirtyFlag() noexcept;

  protected:
    explicit Light(LightHandle handle, LightType type,
                   const Colour &intensity = Colour {1.0f, 1.0f, 1.0f}) noexcept;

    NO_DISCARD Vec3 GetIntensityData() const noexcept;

    LightHandle _handle;
    LightType _type;
    Colour _intensity;
    bool _dirty {true};
  };
}