#include "Graphics/Scene/SceneGraph.h"

namespace Krys::Graphics
{
  SceneGraph::SceneGraph() noexcept
      : Root(CreateRef<Node>()) {}

  SceneGraph::SceneGraph(Ref<Node> root) noexcept
      : Root(root) {}

  void SceneGraph::Add(Ref<Node> node) noexcept
  {
    node->Parent = Root;
    Root->Children.push_back(node);
  }

  void SceneGraph::Attach(Ref<Node> node, Ref<Node> parent) noexcept
  {
    node->Parent = parent;
    parent->Children.push_back(node);
  }

  void SceneGraph::Remove(Ref<Node> node) noexcept
  {
    if (auto parent = node->Parent.lock())
      parent->Children.erase(std::find(parent->Children.begin(), parent->Children.end(), node));
  }

  SceneGraph SceneGraph::Detach(Ref<Node> node) noexcept
  {
    if (auto parent = node->Parent.lock())
    {
      parent->Children.erase(std::find(parent->Children.begin(), parent->Children.end(), node));
      return SceneGraph(node);
    }
    return Ref<Node>(nullptr);
  }
}