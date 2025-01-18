#include "Graphics/Renderer.hpp"

namespace Krys::Gfx
{
  Renderer::Renderer(Ptr<GraphicsContext> context) noexcept : _context(std::move(context))
  {
  }
}