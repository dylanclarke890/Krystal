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
    ~GLIndexBuffer() override;

    void Bind() override;
    void Unbind() override;

    uint Size() override;
  };

  class GLVertexBuffer : public VertexBuffer
  {
  private:
    GLRendererId Id;
    BufferLayout Layout;

  public:
    GLVertexBuffer(uint32 size);
    GLVertexBuffer(float *vertices, uint32 size);
    ~GLVertexBuffer() override;

    void Bind() override;
    void Unbind() override;

    void SetData(const void *data, uint32 size) override;

    const BufferLayout &GetLayout() const override;
    void SetLayout(const BufferLayout &layout) override;
  };
}