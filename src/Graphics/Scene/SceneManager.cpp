#include "Graphics/Scene/SceneManager.h"

namespace Krys::Graphics
{
  void SceneManager::ChangeTo(Unique<Scene> scene) noexcept
  {
    _currentScene = std::move(scene);
  }

  void SceneManager::AddVisitor(Unique<NodeVisitor> visitor) noexcept
  {
    visitor->_renderer = _renderer;
    _visitors.push_back(std::move(visitor));
  }

  void SceneManager::UpdateScene() noexcept
  {
    Traverse(_currentScene->Graph.GetRoot());
  }

  void SceneManager::Traverse(Ref<Node> node) noexcept
  {
    for (int i = 0; i < _visitors.size(); i++)
      node->Accept(*_visitors[i]);

    for (auto child : node->Children)
      Traverse(child);
  }
}
