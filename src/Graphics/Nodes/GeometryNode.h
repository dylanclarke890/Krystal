#pragma once

#include "Types.h"
#include "Graphics/Mesh.h"
#include "Graphics/Material.h"
#include "Graphics/Nodes/Node.h"

namespace Krys::Graphics
{
  class GeometryNode : public Node
  {
  public:
    virtual void Accept(NodeVisitor &visitor) noexcept override;

    typedef Ref<Mesh>
        MeshRef;
    typedef Ref<Material> MatRef;
    MeshRef Mesh;
    MatRef Material;

    GeometryNode(MeshRef mesh, MatRef material)
        : Mesh(mesh), Material(material) {}
  };
}