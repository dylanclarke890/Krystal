#pragma once

#include "Graphics/Lights/AmbientLight.hpp"
#include "Graphics/Scene/GlobalLightNode.hpp"
#include "Graphics/Scene/GlobalLightType.hpp"

namespace Krys::Gfx
{
  class AmbientLightNode : public GlobalLightNode
  {
  public:
    AmbientLightNode(AmbientLight &light) noexcept : GlobalLightNode(GlobalLightType::Ambient), _light(light)
    {
    }

    virtual ~AmbientLightNode() noexcept = default;

    AmbientLight &GetLight() noexcept
    {
      return _light;
    }

    const AmbientLight &GetLight() const noexcept
    {
      return _light;
    }

  protected:
    AmbientLight &_light;
  };
}