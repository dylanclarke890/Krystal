#pragma once

#include "Base/Attributes.hpp"
#include "Base/Types.hpp"
#include "Graphics/Handles.hpp"

namespace Krys::Gfx
{
  class Material
  {
  public:
    virtual ~Material() noexcept = default;

    NO_DISCARD MaterialHandle GetHandle() const noexcept;

    NO_DISCARD ProgramHandle GetProgram() const noexcept;

    NO_DISCARD UniformHandle GetUniform(const string &name) const noexcept;

    NO_DISCARD TextureHandle GetTexture(const string &name) const noexcept;

  protected:
    Material() noexcept = default;

    MaterialHandle _handle;
    ProgramHandle _program;
    Map<string, UniformHandle> _uniforms;
    Map<string, TextureHandle> _textures;
  };
}