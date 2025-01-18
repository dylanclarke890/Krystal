#pragma once

#include "Types.h"
#include "Graphics/Nodes/Node.h"
#include "Graphics/Scene/SceneGraph.h"

namespace Krys::Gfx
{
  class Scene
  {
  public:
    SceneGraph Graph;

  public:
    Scene() noexcept;
    Scene(Ref<Node> root) noexcept;
  };
}