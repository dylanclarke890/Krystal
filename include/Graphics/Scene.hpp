#pragma once

#include "Base/Attributes.hpp"
#include "Base/Macros.hpp"
#include "Base/Types.hpp"
#include "Graphics/Cameras/Camera.hpp"
#include "Graphics/Colour.hpp"
#include "Graphics/Entities/InstancedRenderEntity.hpp"
#include "Graphics/Entities/RenderEntity.hpp"
#include "Graphics/Entities/SingleRenderEntity.hpp"
#include "Graphics/Handles.hpp"
#include "Graphics/Lights/DirectionalLight.hpp"
#include "Graphics/Lights/LightingRig.hpp"
#include "Graphics/Lights/PointLight.hpp"

namespace Krys::Gfx
{
  /// @brief A scene is a collection of entities and lights that can be rendered.
  /// It owns all the entities and lights that are added to it.
  class Scene
  {
  public:
    Scene() = delete;
    ~Scene() = default;

    NO_COPY_MOVE(Scene);

    /// @brief Get the name of the scene.
    NO_DISCARD const string &GetName() const noexcept;

    /// @brief Get all the entities in the scene.
    NO_DISCARD List<RenderEntity *> GetEntities() const noexcept;

    /// @brief Get the lighting rig of the scene.
    NO_DISCARD const LightingRig &GetLightingRig() const noexcept;

    /// @brief Get the ambient lighting of the scene.
    NO_DISCARD const Colour &GetAmbientLight() const noexcept;

    /// @brief Remove a light from the scene.
    /// @param handle The handle of the light to remove.
    /// @note This can be used for any type of light; it will be removed from the scene and destroyed.
    /// @return True if the light was found and removed, false otherwise.
    bool RemoveLight(LightHandle handle) noexcept;

    /// @brief Remove an entity from the scene.
    /// @param handle The handle of the entity to remove.
    /// @note This can be used for any type of entity; it will be removed from the scene and destroyed.
    /// @return True if the entity was found and removed, false otherwise.
    bool RemoveEntity(RenderEntityHandle handle) noexcept;

    /// @brief Set the ambient lighting for the scene. The light will be owned by the scene.
    /// @tparam Args The types of the arguments to pass to the constructor of the light.
    /// @param args The arguments to forward to the constructor of the light.
    /// @return A handle to the light.
    template <typename... Args>
    LightHandle SetAmbientLight(Args &&...args) noexcept
    {
      if (_lightingRig.AmbientLight)
        RemoveLight(_lightingRig.AmbientLight->GetHandle());

      auto handle = _lightHandles.Next();
      _lightingRig.AmbientLight = CreateUnique<AmbientLight>(handle, std::forward<Args>(args)...);
      return handle;
    }

    /// @brief Add a directional light to the scene. The light will be owned by the scene.
    /// @tparam Args The types of the arguments to pass to the constructor of the light.
    /// @param args The arguments to forward to the constructor of the light.
    /// @return A handle to the light.
    template <typename... Args>
    NO_DISCARD LightHandle AddDirectionalLight(Args &&...args) noexcept
    {
      auto handle = _lightHandles.Next();
      auto light = CreateUnique<DirectionalLight>(handle, std::forward<Args>(args)...);
      _lightingRig.DirectionalLights.emplace_back(std::move(light));
      return handle;
    }

    /// @brief Add a point light to the scene.
    /// @tparam Args The types of the arguments to pass to the constructor of the light.
    /// @param args The arguments to forward to the constructor of the light.
    /// @return A handle to the light.
    template <typename... Args>
    NO_DISCARD LightHandle AddPointLight(Args &&...args) noexcept
    {
      auto handle = _lightHandles.Next();
      auto light = CreateUnique<PointLight>(handle, std::forward<Args>(args)...);
      _lightingRig.PointLights.emplace_back(std::move(light));
      return handle;
    }

    /// @brief Add an entity to the scene.
    /// @tparam T The entity type.
    /// @tparam Args The types of the arguments to pass to the constructor of the entity.
    /// @param args The arguments to forward to the constructor of the entity.
    /// @return A handle to the entity.
    template <typename T, typename... Args>
    requires std::derived_from<T, RenderEntity>
    NO_DISCARD RenderEntityHandle AddEntity(Args &&...args) noexcept
    {
      auto handle = _renderEntityHandles.Next();
      auto entity = CreateUnique<T>(handle, std::forward<Args>(args)...);
      _renderEntities.emplace(handle, std::move(entity));
      return handle;
    }

    /// @brief Get an entity by its handle.
    /// @tparam T The type of the entity to get. Can be omitted to get the base class, useful if the type is
    /// unknown.
    /// @param handle The handle of the entity.
    /// @return A pointer to the entity if it was found, nullptr otherwise.
    /// @note The type is static_cast to T, so it must be a valid cast. Use the default type if unsure then
    /// get the derived type via `entity.GetType()` and cast it that way.
    template <typename T = RenderEntity>
    requires std::derived_from<T, RenderEntity>
    NO_DISCARD T *GetEntity(RenderEntityHandle handle) noexcept
    {
      if (const auto it = _renderEntities.find(handle); it != _renderEntities.end())
        return static_cast<T *>(it->second.get());
      return nullptr;
    }

    /// @brief Set the camera for the scene.
    /// @param camera The camera to set.
    void SetCamera(Camera *camera) noexcept;

  protected:
    friend class SceneManager;

    Scene(SceneHandle handle, const string &name) noexcept;

    string _name;
    SceneHandle _handle;
    LightingRig _lightingRig;
    LightHandleManager _lightHandles {};
    Camera *_camera {nullptr};

    RenderEntityHandleMap<Unique<RenderEntity>> _renderEntities;
    RenderEntityHandleManager _renderEntityHandles {};
  };
}