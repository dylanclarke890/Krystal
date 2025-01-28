#pragma once

#include "Base/Attributes.hpp"
#include "Base/Macros.hpp"
#include "Base/Pointers.hpp"
#include "Base/Types.hpp"
#include "Graphics/Handles.hpp"
#include "Graphics/Scene.hpp"

namespace Krys::Gfx
{
  class SceneManager
  {
  public:
    ~SceneManager() = default;

    NO_COPY_MOVE(SceneManager);

    /// @brief Create a new scene with the given name. If this is the first scene created, it will
    /// automatically be set as the active scene.
    /// @tparam ...Args The types of the arguments to pass to the constructor of the scene.
    /// @param name The name of the scene.
    /// @param ...args The arguments to forward to the constructor of the scene.
    /// @return A handle to the scene.
    /// @note The scene will be owned by the scene manager. Unlike other managers, you are not required to
    /// keep track of the handle of the scene, you can use the name if you prefer.
    template <typename... Args>
    SceneHandle CreateScene(const string &name, Args &&...args) noexcept
    {
      auto handle = _sceneHandles.Next();
      auto scene = CreateUnique<Scene>(handle, name, std::forward<Args>(args)...);

      _scenes.emplace(handle, std::move(scene));
      _sceneNames.emplace(name, handle);

      if (!_activeScene.IsValid())
        _activeScene = handle;

      return handle;
    }

    /// @brief Remove a scene from the scene manager.
    /// @param handle The handle of the scene to remove.
    /// @return True if the scene was found and removed, false otherwise.
    bool RemoveScene(SceneHandle handle) noexcept;

    /// @brief Remove a scene from the scene manager.
    /// @param name The name of the scene to remove.
    /// @return True if the scene was found and removed, false otherwise.
    bool RemoveScene(const string &name) noexcept;

    /// @brief Get a scene by name.
    /// @param name The name of the scene.
    /// @return A pointer to the scene if it exists, nullptr otherwise.
    NO_DISCARD Scene *GetScene(const string &name) noexcept;

    /// @brief Get a scene by handle.
    /// @param handle The handle of the scene.
    /// @return A pointer to the scene if it exists, nullptr otherwise.
    NO_DISCARD Scene *GetScene(SceneHandle handle) noexcept;

    /// @brief Get the active scene.
    /// @return A reference to the active scene.
    /// @note If you call this before setting an active scene it will trigger an assertion.
    NO_DISCARD Scene &GetActiveScene() const noexcept;

    void SetActiveScene(const string &name) noexcept;
    void SetActiveScene(SceneHandle handle) noexcept;

  private:
    Map<SceneHandle, Unique<Scene>, SceneHandle::Hash> _scenes;
    Map<string, SceneHandle> _sceneNames;

    SceneHandle _activeScene{};
    HandleManager<SceneHandle> _sceneHandles{};
  };
}