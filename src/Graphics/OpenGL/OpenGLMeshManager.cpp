#include "Graphics/OpenGL/OpenGLMeshManager.hpp"
#include "Base/Pointers.hpp"
#include "Graphics/OpenGL/OpenGLGraphicsContext.hpp"
#include "Graphics/OpenGL/OpenGLMesh.hpp"

namespace Krys::Gfx::OpenGL
{
  OpenGLMeshManager::OpenGLMeshManager(Ptr<GraphicsContext> context) noexcept : MeshManager(context)
  {
  }

  MeshHandle OpenGLMeshManager::CreateMesh(const List<VertexData> &vertices, const List<uint32> &indices,
                                           const VertexLayout &layout) noexcept
  {
    auto handle = _nextHandle;
    _nextHandle = MeshHandle(_nextHandle.Id() + 1);

    auto mesh =
      CreateUnique<OpenGLMesh>(vertices, indices, layout, static_cast<Ptr<OpenGLGraphicsContext>>(_context));
    mesh->_handle = handle;

    _meshes[handle] = std::move(mesh);

    return handle;
  }
}