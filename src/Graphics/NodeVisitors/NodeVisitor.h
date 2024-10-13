#pragma once

#include "Graphics/Nodes/Node.h"
#include "Graphics/Nodes/GeometryNode.h"

namespace Krys::Graphics
{
  class NodeVisitor
  {
  public:
    virtual void Visit(const Node &node) = 0;
    virtual void Visit(const GeometryNode &node) = 0;
  };
}