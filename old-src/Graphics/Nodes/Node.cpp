#include "Graphics/Nodes/Node.h"
#include "Graphics/NodeVisitors/NodeVisitor.h"

#pragma once

namespace Krys::Graphics
{
  void Node::Accept(NodeVisitor &visitor) noexcept
  {
    visitor.Visit(*this);
  }
}