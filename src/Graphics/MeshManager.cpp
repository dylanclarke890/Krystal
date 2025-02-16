#include "Graphics/MeshManager.hpp"
#include "Debug/Macros.hpp"
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

    _meshes[handle] = {.Mesh = CreateMeshImpl(handle, vertices, indices), .Id = meshId};
    _loadedMeshes[meshId] = handle;

    return handle;
  }

  MeshHandle MeshManager::CreateMesh(const string &name, const List<VertexData> &vertices,
                                     const List<uint32> &indices, const VertexLayout &layout) noexcept
  {
    auto handle = _meshHandles.Next();
    _meshes[handle] = {.Mesh = CreateMeshImpl(handle, vertices, indices, layout), .Id = name};
    return handle;
  }

  Mesh *MeshManager::GetMesh(MeshHandle handle) noexcept
  {
    if (auto it = _meshes.find(handle); it != _meshes.end())
      return it->second.Mesh.get();
    return nullptr;
  }

  bool MeshManager::DestroyMesh(MeshHandle handle) noexcept
  {
    if (auto it = _meshes.find(handle); it != _meshes.end())
    {
      _loadedMeshes.erase(it->second.Id);
      _meshes.erase(it);
      _meshHandles.Recycle(handle);
      return true;
    }

    return false;
  }
}