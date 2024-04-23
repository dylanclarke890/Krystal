#pragma once

#include "GL.h"
#include "Graphics/VertexArray.h"

namespace Krys
{
  class GLVertexArray : public VertexArray
  {
  private:
    GLRendererId Id;
    uint32 VertexBufferIndex = 0;
    std::vector<VertexBuffer *> VertexBuffers;
    IndexBuffer *ZBuffer;

  public:
    GLVertexArray();
    ~GLVertexArray() override;

    void Bind() const override;
    void Unbind() const override;

    void AddVertexBuffer(VertexBuffer *buffer) override;
    void SetIndexBuffer(IndexBuffer *buffer) override;

    const std::vector<VertexBuffer *> &GetVertexBuffers() const override;
    const IndexBuffer *GetIndexBuffer() override;
  };
}