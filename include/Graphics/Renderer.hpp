#pragma once

#include "Base/Pointers.hpp"
#include "Graphics/GraphicsContext.hpp"
#include "Graphics/RenderContext.hpp"

namespace Krys::Gfx
{
  class SceneGraph;
  class Camera;
  class Node;
  class Transform;

  class Renderer
  {
  public:
    virtual ~Renderer() noexcept = default;

    virtual void Init() noexcept = 0;

    void Render(SceneGraph *scene, Camera &camera) noexcept;

  protected:
    virtual void BeforeRender() noexcept;

    virtual void Render(Node *node, const Transform &parentTransform, Camera &camera) noexcept = 0;

    Renderer(RenderContext ctx) noexcept;

    RenderContext _ctx;
  };
}