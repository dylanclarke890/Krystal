#pragma once

#include "GL.h"
#include "Graphics/VertexArray.h"

namespace Krys
{
  class GLVertexArray : public VertexArray
  {
  private:
    uint Id;
    uint32 VertexBufferIndex = 0;
    std::vector<Ref<VertexBuffer>> VertexBuffers;
    Ref<IndexBuffer> ZBuffer;

  public:
    GLVertexArray();
    ~GLVertexArray() override;

    void Bind() const override;
    void Unbind() const override;

    void AddVertexBuffer(Ref<VertexBuffer> buffer) override;
    void SetIndexBuffer(Ref<IndexBuffer> buffer) override;

    const std::vector<Ref<VertexBuffer>> &GetVertexBuffers() const override;
    const Ref<IndexBuffer> GetIndexBuffer() override;
  };
}