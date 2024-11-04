#include "Graphics/Nodes/GeometryNode.h"
#include "Graphics/NodeVisitors/NodeVisitor.h"

namespace Krys::Graphics
{
  void GeometryNode::Accept(NodeVisitor &visitor) noexcept
  {
    visitor.Visit(*this);
  }
}