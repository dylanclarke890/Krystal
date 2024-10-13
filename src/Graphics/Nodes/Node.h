#pragma once

#include "Types.h"
#include "Maths/Transform.h"
#include "Graphics/NodeVisitors/NodeVisitor.h"

namespace Krys::Graphics
{
  class Node
  {
  public:
    virtual void Accept(NodeVisitor &visitor)
    {
      visitor.Visit(*this);
    }

    Maths::Transform Transform;
    WeakRef<Node> Parent;
    List<Ref<Node>> Children;
  };
}