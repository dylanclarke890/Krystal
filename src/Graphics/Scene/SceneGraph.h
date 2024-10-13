#pragma once

#include "Types.h"
#include "Graphics/Nodes/Node.h"

namespace Krys::Graphics
{
  class SceneGraph
  {
  private:
    Ref<Node> Root;

  public:
    SceneGraph() noexcept;
    SceneGraph(Ref<Node> root) noexcept;
    void Add(Ref<Node> node) noexcept;
    void Attach(Ref<Node> node, Ref<Node> parent) noexcept;
    void Remove(Ref<Node> node) noexcept;
    SceneGraph Detach(Ref<Node> node) noexcept;
  };
}