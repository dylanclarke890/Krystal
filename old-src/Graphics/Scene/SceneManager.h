#pragma once

#include "Types.h"
#include "Graphics/Renderer.h"
#include "Graphics/Scene/Scene.h"
#include "Graphics/NodeVisitors/NodeVisitor.h"

namespace Krys::Gfx
{
  class SceneManager
  {
  private:
    Unique<Scene> _currentScene;
    List<Unique<NodeVisitor>> _visitors;
    Ref<Renderer> _renderer;

  public:
    SceneManager(Ref<Renderer> renderer) noexcept;
    void ChangeTo(Unique<Scene> scene) noexcept;
    void AddVisitor(Unique<NodeVisitor> visitor) noexcept;
    void UpdateScene() noexcept;

  private:
    void Traverse(Ref<Node> node) noexcept;
  };
}