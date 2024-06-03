#pragma once

#include "Core.h"
#include "GL.h"
#include "Graphics/Buffer.h"
#include "Graphics/GraphicsContext.h"

namespace Krys
{

  class GLIndexBuffer : public IndexBuffer
  {
  private:
    uint Id;
    uint Count;

  public:
    GLIndexBuffer(uint32 count);
    GLIndexBuffer(const uint32 *indices, uint32 count);
    ~GLIndexBuffer() override;

    void Bind() override;
    void Unbind() override;

    void SetData(const uint32 *indices, uint32 count) override;

    uint Size() override;
  };

  class GLVertexBuffer : public VertexBuffer
  {
  private:
    uint Id;
    VertexBufferLayout Layout;

  public:
    GLVertexBuffer(uint32 size);
    GLVertexBuffer(float *vertices, uint32 size);
    ~GLVertexBuffer() override;

    void Bind() override;
    void Unbind() override;

    void SetData(const void *data, uint32 size) override;

    const VertexBufferLayout &GetLayout() const override;
    void SetLayout(const VertexBufferLayout &layout) override;
  };

  class GLUniformBuffer : public UniformBuffer
  {
  private:
    uint Id;
    UniformBufferLayout Layout;

  public:
    GLUniformBuffer(uint32 size, uint32 binding);
    GLUniformBuffer(uint32 binding, UniformBufferLayout layout);
    ~GLUniformBuffer() override;

    void SetData(const void *data, uint32 size, uint32 offset) override;
    void SetData(const std::string &name, const void *data) override;

    const UniformBufferLayout &GetLayout() const override;
    void SetLayout(const UniformBufferLayout &layout) override;

    void Bind() override;
  };

  class GLInstanceArrayBuffer : public InstanceArrayBuffer
  {
  private:
    uint Id;
    InstanceArrayBufferLayout Layout;

  public:
    GLInstanceArrayBuffer(uint32 size);
    GLInstanceArrayBuffer(void *data, uint32 size);
    ~GLInstanceArrayBuffer() override;

    void Bind() override;
    void Unbind() override;

    void SetData(const void *data, uint32 size) override;

    const InstanceArrayBufferLayout &GetLayout() const override;
    void SetLayout(const InstanceArrayBufferLayout &layout) override;
  };
}