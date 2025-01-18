#include "Graphics/Pipeline.hpp"

namespace Krys::Graphics
{
  Pipeline::Pipeline() noexcept : _handle(PipelineHandle::InvalidHandle)
  {
  }

  PipelineHandle Pipeline::GetHandle() const noexcept
  {
    return _handle;
  }

  const List<ShaderHandle> &Pipeline::GetShaders() const noexcept
  {
    return _shaders;
  }

  bool Pipeline::IsValid() const noexcept
  {
    return _isValid;
  }

  bool Pipeline::IsLinked() const noexcept
  {
    return _linked;
  }
}