#pragma once

#include "Base/Pointers.hpp"
#include "Base/Types.hpp"
#include "Graphics/Lights/AmbientLight.hpp"
#include "Graphics/Lights/DirectionalLight.hpp"
#include "Graphics/Lights/PointLight.hpp"

namespace Krys::Gfx
{
  /// @brief A lighting rig is a collection of lights that can be used to light a scene.
  struct LightingRig
  {
    /// @brief Ambient lighting.
    Unique<AmbientLight> Ambient;

    /// @brief Collection of directional lights.
    List<Unique<DirectionalLight>> DirectionalLights;

    /// @brief Collection of point lights.
    List<Unique<PointLight>> PointLights;
  };
}