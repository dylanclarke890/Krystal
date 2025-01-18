#include "Graphics/Nodes/Node.h"
#include "Graphics/NodeVisitors/NodeVisitor.h"

#pragma once

namespace Krys::Gfx
{
  void Node::Accept(NodeVisitor &visitor) noexcept
  {
    visitor.Visit(*this);
  }
}