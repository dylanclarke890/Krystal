#include "Graphics/Entities/SingleRenderEntity.hpp"
#include "MTL/Matrices/Ext/Inverse.hpp"
#include "MTL/Matrices/Ext/Transpose.hpp"

namespace Krys::Gfx
{
  static Mat4 CalculateNormalMatrix(const Mat4 &model) noexcept
  {
    auto normal = MTL::Transpose(MTL::Inverse(model));
    normal[3] = {0.0f, 0.0f, 0.0f, 1.0f};
    return normal;
  }

  SingleRenderEntity::SingleRenderEntity(MeshHandle mesh, const Vec3 &position, bool hasTransparency,
                                         PrimitiveType primitive) noexcept
      : SingleRenderEntity(mesh, Transform {position, Quat {}, {1.0f}}, hasTransparency, primitive)
  {
  }

  SingleRenderEntity::SingleRenderEntity(MeshHandle mesh, const Transform &transform, bool hasTransparency,
                                         PrimitiveType primitive) noexcept
      : RenderEntity(RenderEntityType::Single, mesh, primitive), _transform(transform),
        _hasTransparency(hasTransparency), _normals(CalculateNormalMatrix(_transform.GetMatrix()))
  {
  }

  const Transform &SingleRenderEntity::GetTransform() const noexcept
  {
    return _transform;
  }

  void SingleRenderEntity::SetTransform(const Transform &transform) noexcept
  {
    _transform = transform;
    _normals = CalculateNormalMatrix(_transform.GetMatrix());
  }

  void SingleRenderEntity::SetTransform(const Mat4 &transform) noexcept
  {
    _transform.SetMatrix(transform);
    _normals = CalculateNormalMatrix(_transform.GetMatrix());
  }

  const Mat4 &SingleRenderEntity::GetNormalMatrix() const noexcept
  {
    return _normals;
  }

  bool SingleRenderEntity::HasTransparency() const noexcept
  {
    return _hasTransparency;
  }

  void SingleRenderEntity::SetTransparency(bool hasTransparency) noexcept
  {
    _hasTransparency = hasTransparency;
  }

  Vec3 SingleRenderEntity::GetPosition() const noexcept
  {
    return _transform.GetTranslation();
  }

  void SingleRenderEntity::SetPosition(const Vec3 &position) noexcept
  {
    _transform.SetTranslation(position);
    _normals = CalculateNormalMatrix(_transform.GetMatrix());
  }

  void SingleRenderEntity::SetMesh(MeshHandle mesh) noexcept
  {
    _mesh = mesh;
  }

  Quat SingleRenderEntity::GetOrientation() const noexcept
  {
    return _transform.GetRotation();
  }

  void SingleRenderEntity::SetOrientation(const Quat &orientation) noexcept
  {
    _transform.SetRotation(orientation);
    _normals = CalculateNormalMatrix(_transform.GetMatrix());
  }

  Vec3 SingleRenderEntity::GetScale() const noexcept
  {
    return _transform.GetScale();
  }

  void SingleRenderEntity::SetScale(const Vec3 &scale) noexcept
  {
    _transform.SetScale(scale);
    _normals = CalculateNormalMatrix(_transform.GetMatrix());
  }
}
