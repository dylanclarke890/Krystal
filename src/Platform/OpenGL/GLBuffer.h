#pragma once

#include "Core.h"

#include "Graphics/Buffer.h"
#include "Maths/Vector.h"
#include "OpenGL/GL.h"

namespace Krys::OpenGL
{
  using namespace Krys::Graphics;
  using namespace Krys::Maths;

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

    struct AttributeInfo
    {
      uint32 Offset = 0;
      uint32 Size = 0;
      bool Found = false;
    };

  public:
    GLUniformBuffer(uint32 size, uint32 binding);
    GLUniformBuffer(uint32 binding, UniformBufferLayout layout);
    ~GLUniformBuffer() override;

    void SetData(const string &name, bool value) override;
    void SetData(const string &name, int value) override;
    void SetData(const string &name, size_t value) override;
    void SetData(const string &name, float value) override;
    void SetData(const string &name, const Vec2 &value) override;
    void SetData(const string &name, const Vec3 &value) override;
    void SetData(const string &name, const Vec4 &value) override;
    void SetData(const string &name, const Mat3 &value) override;
    void SetData(const string &name, const Mat4 &value) override;

    const UniformBufferLayout &GetLayout() const override;
    void SetLayout(const UniformBufferLayout &layout) override;

    void Bind() override;

  private:
    AttributeInfo GetAttributeInfo(const string &name) const noexcept;
    AttributeInfo GetAttributeInfo(const string &name, UniformStructLayout layout, AttributeInfo info) const noexcept;
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