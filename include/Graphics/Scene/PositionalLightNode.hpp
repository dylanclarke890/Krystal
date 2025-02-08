#pragma once

#include "Graphics/Scene/PositionalLightType.hpp"
#include "Graphics/Scene/TransformNode.hpp"

namespace Krys::Gfx
{
  class PositionalLightNode : public TransformNode
  {
  public:
    PositionalLightNode(PositionalLightType type, const Transform &transform = {}) noexcept
        : TransformNode(transform), _type(type)
    {
    }

    KRYS_NODE_CLASS_TYPE("positional-light")

    virtual ~PositionalLightNode() noexcept = default;

    PositionalLightType GetType() const noexcept
    {
      return _type;
    };

  protected:
    PositionalLightType _type;
  };
}