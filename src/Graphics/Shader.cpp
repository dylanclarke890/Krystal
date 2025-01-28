#include "Graphics/Shader.hpp"

namespace Krys::Gfx
{
  Shader::Shader(ShaderHandle handle, ShaderStage stage) noexcept : _handle(handle), _stage(stage)
  {
  }

  ShaderStage Shader::GetStage() const noexcept
  {
    return _stage;
  }

  ShaderHandle Shader::GetHandle() const noexcept
  {
    return _handle;
  }
}