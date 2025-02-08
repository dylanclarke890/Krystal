#pragma once

#include "Graphics/Lights/DirectionalLight.hpp"
#include "Graphics/Scene/GlobalLightNode.hpp"
#include "Graphics/Scene/GlobalLightType.hpp"

namespace Krys::Gfx
{
  class DirectionalLightNode : public GlobalLightNode
  {
  public:
    DirectionalLightNode(DirectionalLight &light) noexcept
        : GlobalLightNode(GlobalLightType::Directional), _light(light)
    {
    }

    KRYS_NODE_CLASS_TYPE("directional-light")

    virtual ~DirectionalLightNode() noexcept = default;

    DirectionalLight &GetLight() noexcept
    {
      return _light;
    }

    const DirectionalLight &GetLight() const noexcept
    {
      return _light;
    }

  protected:
    DirectionalLight &_light;
  };
}