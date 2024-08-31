#pragma once

#include "Texture.h"

#include "Maths/Maths.h"

namespace Krys
{
  class Texture2D : public Texture
  {
  protected:
    uint32 Samples;
    TextureType Type;
    TextureInternalFormat InternalFormat;
    uint Width, Height;
    string Path;

  public:
    virtual ~Texture2D() = default;

    NO_DISCARD TextureType GetType() const noexcept
    {
      return Type;
    }

    NO_DISCARD TextureInternalFormat GetInternalFormat() const noexcept
    {
      return InternalFormat;
    }

    NO_DISCARD uint32 GetWidth() const noexcept
    {
      return Width;
    }

    NO_DISCARD uint32 GetHeight() const noexcept
    {
      return Height;
    }

    NO_DISCARD bool IsMultisampled() const noexcept
    {
      return Samples > 1;
    }

    virtual void Bind(uint32 slot = 0) const noexcept = 0;

    virtual void SetFilterModes(TextureMinifyMode min, TextureMagnifyMode mag) noexcept = 0;
    virtual void SetMagnifyMode(TextureMagnifyMode mode) noexcept = 0;
    virtual void SetMinifyMode(TextureMinifyMode mode) noexcept = 0;

    virtual void SetTextureWrapS(TextureWrapMode mode) noexcept = 0;
    virtual void SetTextureWrapT(TextureWrapMode mode) noexcept = 0;
    virtual void SetTextureWrapModes(TextureWrapMode s, TextureWrapMode t) noexcept = 0;

    virtual void SetBorderColor(const Vec4 &color) noexcept = 0;
    virtual void GenerateMipmaps(TextureMinifyMode mode = TextureMinifyMode::LinearMipmapLinear) noexcept = 0;
  };
}