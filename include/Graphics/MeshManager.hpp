#pragma once

#include "Base/Attributes.hpp"
#include "Base/Pointers.hpp"
#include "Base/Types.hpp"
#include "Graphics/Handles.hpp"
#include "Graphics/Mesh.hpp"
#include "Graphics/VertexLayout.hpp"

namespace Krys::Gfx
{
  class GraphicsContext;

  class MeshManager
  {
  public:
    virtual ~MeshManager() = default;

    NO_DISCARD virtual MeshHandle
      CreateMesh(const List<VertexData> &vertices, const List<uint32> &indices,
                 const VertexLayout &layout = VertexLayout::Default()) noexcept = 0;

    NO_DISCARD MeshHandle CreateCube(const Colour &colour) noexcept;

    NO_DISCARD MeshHandle UniqueCube(const Colour &colour) noexcept;

    NO_DISCARD Mesh &GetMesh(MeshHandle handle) noexcept;

    void DestroyMesh(MeshHandle handle) noexcept;

  protected:
    MeshManager(Ptr<GraphicsContext> context) noexcept;

    Ptr<GraphicsContext> _context {nullptr};
    Map<MeshHandle, Unique<Mesh>, MeshHandle::Hash> _meshes;
    Map<string, MeshHandle> _loadedMeshes;

    MeshHandle _nextHandle {0};
  };
}