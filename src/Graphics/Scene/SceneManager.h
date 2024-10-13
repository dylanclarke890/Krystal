#pragma once

#include "Types.h"
#include "Graphics/Scene/Scene.h"

namespace Krys::Graphics
{
  class SceneManager
  {
  private:
    Unique<Scene> CurrentScene;

  public:
    void SetCurrentScene(Unique<Scene> scene) noexcept
    {
      CurrentScene = std::move(scene);
    }
  };
}