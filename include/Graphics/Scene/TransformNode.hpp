#pragma once

#include "Base/Pointers.hpp"
#include "Base/Types.hpp"
#include "Graphics/Scene/Node.hpp"

namespace Krys::Gfx
{
  class TransformNode : public Node
  {
  public:
    TransformNode(const Transform &localTransform = {}) noexcept
        : _localTransform(localTransform), _worldTransform()
    {
    }

    virtual ~TransformNode() noexcept = default;

    const Transform &GetLocalTransform() const noexcept
    {
      return _localTransform;
    }

    Transform &GetLocalTransform() noexcept
    {
      return _localTransform;
    }

    Transform ComputeWorldTransform(const Transform &parentWorldTransform) noexcept override
    {
      _worldTransform = parentWorldTransform * _localTransform;
      return _worldTransform;
    }

  protected:
    Transform _localTransform;
    Transform _worldTransform;
  };
}
