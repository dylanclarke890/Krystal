#include "Graphics/Scene/Scene.h"

namespace Krys::Graphics
{
  Scene::Scene() noexcept
      : Graph() {}

  Scene::Scene(Ref<Node> root) noexcept
      : Graph(root) {}
}
