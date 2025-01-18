#pragma once

#include "Types.h"
#include "Maths/Transform.h"

namespace Krys::Gfx
{
  class NodeVisitor;

  class Node
  {
  public:
    virtual ~Node() = default;
    virtual void Accept(NodeVisitor &visitor) noexcept;

    Maths::Transform Transform;
    WeakRef<Node> Parent;
    List<Ref<Node>> Children;
  };
}