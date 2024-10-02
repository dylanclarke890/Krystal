#pragma once

#include "Core.h"
#include "BufferLayout.h"
#include "Maths/Maths.h"

namespace Krys
{
  class IndexBuffer
  {
  public:
    virtual ~IndexBuffer() = default;

    virtual void Bind() = 0;
    virtual void Unbind() = 0;
    virtual void SetData(const uint32 *indices, uint32 count) = 0;

    virtual uint Size() = 0;
  };

  class VertexBuffer
  {
  protected:
    inline static int MaxVertexAttributes = 0;

  public:
    virtual ~VertexBuffer() = default;

    virtual void Bind() = 0;
    virtual void Unbind() = 0;

    virtual void SetData(const void *data, uint32 size) = 0;

    virtual const VertexBufferLayout &GetLayout() const = 0;
    virtual void SetLayout(const VertexBufferLayout &layout) = 0;

    static void SetDriverLimits(int maxVertexAttributes)
    {
      MaxVertexAttributes = maxVertexAttributes;
    }
  };

  class UniformBuffer
  {
  public:
    virtual ~UniformBuffer() = default;

    virtual void Bind() = 0;

    virtual void SetData(const string &name, bool value) = 0;
    virtual void SetData(const string &name, int value) = 0;
    virtual void SetData(const string &name, size_t value) = 0;
    virtual void SetData(const string &name, float value) = 0;
    virtual void SetData(const string &name, const Vec2 &value) = 0;
    virtual void SetData(const string &name, const Vec3 &value) = 0;
    virtual void SetData(const string &name, const Vec4 &value) = 0;
    virtual void SetData(const string &name, const Mat3 &value) = 0;
    virtual void SetData(const string &name, const Mat4 &value) = 0;

    virtual const UniformBufferLayout &GetLayout() const = 0;
    virtual void SetLayout(const UniformBufferLayout &layout) = 0;
  };

  class InstanceArrayBuffer
  {
  public:
    virtual ~InstanceArrayBuffer() = default;

    virtual void Bind() = 0;
    virtual void Unbind() = 0;
    virtual void SetData(const void *data, uint32 size) = 0;

    virtual const InstanceArrayBufferLayout &GetLayout() const = 0;
    virtual void SetLayout(const InstanceArrayBufferLayout &layout) = 0;
  };
}