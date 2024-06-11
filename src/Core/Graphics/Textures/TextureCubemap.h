#pragma once

#include "Texture.h"

namespace Krys
{
  class TextureCubemap
  {
  protected:
    uint Id;
    TextureInternalFormat InternalFormat;

  public:
    virtual ~TextureCubemap() = default;

    uint GetId() const noexcept
    {
      return Id;
    }

    TextureInternalFormat GetInternalFormat() const noexcept
    {
      return InternalFormat;
    }

    virtual void Bind(uint32 slot = 0) const noexcept = 0;

    virtual void SetFilterModes(TextureMinifyMode min, TextureMagnifyMode mag) noexcept = 0;
    virtual void SetMagnifyMode(TextureMagnifyMode mode) noexcept = 0;
    virtual void SetMinifyMode(TextureMinifyMode mode) noexcept = 0;

    virtual void SetTextureWrapS(TextureWrapMode mode) noexcept = 0;
    virtual void SetTextureWrapT(TextureWrapMode mode) noexcept = 0;
    virtual void SetTextureWrapR(TextureWrapMode func) noexcept = 0;
    virtual void SetTextureWrapModes(TextureWrapMode s, TextureWrapMode t, TextureWrapMode r) noexcept = 0;
  };
}