#pragma once

#include "Krystal.h"

namespace Krys
{
  class Texture2D
  {
  public:
    virtual ~Texture2D() = default;
    virtual uint32 GetWidth() const = 0;
    virtual uint32 GetHeight() const = 0;

    virtual void Bind(uint32 slot = 0) const = 0;
    virtual void SetData(void *data, uint32 size) = 0;

    virtual void GenerateMipmaps() = 0;
  };
}