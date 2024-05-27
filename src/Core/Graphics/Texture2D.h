#pragma once

#include "Core.h"

namespace Krys
{
  enum class TextureType
  {
    None = 0,
    Diffuse,
    Specular,
    Emission
  };

  enum class TextureMagnifyMode : ushort
  {
    None = 0,
    Nearest,
    Linear
  };

  enum class TextureMinifyMode : ushort
  {
    None = 0,
    Nearest,
    NearestMipmapNearest,
    NearestMipmapLinear,
    Linear,
    LinearMipmapNearest,
    LinearMipmapLinear,
  };

  enum class TextureWrapMode : ushort
  {
    None = 0,
    Repeat,
    MirroredRepeat,
    ClampToEdge,
    MirroredClampToEdge,
    ClampToBorder
  };

  enum class Texture2DFormat
  {
    None = 0,
    R8,
    RGB8,
    RGBA8,
    RGBA32F
  };

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
    virtual void SetData(void *data, uint32 size) noexcept = 0;

    virtual void SetFilterModes(TextureMinifyMode min, TextureMagnifyMode mag) noexcept = 0;
    virtual void SetMagnifyMode(TextureMagnifyMode mode) noexcept = 0;
    virtual void SetMinifyMode(TextureMinifyMode mode) noexcept = 0;

    virtual void SetTextureWrapS(TextureWrapMode mode) noexcept = 0;
    virtual void SetTextureWrapT(TextureWrapMode mode) noexcept = 0;
    virtual void SetTextureWrapModes(TextureWrapMode s, TextureWrapMode t) noexcept = 0;
    // TODO: are we converting this class to a generic texture class? This is needed if so
    // virtual void SetTextureWrapR(TextureWrapFunc func) = 0;

    virtual void GenerateMipmaps(TextureMinifyMode mode = TextureMinifyMode::LinearMipmapLinear) noexcept = 0;
  };
}