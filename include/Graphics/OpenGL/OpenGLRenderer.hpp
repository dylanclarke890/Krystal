#pragma once

#include "Base/Pointers.hpp"
#include "Graphics/GraphicsContext.hpp"
#include "Graphics/Renderer.hpp"

namespace Krys::Graphics::OpenGL
{
  class OpenGLRenderer : public Renderer
  {
  public:
    explicit OpenGLRenderer(Ptr<GraphicsContext> context) noexcept : Renderer(std::move(context))
    {
    }

    ~OpenGLRenderer() noexcept override = default;
  };
}