#include "Graphics/Scene/SceneGraphManager.hpp"

namespace Krys::Gfx
{
  bool SceneGraphManager::RemoveScene(SceneGraphHandle handle) noexcept
  {
    if (auto it = _scenes.find(handle); it != _scenes.end())
    {
      if (_activeScene == handle)
        _activeScene = SceneGraphHandle::InvalidHandle;

      _sceneNames.erase(it->second->GetName());
      _scenes.erase(it);
      _sceneGraphHandles.Recycle(handle);
      return true;
    }

    return false;
  }

  bool SceneGraphManager::RemoveScene(const string &name) noexcept
  {
    if (auto it = _sceneNames.find(name); it != _sceneNames.end())
    {
      auto handle = it->second;
      if (_activeScene == handle)
        _activeScene = SceneGraphHandle::InvalidHandle;

      _scenes.erase(handle);
      _sceneNames.erase(it);
      _sceneGraphHandles.Recycle(handle);
      return true;
    }

    return false;
  }

  SceneGraph *SceneGraphManager::GetScene(const string &name) noexcept
  {
    if (auto it = _sceneNames.find(name); it != _sceneNames.end())
      return _scenes[it->second].get();
    return nullptr;
  }

  SceneGraph *SceneGraphManager::GetScene(SceneGraphHandle handle) noexcept
  {
    if (auto it = _scenes.find(handle); it != _scenes.end())
      return it->second.get();
    return nullptr;
  }

  void SceneGraphManager::SetActiveScene(const string &name) noexcept
  {
    auto it = _sceneNames.find(name);

    KRYS_ASSERT(it != _sceneNames.end(), "Scene not found.");
    KRYS_ASSERT(it->second.IsValid(), "Invalid scene handle.");

    if (it != _sceneNames.end() && it->second.IsValid())
      _activeScene = it->second;
  }

  void SceneGraphManager::SetActiveScene(SceneGraphHandle handle) noexcept
  {
    auto it = _scenes.find(handle);

    KRYS_ASSERT(handle.IsValid(), "Invalid scene handle.");
    KRYS_ASSERT(it != _scenes.end(), "Scene not found.");

    if (it != _scenes.end())
      _activeScene = handle;
  }

  SceneGraph *SceneGraphManager::GetActiveScene() const noexcept
  {
    KRYS_ASSERT(_activeScene.IsValid(), "No active scene has been set.");
    if (auto it = _scenes.find(_activeScene); it != _scenes.end())
      return it->second.get();
    return nullptr;
  }
}