#include "Graphics/Materials/Material.hpp"
#include "Core/Debug/Macros.hpp"

namespace Krys::Gfx
{
  Material::Material(MaterialType type, MaterialHandle handle, ProgramHandle program) noexcept
      : _handle(handle), _program(program), _type(type)
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
}