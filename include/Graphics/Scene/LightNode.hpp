#pragma once

#include "Graphics/Handles.hpp"
#include "Graphics/Scene/TransformNode.hpp"

namespace Krys::Gfx
{
  class LightNode : public TransformNode
  {
  public:
    LightNode(LightHandle light) noexcept : _light(light)
    {
    }

    KRYS_NODE_CLASS_TYPE("light")

    virtual ~LightNode() noexcept = default;

    LightHandle GetLight() const noexcept
    {
      return _light;
    }

    void SetLight(LightHandle light) noexcept
    {
      _light = light;
    }

    virtual bool IsLeafOnly() const noexcept override
    {
      return true;
    }

  protected:
    LightHandle _light;
  };
}