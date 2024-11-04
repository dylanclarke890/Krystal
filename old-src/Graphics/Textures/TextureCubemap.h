#pragma once

#include "Texture.h"

#include "Maths/Vector.h"

namespace Krys::Graphics
{
  class TextureCubemap : public Texture
  {
  protected:
    TextureInternalFormat _internalFormat;

  public:
    virtual ~TextureCubemap() = default;

    TextureInternalFormat GetInternalFormat() const noexcept
    {
      return _internalFormat;
    }

    virtual void SetFilterModes(TextureMinifyMode min, TextureMagnifyMode mag) noexcept = 0;
    virtual void SetMagnifyMode(TextureMagnifyMode mode) noexcept = 0;
    virtual void SetMinifyMode(TextureMinifyMode mode) noexcept = 0;

    virtual void SetTextureWrapS(TextureWrapMode mode) noexcept = 0;
    virtual void SetTextureWrapT(TextureWrapMode mode) noexcept = 0;
    virtual void SetTextureWrapR(TextureWrapMode func) noexcept = 0;
    virtual void SetTextureWrapModes(TextureWrapMode s, TextureWrapMode t, TextureWrapMode r) noexcept = 0;
    virtual void SetBorderColor(const Krys::Maths::Vec4 &color) noexcept = 0;
  };
}