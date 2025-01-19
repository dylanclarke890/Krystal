#include "Graphics/Renderer.hpp"

namespace Krys::Gfx
{
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
        auto mesh = command.Mesh;
        KRYS_ASSERT(mesh != nullptr, "Mesh must be provided if VBO is not");
        mesh->Bind();
        if (mesh->IsIndexed())
        {
          context->DrawElements(command.Type, static_cast<uint32>(mesh->GetCount()));
        }
        else
        {
          context->DrawArrays(command.Type, static_cast<uint32>(mesh->GetCount()));
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