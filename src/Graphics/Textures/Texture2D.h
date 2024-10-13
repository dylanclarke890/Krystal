#pragma once

#include "Texture.h"

#include "Maths/Vector.h"

namespace Krys::Graphics
{
  class Texture2D : public Texture
  {
  protected:
    uint32 _samples;
    TextureType _type;
    TextureInternalFormat _internalFormat;
    uint _width, _height;
    string _path;

  public:
    virtual ~Texture2D() = default;

    NO_DISCARD TextureType GetType() const noexcept
    {
      return _type;
    }

    NO_DISCARD TextureInternalFormat GetInternalFormat() const noexcept
    {
      return _internalFormat;
    }

    NO_DISCARD uint32 GetWidth() const noexcept
    {
      return _width;
    }

    NO_DISCARD uint32 GetHeight() const noexcept
    {
      return _height;
    }

    NO_DISCARD bool IsMultisampled() const noexcept
    {
      return _samples > 1;
    }

    virtual void SetFilterModes(TextureMinifyMode min, TextureMagnifyMode mag) noexcept = 0;
    virtual void SetMagnifyMode(TextureMagnifyMode mode) noexcept = 0;
    virtual void SetMinifyMode(TextureMinifyMode mode) noexcept = 0;

    virtual void SetTextureWrapS(TextureWrapMode mode) noexcept = 0;
    virtual void SetTextureWrapT(TextureWrapMode mode) noexcept = 0;
    virtual void SetTextureWrapModes(TextureWrapMode s, TextureWrapMode t) noexcept = 0;

    virtual void SetBorderColor(const Krys::Maths::Vec4 &color) noexcept = 0;
    virtual void GenerateMipmaps(TextureMinifyMode mode = TextureMinifyMode::LinearMipmapLinear) noexcept = 0;
  };
}