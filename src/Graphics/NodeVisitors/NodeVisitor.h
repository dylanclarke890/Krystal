#pragma once

#include "Graphics/Nodes/Node.h"
#include "Graphics/Nodes/GeometryNode.h"
#include "Graphics/Renderer.h"

namespace Krys::Graphics
{
  class SceneManager;

  class NodeVisitor
  {
    friend class SceneManager;

  protected:
    Ref<Renderer> _renderer;

  public:
    virtual ~NodeVisitor() = default;
    virtual void Visit(const Node &node) = 0;
    virtual void Visit(const GeometryNode &node) = 0;
  };
}