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

    virtual void Bind(uint32 slot = 0) const = 0;
    virtual void SetData(void *data, uint32 size) = 0;

    virtual void GenerateMipmaps() = 0;
  };
}