#include "Graphics/Entities/RenderEntity.hpp"

namespace Krys::Gfx
{
  RenderEntity::RenderEntity(RenderEntityType type, MeshHandle mesh, PrimitiveType primitive) noexcept
      : _type(type), _mesh(mesh), _primitiveType(primitive)
  {
  }

  RenderEntityType RenderEntity::GetType() const noexcept
  {
    return _type;
  }

  MeshHandle RenderEntity::GetMesh() const noexcept
  {
    return _mesh;
  }

  PrimitiveType RenderEntity::GetPrimitiveType() const noexcept
  {
    return _primitiveType;
  }

  bool RenderEntity::ShouldRenderWithWireframe() const noexcept
  {
    return _wireframe;
  }

  void RenderEntity::SetWireframe(bool wireframe) noexcept
  {
    _wireframe = wireframe;
  }

  bool RenderEntity::ShouldReceiveShadows() const noexcept
  {
    return _receiveShadows;
  }

  void RenderEntity::SetReceiveShadows(bool receiveShadows) noexcept
  {
    _receiveShadows = receiveShadows;
  }

  const string &RenderEntity::GetName() const noexcept
  {
    return _name;
  }

  void RenderEntity::SetName(const string &name) noexcept
  {
    _name = name;
  }
}
