#pragma once

#include "Base/Pointers.hpp"
#include "Graphics/Handles.hpp"
#include "Graphics/Mesh.hpp"
#include "Graphics/MeshManager.hpp"
#include "Graphics/VertexLayout.hpp"

namespace Krys::Gfx::OpenGL
{
  class OpenGLMeshManager : public MeshManager
  {
  public:
    OpenGLMeshManager(Ptr<GraphicsContext> context) noexcept;

    NO_DISCARD MeshHandle CreateMesh(const List<VertexData> &vertices, const List<uint32> &indices,
                                     const VertexLayout &layout) noexcept override;
  };
}