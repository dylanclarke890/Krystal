#pragma once

#include "GL.h"
#include "Graphics/VertexArray.h"

namespace Krys
{
  class GLVertexArray : public VertexArray
  {
  private:
    uint Id;
    uint32 AttributeIndex = 0;
    List<Ref<VertexBuffer>> VertexBuffers;
    List<Ref<InstanceArrayBuffer>> InstanceArrayBuffers;
    Ref<IndexBuffer> ZBuffer;

  public:
    GLVertexArray();
    ~GLVertexArray() override;

    void Bind() const override;
    void Unbind() const override;

    void AddVertexBuffer(Ref<VertexBuffer> buffer) override;
    void AddInstanceArrayBuffer(Ref<InstanceArrayBuffer> buffer) override;
    void SetIndexBuffer(Ref<IndexBuffer> buffer) override;

    const List<Ref<VertexBuffer>> &GetVertexBuffers() const override;
    const List<Ref<InstanceArrayBuffer>> &GetInstanceArrayBuffers() const override;
    const Ref<IndexBuffer> GetIndexBuffer() override;
  };
}