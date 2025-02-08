#pragma once

#include "Graphics/Handles.hpp"
#include "Graphics/PrimitiveType.hpp"
#include "Graphics/Scene/TransformNode.hpp"

namespace Krys::Gfx
{
  class MeshNode : public TransformNode
  {
  public:
    MeshNode(MeshHandle mesh, const Transform &transform = {},
             PrimitiveType type = PrimitiveType::Triangles) noexcept
        : TransformNode(transform), _mesh(mesh), _type(type)
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

    PrimitiveType GetType() const noexcept
    {
      return _type;
    }

    void SetType(PrimitiveType type) noexcept
    {
      _type = type;
    }

  protected:
    MeshHandle _mesh;
    PrimitiveType _type;
  };
}