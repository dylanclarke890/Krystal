#pragma once

#include "Core.h"

namespace Krys
{
  enum class Texture2DFormat
  {
    None = 0,
    R8,
    RGB8,
    RGBA8,
    RGBA32F
  };

  struct Texture2DSettings
  {
    uint32 Width;
    uint32 Height;
    Texture2DFormat Format;
    bool GenerateMipMaps;
  };

  class Texture2D
  {
  public:
    virtual ~Texture2D() = default;
    virtual uint32 GetWidth() const = 0;
    virtual uint32 GetHeight() const = 0;
    virtual uint32 GetRendererId() const = 0;

    virtual void Bind(uint32 slot = 0) const = 0;
    virtual void SetData(void *data, uint32 size) = 0;

    virtual void GenerateMipmaps() = 0;
  };
}