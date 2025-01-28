#pragma once

#include "Base/Attributes.hpp"
#include "Base/Types.hpp"
#include "Graphics/Entities/RenderEntity.hpp"
#include "Graphics/Transform.hpp"
#include "MTL/Matrices/Mat4x4.hpp"
#include "MTL/Vectors/Vec3.hpp"

namespace Krys::Gfx
{
  class SingleRenderEntity : public RenderEntity
  {
  public:
    ~SingleRenderEntity() override = default;

    /// @brief Constructs a single render entity.
    /// @param mesh The mesh handle.
    /// @param position The position of the render entity.
    /// @param hasTransparency Whether the render entity has transparency.
    /// @param primitive The primitive type.
    SingleRenderEntity(MeshHandle mesh, const Vec3 &position, bool hasTransparency = false,
                       PrimitiveType primitive = PrimitiveType::Triangles) noexcept;

    /// @brief Constructs a single render entity.
    /// @param mesh The mesh handle.
    /// @param transform The transform of the render entity.
    /// @param hasTransparency Whether the render entity has transparency.
    /// @param primitive The primitive type.
    SingleRenderEntity(MeshHandle mesh, const Transform &transform, bool hasTransparency = false,
                       PrimitiveType primitive = PrimitiveType::Triangles) noexcept;

    /// @brief Get the transform of the render entity.
    NO_DISCARD const Transform &GetTransform() const noexcept;

    /// @brief Set the transform of the render entity.
    /// @param transform The new transform.
    void SetTransform(const Transform &transform) noexcept;

    /// @brief Set the transform of the render entity.
    /// @param transform The new transform matrix.
    void SetTransform(const Mat4 &transform) noexcept;

    /// @brief Get the normal matrix of the render entity.
    NO_DISCARD const Mat4 &GetNormalMatrix() const noexcept;

    /// @brief Get whether the render entity has transparency.
    NO_DISCARD bool HasTransparency() const noexcept override;

    /// @brief Set whether the render entity has transparency.
    /// @param hasTransparency Whether the render entity has transparency.
    void SetTransparency(bool hasTransparency) noexcept;

    /// @brief Get the position of the render entity.
    NO_DISCARD Vec3 GetPosition() const noexcept;

    /// @brief Set the position of the render entity.
    /// @param position The new position.
    void SetPosition(const Vec3 &position) noexcept;

    /// @brief Get the orientation of the render entity.
    NO_DISCARD Quat GetOrientation() const noexcept;

    /// @brief Set the orientation of the render entity.
    /// @param orientation The new orientation.
    void SetOrientation(const Quat &orientation) noexcept;

    /// @brief Get the scale of the render entity.
    NO_DISCARD Vec3 GetScale() const noexcept;

    /// @brief Set the scale of the render entity.
    /// @param scale The new scale.
    void SetScale(const Vec3 &scale) noexcept;

    /// @brief Set the mesh handle of the render entity.
    /// @param mesh The new mesh handle.
    void SetMesh(MeshHandle mesh) noexcept;

  private:
    Transform _transform;
    Mat4 _normals;
    bool _hasTransparency;
  };
}