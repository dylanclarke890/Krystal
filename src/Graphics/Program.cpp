#include "Graphics/Program.hpp"

namespace Krys::Gfx
{
  Program::Program() noexcept : _handle()
  {
  }

  ProgramHandle Program::GetHandle() const noexcept
  {
    return _handle;
  }

  const List<ShaderHandle> &Program::GetShaders() const noexcept
  {
    return _shaders;
  }

  bool Program::IsValid() const noexcept
  {
    return _isValid;
  }

  bool Program::IsLinked() const noexcept
  {
    return _linked;
  }
}