#include "Graphics/Material.hpp"
#include "Core/Debug/Macros.hpp"

namespace Krys::Gfx
{
  MaterialHandle Material::GetHandle() const noexcept
  {
    return _handle;
  }

  ProgramHandle Material::GetProgram() const noexcept
  {
    return _program;
  }

  UniformHandle Material::GetUniform(const string &name) const noexcept
  {
    const auto &it = _uniforms.find(name);
    KRYS_ASSERT(it != _uniforms.end(), "Material: Uniform '{0}' not found.", name);

    if (it != _uniforms.end())
      return it->second;

    return {};
  }

  TextureHandle Material::GetTexture(const string &name) const noexcept
  {
    const auto &it = _textures.find(name);
    KRYS_ASSERT(it != _textures.end(), "Material: Texture '{0}' not found.", name);

    if (it != _textures.end())
      return it->second;

    return {};
  }
}