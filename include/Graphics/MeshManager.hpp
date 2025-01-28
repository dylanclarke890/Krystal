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

    /// @brief Create a cube mesh. If a cube mesh with the same colour has already been created, it will be
    /// returned, unless 'forceUnique' is set to true, in which case a new cube mesh will be created each
    /// time.
    /// @param colour The colour of the cube.
    /// @param forceUnique If true, will create a new cube mesh each time.
    /// @return A handle to the cube mesh.
    NO_DISCARD MeshHandle CreateCube(const Colour &colour, bool forceUnique = false) noexcept;

    /// @brief Get a mesh by handle.
    /// @param handle The handle of the mesh.
    /// @return A pointer to the mesh if it exists, nullptr otherwise.
    NO_DISCARD Mesh *GetMesh(MeshHandle handle) noexcept;

    /// @brief Destroy a mesh by handle.
    /// @param handle The handle of the mesh.
    /// @return True if the mesh was found and destroyed, false otherwise.
    bool DestroyMesh(MeshHandle handle) noexcept;

  protected:
    MeshManager(Ptr<GraphicsContext> context) noexcept;

    struct LoadedMesh
    {
      Unique<Mesh> Mesh;
      string Id;
    };

    NO_DISCARD virtual Unique<Mesh>
      CreateMeshImpl(MeshHandle handle, const List<VertexData> &vertices, const List<uint32> &indices,
                     const VertexLayout &layout = VertexLayout::Default()) noexcept = 0;

    Ptr<GraphicsContext> _context {nullptr};
    MeshHandleMap<LoadedMesh> _meshes {};
    MeshHandleManager _meshHandles {};
    Map<string, MeshHandle> _loadedMeshes {};
  };
}