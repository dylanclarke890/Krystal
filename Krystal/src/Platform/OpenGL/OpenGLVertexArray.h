#pragma once

#include "Krystal/Renderer/VertexArray.h"

namespace Krys
{
  class OpenGLVertexArray : public VertexArray
  {
  private:
    uint32_t m_RendererId, m_VertexBufferIndex;
    std::vector<Ref<VertexBuffer>> m_VertexBuffers;
    Ref<IndexBuffer> m_IndexBuffer;
  public:
    OpenGLVertexArray();
    virtual ~OpenGLVertexArray();

    virtual void Bind() const override;
    virtual void Unbind() const override;

    virtual void AddVertexBuffer(Ref<VertexBuffer> buffer) override;
    virtual void SetIndexBuffer(Ref<IndexBuffer> buffer) override;

    virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override { return m_VertexBuffers; }
    virtual const Ref<IndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; }
  };
}