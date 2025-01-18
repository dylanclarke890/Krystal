#include "Graphics/Shader.hpp"

namespace Krys::Gfx
{
  Shader::Shader(const ShaderDescription &description) noexcept
      : _stage(description.Stage), _handle(ShaderHandle::InvalidHandle)
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