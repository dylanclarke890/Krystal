#pragma once

#include "Krystal.h"
#include "GL.h"
#include "Graphics/Buffer.h"
#include "Graphics/GraphicsContext.h"

namespace Krys
{
  class GLIndexBuffer : public IndexBuffer
  {
  private:
    GLRendererId Id;
    uint Count;

  public:
    GLIndexBuffer(uint32 *indices, uint32 count);
    ~GLIndexBuffer();

    void Bind() override;
    void Unbind() override;

    uint Size() override;
  };
}