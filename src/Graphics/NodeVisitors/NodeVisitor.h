#pragma once

#include "Graphics/Nodes/Node.h"
#include "Graphics/Nodes/GeometryNode.h"
#include "Graphics/NodeVisitors/NodeVisitorContext.h"

namespace Krys::Graphics
{
  class SceneManager;

  class NodeVisitor
  {
    friend class SceneManager;

  protected:
    NodeVisitorContext _context;

  public:
    NodeVisitor(NodeVisitorContext context) noexcept
     : _context(context) {}
    virtual ~NodeVisitor() noexcept = default;
    virtual void Visit(const Node &node) noexcept = 0;
    virtual void Visit(const GeometryNode &node) noexcept = 0;
  };
}