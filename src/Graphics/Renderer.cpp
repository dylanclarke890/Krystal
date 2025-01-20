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

      if (!command.VBO.IsValid())
      {
        KRYS_ASSERT(command.Mesh.IsValid(), "Mesh must be provided if VBO is not");
        auto &mesh = _meshManager->GetMesh(command.Mesh);

        mesh.Bind();
        if (mesh.IsIndexed())
        {
          context->DrawElements(command.Type, static_cast<uint32>(mesh.GetCount()));
        }
        else
        {
          context->DrawArrays(command.Type, static_cast<uint32>(mesh.GetCount()));
        }
      }
      else
      {
        auto &vertexBuffer = context->GetVertexBuffer(command.VBO);
        vertexBuffer.Bind();

        if (command.EBO.IsValid())
        {
          auto &indexBuffer = context->GetIndexBuffer(command.EBO);
          indexBuffer.Bind();
          context->DrawElements(command.Type, command.Count);
        }
        else
        {
          context->DrawArrays(command.Type, command.Count);
        }
      }
    }

    _commands.clear();
  }
}