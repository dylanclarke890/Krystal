#pragma once

#include "Base/Pointers.hpp"
#include "Graphics/GraphicsContext.hpp"
#include "Graphics/RenderCommand.hpp"
#include "Graphics/RenderContext.hpp"

namespace Krys::Gfx
{
  class Renderer
  {
  public:
    virtual ~Renderer() noexcept = default;

    void Submit(const RenderCommand &command) noexcept;
    virtual void Execute() noexcept = 0;

  protected:
    Renderer(RenderContext ctx) noexcept;

    RenderContext _ctx;
    List<RenderCommand> _commands {};
  };
}