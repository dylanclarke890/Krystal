#pragma once

#include "Texture.h"

namespace Krys
{
  class Texture2D
  {
  protected:
    uint Id;
    TextureType Type;
    uint Width, Height;
    const char *Path;

  public:
    virtual ~Texture2D() = default;

    uint GetId() const noexcept
    {
      return Id;
    }

    TextureType GetType() const noexcept
    {
      return Type;
    }

    uint32 GetWidth() const noexcept
    {
      return Width;
    }

    uint32 GetHeight() const noexcept
    {
      return Height;
    }

    virtual void Bind(uint32 slot = 0) const noexcept = 0;

    virtual void SetFilterModes(TextureMinifyMode min, TextureMagnifyMode mag) noexcept = 0;
    virtual void SetMagnifyMode(TextureMagnifyMode mode) noexcept = 0;
    virtual void SetMinifyMode(TextureMinifyMode mode) noexcept = 0;

    virtual void SetTextureWrapS(TextureWrapMode mode) noexcept = 0;
    virtual void SetTextureWrapT(TextureWrapMode mode) noexcept = 0;
    virtual void SetTextureWrapModes(TextureWrapMode s, TextureWrapMode t) noexcept = 0;

    virtual void GenerateMipmaps(TextureMinifyMode mode = TextureMinifyMode::LinearMipmapLinear) noexcept = 0;
  };
}