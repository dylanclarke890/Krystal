#include "Graphics/OpenGL/OpenGLRenderer.hpp"

namespace Krys::Graphics::OpenGL
{
  OpenGLRenderer::OpenGLRenderer(Ptr<GraphicsContext> context) noexcept : Renderer(std::move(context))
  {
  }
}