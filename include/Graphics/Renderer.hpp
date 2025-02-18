#pragma once

#include "Base/Pointers.hpp"
#include "Graphics/GraphicsContext.hpp"
#include "Graphics/RenderContext.hpp"
#include "Graphics/RenderPass.hpp"
#include "Graphics/RenderPipeline.hpp"

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

    virtual void Render() noexcept = 0;

    void SetRenderPipeline(RenderPipeline pipeline) noexcept;

  protected:
    Renderer(const RenderContext &ctx) noexcept;

    virtual void OnRenderPipelineChange() noexcept;

    virtual void BeforeRender() noexcept;

    virtual void AfterRender() noexcept;

    virtual void BeforeRenderPass(const RenderPass &pass) noexcept;

    virtual void AfterRenderPass(const RenderPass &pass) noexcept;

    RenderContext _ctx;
    RenderPipeline _pipeline;
  };
}