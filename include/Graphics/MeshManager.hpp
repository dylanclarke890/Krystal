#pragma once

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

    virtual MeshHandle CreateMesh(const List<VertexData> &vertices, const List<uint32> &indices,
                                  const VertexLayout &layout = VertexLayout::Default()) noexcept = 0;

    Mesh &GetMesh(MeshHandle handle) noexcept;

    void DestroyMesh(MeshHandle handle) noexcept;

  protected:
    MeshManager(Ptr<GraphicsContext> context) noexcept;

    Ptr<GraphicsContext> _context {nullptr};
    Map<MeshHandle, Unique<Mesh>, MeshHandle::Hash> _meshes;
    MeshHandle _nextHandle {0};
  };
}