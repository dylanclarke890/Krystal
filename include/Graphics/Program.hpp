#pragma once

#include "Base/Attributes.hpp"
#include "Base/Types.hpp"
#include "Graphics/Handles.hpp"

namespace Krys::Gfx
{
  class Program
  {
  public:
    virtual ~Program() noexcept = default;

    virtual void Bind() noexcept = 0;
    virtual void Unbind() noexcept = 0;

    NO_DISCARD ProgramHandle GetHandle() const noexcept;
    NO_DISCARD const List<ShaderHandle> &GetShaders() const noexcept;
    NO_DISCARD bool IsValid() const noexcept;
    NO_DISCARD bool IsLinked() const noexcept;

  protected:
    Program(ProgramHandle handle) noexcept;

    ProgramHandle _handle;
    bool _linked {false}, _isValid {false};
    List<ShaderHandle> _shaders;
  };
}