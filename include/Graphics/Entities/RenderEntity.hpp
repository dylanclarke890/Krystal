#pragma once

#include "Base/Attributes.hpp"
#include "Base/Types.hpp"
#include "Graphics/Entities/RenderEntityType.hpp"
#include "Graphics/Handles.hpp"
#include "Graphics/PrimitiveType.hpp"

namespace Krys::Gfx
{
  class RenderEntity
  {
  public:
    virtual ~RenderEntity() = default;

    /// @brief Get the type of the render entity.
    NO_DISCARD RenderEntityType GetType() const noexcept;

    /// @brief Get the mesh handle of the render entity.
    NO_DISCARD MeshHandle GetMesh() const noexcept;

    /// @brief Get the primitive type.
    NO_DISCARD PrimitiveType GetPrimitiveType() const noexcept;

    /// @brief Set the primitive type.
    NO_DISCARD bool ShouldRenderWithWireframe() const noexcept;

    /// @brief Set whether the render entity should be rendered with wireframe.
    /// @param wireframe Whether to render with wireframe.
    void SetWireframe(bool wireframe) noexcept;

    /// @brief Get whether the render entity should receive shadows.
    NO_DISCARD bool ShouldReceiveShadows() const noexcept;

    /// @brief Set whether the render entity should receive shadows.
    /// @param receiveShadows Whether to receive shadows.
    void SetReceiveShadows(bool receiveShadows) noexcept;

    /// @brief Get the name of the render entity.
    /// @note Can be an empty string if not set.
    NO_DISCARD const string &GetName() const noexcept;

    /// @brief Set the name of the render entity.
    /// @param name The name to set.
    void SetName(const string &name) noexcept;

    /// @brief Get whether the render entity has transparency.
    NO_DISCARD virtual bool HasTransparency() const noexcept = 0;

  protected:
    /// @brief Constructs a render entity.
    /// @param type The type of the render entity.
    /// @param mesh The mesh handle.
    /// @param primitive The primitive type.
    RenderEntity(RenderEntityType type, MeshHandle mesh, PrimitiveType primitive) noexcept;

    RenderEntity(const RenderEntity &) = delete;
    RenderEntity &operator=(const RenderEntity &) = delete;
    RenderEntity(RenderEntity &&) = delete;
    RenderEntity &operator=(RenderEntity &&) = delete;

    MeshHandle _mesh;
    RenderEntityType _type;
    PrimitiveType _primitiveType {PrimitiveType::Triangles};
    bool _wireframe {false}, _receiveShadows {true};
    string _name;
  };
}