#include "Graphics/Materials/Material.hpp"
#include "Core/Debug/Macros.hpp"

namespace Krys::Gfx
{
  Material::Material(MaterialHandle handle, ProgramHandle program, MaterialType type) noexcept
      : _handle(handle), _program(program), _type(type), _isDirty(true)
  {
  }

  MaterialHandle Material::GetHandle() const noexcept
  {
    return _handle;
  }

  ProgramHandle Material::GetProgram() const noexcept
  {
    return _program;
  }

  MaterialType Material::GetType() const noexcept
  {
    return _type;
  }

  bool Material::IsDirty() const noexcept
  {
    return _isDirty;
  }

  void Material::ClearIsDirtyFlag() noexcept
  {
    _isDirty = false;
  }
}