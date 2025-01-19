#pragma once

#include "Base/Pointers.hpp"
#include "Base/Types.hpp"
#include "Graphics/Mesh.hpp"
#include "Graphics/VertexLayout.hpp"

namespace Krys::Gfx
{
  class GraphicsContext;

  class MeshManager
  {
  public:
    virtual ~MeshManager() = default;

    virtual Unique<Mesh> CreateMesh(const List<VertexData> &vertices, const List<uint32> &indices,
                                    const VertexLayout &layout = VertexLayout::Default()) noexcept = 0;

  protected:
    MeshManager(Ptr<GraphicsContext> context) noexcept;

    Ptr<GraphicsContext> _context {nullptr};
  };
}