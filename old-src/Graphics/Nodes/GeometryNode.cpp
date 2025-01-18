#include "Graphics/Nodes/GeometryNode.h"
#include "Graphics/NodeVisitors/NodeVisitor.h"

namespace Krys::Gfx
{
  void GeometryNode::Accept(NodeVisitor &visitor) noexcept
  {
    visitor.Visit(*this);
  }
}