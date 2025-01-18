#include "Graphics/OpenGL/OpenGLRenderer.hpp"

namespace Krys::Gfx::OpenGL
{
  OpenGLRenderer::OpenGLRenderer(Ptr<GraphicsContext> context) noexcept : Renderer(std::move(context))
  {
  }
}