#pragma once

#include "Base/Attributes.hpp"
#include "Base/Types.hpp"
#include "Graphics/Handles.hpp"

namespace Krys::Graphics
{
  class Pipeline
  {
  public:
    virtual ~Pipeline() noexcept = default;

    virtual void Bind() noexcept = 0;
    virtual void Unbind() noexcept = 0;

    virtual void Link() noexcept = 0;
    virtual void AddShader(ShaderHandle handle) noexcept = 0;

    NO_DISCARD PipelineHandle GetHandle() const noexcept;
    NO_DISCARD const List<ShaderHandle> &GetShaders() const noexcept;
    NO_DISCARD bool IsValid() const noexcept;
    NO_DISCARD bool IsLinked() const noexcept;

  protected:
    Pipeline() noexcept;

    bool _linked {false}, _isValid {false};
    PipelineHandle _handle;
    List<ShaderHandle> _shaders;
  };
}