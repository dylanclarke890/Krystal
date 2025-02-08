#pragma once

#include "Base/Pointers.hpp"
#include "Base/Types.hpp"
#include "Graphics/Scene/Node.hpp"

namespace Krys::Gfx
{
  class TransformNode : public Node
  {
  public:
    TransformNode(const Transform &localTransform = {}) noexcept : _localTransform(localTransform)
    {
    }

    KRYS_NODE_CLASS_TYPE("transform")

    virtual ~TransformNode() noexcept = default;

    const Transform &GetLocalTransform() const noexcept override
    {
      return _localTransform;
    }

  protected:
    Transform _localTransform;
  };
}
