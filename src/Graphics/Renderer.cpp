#include "Graphics/Renderer.hpp"

namespace Krys::Graphics
{
  Renderer::Renderer(Ptr<GraphicsContext> context) noexcept : _context(std::move(context))
  {
  }
}