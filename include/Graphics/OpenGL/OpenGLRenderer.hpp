#pragma once

#include "Base/Pointers.hpp"
#include "Graphics/GraphicsContext.hpp"
#include "Graphics/Renderer.hpp"

namespace Krys::Gfx::OpenGL
{
  class OpenGLRenderer : public Renderer
  {
  public:
    explicit OpenGLRenderer(Ptr<GraphicsContext> context) noexcept;
    ~OpenGLRenderer() noexcept override = default;
  };
}