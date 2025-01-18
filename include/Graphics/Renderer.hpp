#pragma once

#include "Base/Pointers.hpp"
#include "Graphics/GraphicsContext.hpp"

namespace Krys::Graphics
{
  class Renderer
  {
  public:
    Renderer() = delete;
    virtual ~Renderer() noexcept = default;

  protected:
    explicit Renderer(Ptr<GraphicsContext> context) noexcept;

    Ptr<GraphicsContext> _context {nullptr};
  };
}