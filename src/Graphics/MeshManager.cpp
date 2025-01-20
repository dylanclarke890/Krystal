#include "Graphics/MeshManager.hpp"
#include "Core/Debug/Macros.hpp"
#include "Graphics/Mesh.hpp"

namespace Krys::Gfx
{
  MeshManager::MeshManager(Ptr<GraphicsContext> context) noexcept : _context(context)
  {
  }

  Mesh &MeshManager::GetMesh(MeshHandle handle) noexcept
  {
    auto it = _meshes.find(handle);
    KRYS_ASSERT(it != _meshes.end(), "Mesh not found");
    return *it->second;
  }

  void MeshManager::DestroyMesh(MeshHandle handle) noexcept
  {
    auto it = _meshes.find(handle);
    KRYS_ASSERT(it != _meshes.end(), "Mesh not found");
    _meshes.erase(it);
  }
}