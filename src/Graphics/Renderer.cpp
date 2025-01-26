#include "Graphics/Renderer.hpp"
#include "Graphics/MeshManager.hpp"

namespace Krys::Gfx
{
  Renderer::Renderer(Ptr<MeshManager> meshManager) noexcept : _meshManager(meshManager)
  {
  }

  void Renderer::Submit(const RenderCommand &command) noexcept
  {
    _commands.push_back(command);
  }

  void Renderer::Execute(Ptr<GraphicsContext> context) noexcept
  {
    for (const auto &command : _commands)
    {
      auto &pipeline = context->GetPipeline(command.Pipeline);
      pipeline.Bind();

      KRYS_ASSERT(command.Mesh.IsValid(), "Mesh was not provided.");
      auto &mesh = _meshManager->GetMesh(command.Mesh);

      mesh.Bind();
      if (mesh.IsIndexed())
        context->DrawElements(command.Type, static_cast<uint32>(mesh.GetCount()));
      else
        context->DrawArrays(command.Type, static_cast<uint32>(mesh.GetCount()));
    }

    _commands.clear();
  }
}