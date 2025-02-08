#pragma once

#include "Graphics/Lights/PointLight.hpp"
#include "Graphics/Scene/PositionalLightNode.hpp"
#include "Graphics/Scene/PositionalLightType.hpp"

namespace Krys::Gfx
{
  class PointLightNode : public PositionalLightNode
  {
  public:
    PointLightNode(PointLight &light, const Transform &transform) noexcept
        : PositionalLightNode(PositionalLightType::Point, transform), _light(light)
    {
    }

    KRYS_NODE_CLASS_TYPE("point-light")

    virtual ~PointLightNode() noexcept = default;

    PointLight &GetLight() noexcept
    {
      return _light;
    }

    const PointLight &GetLight() const noexcept
    {
      return _light;
    }

  protected:
    PointLight &_light;
  };
}