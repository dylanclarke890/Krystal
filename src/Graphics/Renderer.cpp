#include "Graphics/Renderer.hpp"
#include "Graphics/MaterialManager.hpp"
#include "Graphics/MeshManager.hpp"
#include "Graphics/TextureManager.hpp"

namespace Krys::Gfx
{
  Renderer::Renderer(RenderContext ctx) noexcept : _ctx(ctx)
  {
  }

  void Renderer::Submit(const RenderCommand &command) noexcept
  {
    _commands.push_back(command);
  }
}