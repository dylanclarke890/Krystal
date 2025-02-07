#pragma once

#include "Graphics/Scene/GlobalLightType.hpp"
#include "Graphics/Scene/Node.hpp"

namespace Krys::Gfx
{
  class GlobalLightNode : public Node
  {
  public:
    GlobalLightNode(GlobalLightType type) noexcept : _type(type)
    {
    }

    virtual ~GlobalLightNode() noexcept = default;

    virtual bool IsLeafOnly() const noexcept override
    {
      return true;
    }

    GlobalLightType GetType() const noexcept
    {
      return _type;
    }

  protected:
    GlobalLightType _type;
  };
}