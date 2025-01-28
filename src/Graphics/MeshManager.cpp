#include "Graphics/MeshManager.hpp"
#include "Core/Debug/Macros.hpp"
#include "Graphics/Mesh.hpp"

#include <format>
#include <utility>

namespace Krys::Impl
{
  static std::pair<List<Gfx::VertexData>, List<uint32>> GetCubeData(const Gfx::Colour &colour) noexcept
  {
    List<Gfx::VertexData> vertices {
      Gfx::VertexData {{1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, colour, {0.0f, 0.0f, 0.0f}},
      Gfx::VertexData {{-1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, colour, {1.0f, 0.0f, 0.0f}},
      Gfx::VertexData {{-1.0f, -1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, colour, {1.0f, 1.0f, 0.0f}},
      Gfx::VertexData {{1.0f, -1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, colour, {0.0f, 1.0f, 0.0f}},
      Gfx::VertexData {{1.0f, -1.0f, -1.0f}, {0.0f, -1.0f, 0.0f}, colour, {0.0f, 0.0f, 0.0f}},
      Gfx::VertexData {{1.0f, -1.0f, 1.0f}, {0.0f, -1.0f, 0.0f}, colour, {1.0f, 0.0f, 0.0f}},
      Gfx::VertexData {{-1.0f, -1.0f, 1.0f}, {0.0f, -1.0f, 0.0f}, colour, {1.0f, 1.0f, 0.0f}},
      Gfx::VertexData {{-1.0f, -1.0f, -1.0f}, {0.0f, -1.0f, 0.0f}, colour, {0.0f, 1.0f, 0.0f}},
      Gfx::VertexData {{-1.0f, -1.0f, -1.0f}, {-1.0f, 0.0f, 0.0f}, colour, {0.0f, 0.0f, 0.0f}},
      Gfx::VertexData {{-1.0f, -1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}, colour, {1.0f, 0.0f, 0.0f}},
      Gfx::VertexData {{-1.0f, 1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}, colour, {1.0f, 1.0f, 0.0f}},
      Gfx::VertexData {{-1.0f, 1.0f, -1.0f}, {-1.0f, 0.0f, 0.0f}, colour, {0.0f, 1.0f, 0.0f}},
      Gfx::VertexData {{-1.0f, 1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, colour, {0.0f, 0.0f, 0.0f}},
      Gfx::VertexData {{1.0f, 1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, colour, {1.0f, 0.0f, 0.0f}},
      Gfx::VertexData {{1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, colour, {1.0f, 1.0f, 0.0f}},
      Gfx::VertexData {{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, colour, {0.0f, 1.0f, 0.0f}},
      Gfx::VertexData {{1.0f, 1.0f, -1.0f}, {1.0f, 0.0f, 0.0f}, colour, {0.0f, 0.0f, 0.0f}},
      Gfx::VertexData {{1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, colour, {1.0f, 0.0f, 0.0f}},
      Gfx::VertexData {{1.0f, -1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, colour, {1.0f, 1.0f, 0.0f}},
      Gfx::VertexData {{1.0f, -1.0f, -1.0f}, {1.0f, 0.0f, 0.0f}, colour, {0.0f, 1.0f, 0.0f}},
      Gfx::VertexData {{-1.0f, 1.0f, -1.0f}, {0.0f, 1.0f, 0.0f}, colour, {0.0f, 0.0f, 0.0f}},
      Gfx::VertexData {{-1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, colour, {1.0f, 0.0f, 0.0f}},
      Gfx::VertexData {{1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, colour, {1.0f, 1.0f, 0.0f}},
      Gfx::VertexData {{1.0f, 1.0f, -1.0f}, {0.0f, 1.0f, 0.0f}, colour, {0.0f, 1.0f, 0.0f}}};

    List<uint32> indices {0,  1,  2,  0,  2,  3,  4,  5,  6,  4,  6,  7,  8,  9,  10, 8,  10, 11,
                          12, 13, 14, 12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22, 20, 22, 23};

    return {vertices, indices};
  }
}

namespace Krys::Gfx
{
  MeshManager::MeshManager(Ptr<GraphicsContext> context) noexcept : _context(context)
  {
  }

  MeshHandle MeshManager::CreateCube(const Colour &colour, bool forceUnique) noexcept
  {
    auto meshId = std::format("cube_{0}", colour);
    if (!forceUnique)
    {
      if (auto it = _loadedMeshes.find(meshId); it != _loadedMeshes.end())
        return it->second;
    }

    auto handle = _meshHandles.Next();
    auto [vertices, indices] = Impl::GetCubeData(colour);
    auto mesh = CreateMeshImpl(handle, vertices, indices);

    _meshes[handle] = {.Mesh = std::move(mesh), .Id = meshId};
    _loadedMeshes[meshId] = handle;

    return handle;
  }

  Mesh *MeshManager::GetMesh(MeshHandle handle) noexcept
  {
    auto it = _meshes.find(handle);
    return it != _meshes.end() ? it->second.Mesh.get() : nullptr;
  }

  bool MeshManager::DestroyMesh(MeshHandle handle) noexcept
  {
    auto it = _meshes.find(handle);
    if (it == _meshes.end())
      return false;

    _loadedMeshes.erase(it->second.Id);
    _meshes.erase(it);
    _meshHandles.Recycle(handle);

    return true;
  }
}