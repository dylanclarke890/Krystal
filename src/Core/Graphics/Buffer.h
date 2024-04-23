#pragma once

#include "Krystal.h"

namespace Krys
{
  class IndexBuffer
  {
  public:
    virtual ~IndexBuffer() = default;

    virtual void Bind() = 0;
    virtual void Unbind() = 0;

    // TODO: implement this?
    // virtual void Set(uint32* indices, uint32 count) = 0;

    virtual uint Size() = 0;
  };

  // TODO: implement
  class VertexBuffer
  {
  };
}