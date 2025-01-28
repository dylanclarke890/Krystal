#include "Graphics/SceneManager.hpp"

namespace Krys::Gfx
{
  bool SceneManager::RemoveScene(SceneHandle handle) noexcept
  {
    auto it = _scenes.find(handle);
    bool wasFound = it != _scenes.end();

    if (wasFound)
    {
      if (_activeScene == handle)
        _activeScene = SceneHandle::InvalidHandle;

      _sceneNames.erase(it->second->GetName());
      _scenes.erase(it);
      _sceneHandles.Recycle(handle);
    }

    return wasFound;
  }

  bool SceneManager::RemoveScene(const string &name) noexcept
  {
    auto it = _sceneNames.find(name);
    bool wasFound = it != _sceneNames.end();

    if (wasFound)
    {
      auto handle = it->second;
      if (_activeScene == handle)
        _activeScene = SceneHandle::InvalidHandle;

      _scenes.erase(handle);
      _sceneNames.erase(it);
      _sceneHandles.Recycle(handle);
    }

    return wasFound;
  }

  Scene *SceneManager::GetScene(const string &name) noexcept
  {
    auto it = _sceneNames.find(name);
    return it != _sceneNames.end() ? _scenes[it->second].get() : nullptr;
  }

  Scene *SceneManager::GetScene(SceneHandle handle) noexcept
  {
    auto it = _scenes.find(handle);
    return it != _scenes.end() ? it->second.get() : nullptr;
  }

  void SceneManager::SetActiveScene(const string &name) noexcept
  {
    auto it = _sceneNames.find(name);
    KRYS_ASSERT(it != _sceneNames.end(), "Scene not found.");
    _activeScene = it->second;
  }

  void SceneManager::SetActiveScene(SceneHandle handle) noexcept
  {
    auto it = _scenes.find(handle);
    KRYS_ASSERT(it != _scenes.end(), "Scene not found.");
    _activeScene = handle;
  }

  Scene &SceneManager::GetActiveScene() const noexcept
  {
    KRYS_ASSERT(_activeScene.IsValid(), "No active scene has been set.");
    return *_scenes.at(_activeScene);
  }
}