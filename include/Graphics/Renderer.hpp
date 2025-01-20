#pragma once

#include "Base/Pointers.hpp"
#include "Graphics/RenderCommand.hpp"
#include "Graphics/GraphicsContext.hpp"

namespace Krys::Gfx
{
  class MeshManager;
  class Renderer
  {
  public:
    Renderer(Ptr<MeshManager> meshManager) noexcept;
    ~Renderer() noexcept = default;

    void Submit(const RenderCommand &command) noexcept;
    void Execute(Ptr<GraphicsContext> context) noexcept;

  private:
    List<RenderCommand> _commands {};
    Ptr<MeshManager> _meshManager{nullptr};
  };
}