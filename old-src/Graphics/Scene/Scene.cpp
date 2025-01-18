#include "Graphics/Scene/Scene.h"

namespace Krys::Gfx
{
  Scene::Scene() noexcept
      : Graph() {}

  Scene::Scene(Ref<Node> root) noexcept
      : Graph(root) {}
}
