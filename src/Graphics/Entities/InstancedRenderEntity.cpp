#include "Graphics/Entities/InstancedRenderEntity.hpp"
#include "MTL/Matrices/Ext/Inverse.hpp"
#include "MTL/Matrices/Ext/Transpose.hpp"

namespace Krys::Gfx
{
  static Mat4 GetNormalMatrix(const Mat4 &model) noexcept
  {
    auto normal = MTL::Transpose(MTL::Inverse(model));
    normal[3] = {0.0f, 0.0f, 0.0f, 1.0f};
    return normal;
  }

  InstancedRenderEntity::InstancedRenderEntity(MeshHandle mesh, const List<Transform> &transforms,
                                               PrimitiveType primitive) noexcept
      : RenderEntity(RenderEntityType::Instanced, mesh, primitive), _data(transforms.size() * 2),
        _instanceCount(transforms.size())
  {
    for (const auto &transform : transforms)
    {
      auto model = transform.GetMatrix();
      auto normal = GetNormalMatrix(model);
      _data.emplace_back(model);
      _data.emplace_back(normal);
    }
  }

  bool InstancedRenderEntity::HasTransparency() const noexcept
  {
    return false;
  }

  const List<Mat4> &InstancedRenderEntity::GetInstanceData() const noexcept
  {
    return _data;
  }

  size_t InstancedRenderEntity::GetInstanceCount() const noexcept
  {
    return _instanceCount;
  }
}