#pragma once

#include "Texture.h"

#include "Maths/Maths.h"

namespace Krys
{
  class TextureCubemap : public Texture
  {
  protected:
    TextureInternalFormat InternalFormat;

  public:
    virtual ~TextureCubemap() = default;

    TextureInternalFormat GetInternalFormat() const noexcept
    {
      return InternalFormat;
    }

    virtual void SetFilterModes(TextureMinifyMode min, TextureMagnifyMode mag) noexcept = 0;
    virtual void SetMagnifyMode(TextureMagnifyMode mode) noexcept = 0;
    virtual void SetMinifyMode(TextureMinifyMode mode) noexcept = 0;

    virtual void SetTextureWrapS(TextureWrapMode mode) noexcept = 0;
    virtual void SetTextureWrapT(TextureWrapMode mode) noexcept = 0;
    virtual void SetTextureWrapR(TextureWrapMode func) noexcept = 0;
    virtual void SetTextureWrapModes(TextureWrapMode s, TextureWrapMode t, TextureWrapMode r) noexcept = 0;
    virtual void SetBorderColor(const Vec4 &color) noexcept = 0;
  };
}