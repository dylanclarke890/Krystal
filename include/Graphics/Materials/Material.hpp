#pragma once

#include "Base/Attributes.hpp"
#include "Base/Types.hpp"
#include "Graphics/Handles.hpp"
#include "Graphics/Materials/MaterialType.hpp"
#include "MTL/Matrices/Mat4x4.hpp"
#include "MTL/Vectors/Vec2.hpp"
#include "MTL/Vectors/Vec4.hpp"

namespace Krys::Gfx
{
  class MaterialManager;

  class Material
  {
  public:
    virtual ~Material() noexcept = default;

    NO_DISCARD MaterialHandle GetHandle() const noexcept;

    NO_DISCARD ProgramHandle GetProgram() const noexcept;

    NO_DISCARD MaterialType GetType() const noexcept;

    NO_DISCARD bool IsDirty() const noexcept;

    void ClearIsDirtyFlag() noexcept;

  protected:
    friend class MaterialManager;

    Material(MaterialHandle handle, ProgramHandle program, MaterialType type) noexcept;

    MaterialHandle _handle;
    ProgramHandle _program;
    MaterialType _type;
    bool _isDirty;
  };
}