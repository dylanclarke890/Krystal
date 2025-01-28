#include "Graphics/SceneManager.hpp"

namespace Krys::Gfx
{
  bool SceneManager::RemoveScene(SceneHandle handle) noexcept
  {
    if (auto it = _scenes.find(handle); it != _scenes.end())
    {
      if (_activeScene == handle)
        _activeScene = SceneHandle::InvalidHandle;

      _sceneNames.erase(it->second->GetName());
      _scenes.erase(it);
      _sceneHandles.Recycle(handle);
      return true;
    }

    return false;
  }

  bool SceneManager::RemoveScene(const string &name) noexcept
  {
    if (auto it = _sceneNames.find(name); it != _sceneNames.end())
    {
      auto handle = it->second;
      if (_activeScene == handle)
        _activeScene = SceneHandle::InvalidHandle;

      _scenes.erase(handle);
      _sceneNames.erase(it);
      _sceneHandles.Recycle(handle);
      return true;
    }

    return false;
  }

  Scene *SceneManager::GetScene(const string &name) noexcept
  {
    if (auto it = _sceneNames.find(name); it != _sceneNames.end())
      return _scenes[it->second].get();
    return nullptr;
  }

  Scene *SceneManager::GetScene(SceneHandle handle) noexcept
  {
    if (auto it = _scenes.find(handle); it != _scenes.end())
      return it->second.get();
    return nullptr;
  }

  void SceneManager::SetActiveScene(const string &name) noexcept
  {
    auto it = _sceneNames.find(name);

    KRYS_ASSERT(it != _sceneNames.end(), "Scene not found.");
    KRYS_ASSERT(it->second.IsValid(), "Invalid scene handle.");

    if (it != _sceneNames.end() && it->second.IsValid())
      _activeScene = it->second;
  }

  void SceneManager::SetActiveScene(SceneHandle handle) noexcept
  {
    auto it = _scenes.find(handle);

    KRYS_ASSERT(handle.IsValid(), "Invalid scene handle.");
    KRYS_ASSERT(it != _scenes.end(), "Scene not found.");

    if (it != _scenes.end())
      _activeScene = handle;
  }

  Scene *SceneManager::GetActiveScene() const noexcept
  {
    KRYS_ASSERT(_activeScene.IsValid(), "No active scene has been set.");
    if (auto it = _scenes.find(_activeScene); it != _scenes.end())
      return it->second.get();
    return nullptr;
  }
}