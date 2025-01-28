#pragma once

#include "Graphics/Entities/RenderEntity.hpp"
#include "Graphics/Transform.hpp"
#include "MTL/Matrices/Mat4x4.hpp"

namespace Krys::Gfx
{
  class InstancedRenderEntity : public RenderEntity
  {
  public:
    /// @brief Constructs an instanced render entity.
    /// @param mesh The mesh handle.
    /// @param transforms The list of transforms, one for each instance to draw.
    /// @param primitive The primitive type.
    InstancedRenderEntity(MeshHandle mesh, const List<Transform> &transforms,
                          PrimitiveType primitive = PrimitiveType::Triangles) noexcept;

    /// @brief Get the data needed to render the instances. A transform and normal matrix is returned for each
    /// instance.
    NO_DISCARD const List<Mat4> &GetInstanceData() const noexcept;

    /// @brief Get the amount of instances to draw.
    NO_DISCARD size_t GetInstanceCount() const noexcept;

    /// @brief Unsupported for instanced render entities.
    /// @return false
    NO_DISCARD bool HasTransparency() const noexcept override;

  protected:
    InstancedRenderEntity(const InstancedRenderEntity &) = delete;
    InstancedRenderEntity &operator=(const InstancedRenderEntity &) = delete;
    InstancedRenderEntity(InstancedRenderEntity &&) = delete;
    InstancedRenderEntity &operator=(InstancedRenderEntity &&) = delete;

    List<Mat4> _data;
    size_t _instanceCount;
  };
}