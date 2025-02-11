#pragma once

#include "Base/Pointers.hpp"
#include "Graphics/Handles.hpp"
#include "Graphics/Lights/Light.hpp"

namespace Krys::Gfx
{
  class LightManager
  {
  public:
    virtual ~LightManager() = default;

    /// @brief Create a light.
    /// @param type The type of light to create.
    /// @return A handle to the light.
    template <typename T, typename... Args>
    requires std::derived_from<T, Light>
    NO_DISCARD LightHandle CreateLight(Args... args) noexcept
    {
      auto handle = _lightHandles.Next();
      _lights[handle] = CreateUnique<T>(handle, std::forward<Args>(args)...);
      return handle;
    }

    /// @brief Get a light by handle.
    /// @param handle The handle of the light.
    /// @return A pointer to the light if it exists, nullptr otherwise.
    /// @note The type is static_cast to T, so it must be a valid cast. Use the default type if unsure then
    /// get the derived type via `light.GetType()` and cast it that way.
    template <typename T = Light, typename... Args>
    requires std::same_as<T, Light> || std::derived_from<T, Light>
    NO_DISCARD Light *GetLight(LightHandle handle) noexcept
    {
      auto it = _lights.find(handle);
      return it != _lights.end() ? static_cast<T>(it->second.get()) : nullptr;
    }

    /// @brief Destroy a light by handle.
    /// @param handle The handle of the light.
    /// @return True if the light was found and destroyed, false otherwise.
    bool DestroyLight(LightHandle handle) noexcept;

    const auto &GetLights() const noexcept
    {
      return _lights;
    }

  protected:
    LightHandleMap<Unique<Light>> _lights;
    LightHandleManager _lightHandles;
  };
}