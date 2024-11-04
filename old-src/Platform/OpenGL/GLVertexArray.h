#pragma once

#include "Graphics/Buffer.h"
#include "Graphics/VertexArray.h"
#include "OpenGL/GL.h"
#include "Types.h"

namespace Krys::OpenGL
{
  using namespace Krys::Graphics;

  class GLVertexArray : public VertexArray
  {
  private:
    uint _id;
    uint32 _attributeIndex = 0;
    List<Ref<VertexBuffer>> _vertexBuffers;
    List<Ref<InstanceArrayBuffer>> _instanceArrayBuffers;
    Ref<IndexBuffer> _indexBuffer;

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