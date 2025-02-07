#pragma once

#include "Base/Attributes.hpp"
#include "Base/Macros.hpp"
#include "Base/Pointers.hpp"
#include "Base/Types.hpp"
#include "Graphics/Handles.hpp"
#include "Graphics/Scene/SceneGraph.hpp"

namespace Krys::Gfx
{
  class SceneGraphManager
  {
  public:
    SceneGraphManager() noexcept = default;
    ~SceneGraphManager() = default;

    NO_COPY_MOVE(SceneGraphManager);

    /// @brief Create a new scene with the given name. If this is the first scene created, it will
    /// automatically be set as the active scene.
    /// @tparam ...Args The types of the arguments to pass to the constructor of the scene.
    /// @param name The name of the scene.
    /// @param ...args The arguments to forward to the constructor of the scene.
    /// @return A handle to the scene.
    /// @note Like other managers, the created scene will be owned by the scene manager. Unlike other
    /// managers, you are not required to keep track of the handle of the scene, you can use the name if you
    /// prefer.
    template <typename... Args>
    SceneGraphHandle CreateScene(const string &name, Args &&...args) noexcept
    {
      auto handle = _sceneGraphHandles.Next();
      auto scene = Unique<SceneGraph>(new SceneGraph(handle, name, std::forward<Args>(args)...));

      _scenes.emplace(handle, std::move(scene));
      _sceneNames.emplace(name, handle);

      if (!_activeScene.IsValid())
        _activeScene = handle;

      return handle;
    }

    /// @brief Remove a scene from the scene manager using it's handle.
    /// @param handle The handle of the scene to remove.
    /// @return True if the scene was found and removed, false otherwise.
    bool RemoveScene(SceneGraphHandle handle) noexcept;

    /// @brief Remove a scene from the scene manager using it's name.
    /// @param name The name of the scene to remove.
    /// @return True if the scene was found and removed, false otherwise.
    bool RemoveScene(const string &name) noexcept;

    /// @brief Get a scene by name.
    /// @param name The name of the scene.
    /// @return A pointer to the scene if it exists, nullptr otherwise.
    NO_DISCARD SceneGraph *GetScene(const string &name) noexcept;

    /// @brief Get a scene by handle.
    /// @param handle The handle of the scene.
    /// @return A pointer to the scene if it exists, nullptr otherwise.
    NO_DISCARD SceneGraph *GetScene(SceneGraphHandle handle) noexcept;

    /// @brief Get the active scene.
    /// @return A pointer to the active scene.
    NO_DISCARD SceneGraph *GetActiveScene() const noexcept;

    /// @brief Set the active scene by name.
    /// @param name The name of the scene to set as active.
    void SetActiveScene(const string &name) noexcept;

    /// @brief Set the active scene by handle.
    /// @param handle The handle of the scene to set as active.
    void SetActiveScene(SceneGraphHandle handle) noexcept;

  private:
    SceneGraphHandleMap<Unique<SceneGraph>> _scenes;
    SceneGraphHandleManager _sceneGraphHandles {};
    Map<string, SceneGraphHandle> _sceneNames;
    SceneGraphHandle _activeScene {};
  };
}