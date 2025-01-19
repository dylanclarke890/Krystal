#include "Graphics/OpenGL/OpenGLMeshManager.hpp"
#include "Base/Pointers.hpp"
#include "Graphics/OpenGL/OpenGLGraphicsContext.hpp"
#include "Graphics/OpenGL/OpenGLMesh.hpp"

namespace Krys::Gfx::OpenGL
{
  OpenGLMeshManager::OpenGLMeshManager(Ptr<GraphicsContext> context) noexcept : MeshManager(context)
  {
  }

  Unique<Mesh> OpenGLMeshManager::CreateMesh(const List<VertexData> &vertices, const List<uint32> &indices,
                                             const VertexLayout &layout) noexcept
  {
    return CreateUnique<OpenGLMesh>(vertices, indices, layout,
                                    static_cast<Ptr<OpenGLGraphicsContext>>(_context));
  }
}