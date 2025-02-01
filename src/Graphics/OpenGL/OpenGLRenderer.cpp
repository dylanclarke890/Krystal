#include "Graphics/OpenGL/OpenGLRenderer.hpp"
#include "Graphics/OpenGL/OpenGLGraphicsContext.hpp"
#include "Graphics/OpenGL/OpenGLMesh.hpp"
#include "Graphics/OpenGL/OpenGLMeshManager.hpp"
#include "Graphics/OpenGL/OpenGLProgram.hpp"
#include "Graphics/OpenGL/OpenGLTexture.hpp"
#include "Graphics/OpenGL/OpenGLTextureManager.hpp"

namespace Krys::Gfx::OpenGL
{
  OpenGLRenderer::OpenGLRenderer(RenderContext context) noexcept : Renderer(context)
  {
  }

  void OpenGLRenderer::Execute() noexcept
  {
    for (const auto &command : _commands)
    {
      auto& program = static_cast<OpenGLProgram&>(*_ctx.GraphicsContext->GetProgram(command.Program));
      program.Bind();

      KRYS_ASSERT(command.Mesh.IsValid(), "Mesh was not provided.");
      KRYS_ASSERT(command.Material.IsValid(), "Material was not provided.");

      auto &mesh = *_ctx.MeshManager->GetMesh(command.Mesh);

      auto &material = *_ctx.MaterialManager->GetMaterial(command.Material);
      switch (material.GetType())
      {
      case MaterialType::Phong:
        {
          auto &phong = static_cast<PhongMaterial &>(material);
          auto &texture =
            static_cast<OpenGLTexture &>(*_ctx.TextureManager->GetTexture(phong.GetAmbientTexture()));

          SetMaterialProperty(program.GetNativeHandle(), "u_Texture", texture.GetNativeBindlessHandle());
          SetMaterialProperty(program.GetNativeHandle(), "u_AmbientColour", phong.GetAmbientColour());
          break;
        }
        default: KRYS_ASSERT(false, "Unknown material type."); break;
      }

      mesh.Bind();
      if (mesh.IsIndexed())
        _ctx.GraphicsContext->DrawElements(command.Type, static_cast<uint32>(mesh.GetCount()));
      else
        _ctx.GraphicsContext->DrawArrays(command.Type, static_cast<uint32>(mesh.GetCount()));
    }

    _commands.clear();
  }
}