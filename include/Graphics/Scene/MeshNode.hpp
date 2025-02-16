#pragma once

#include "Graphics/Handles.hpp"
#include "Graphics/PrimitiveType.hpp"
#include "Graphics/Scene/TransformNode.hpp"

namespace Krys::Gfx
{
  class MeshNode : public TransformNode
  {
  public:
    MeshNode(MeshHandle mesh, const Transform &transform = {}) noexcept
        : TransformNode(transform), _mesh(mesh)
    {
    }

    KRYS_NODE_CLASS_TYPE("mesh")

    MeshHandle GetMesh() const noexcept
    {
      return _mesh;
    }

    void SetMesh(MeshHandle mesh) noexcept
    {
      _mesh = mesh;
    }

  protected:
    MeshHandle _mesh;
  };
}