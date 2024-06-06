#include "GLBuffer.h"

namespace Krys
{
  GLIndexBuffer::GLIndexBuffer(uint32 count)
  {
    glCreateBuffers(1, &Id);
    glNamedBufferData(Id, count * sizeof(uint32), 0, GL_STATIC_DRAW);
  }

  GLIndexBuffer::GLIndexBuffer(const uint32 *indices, uint32 count)
      : Id(0), Count(count)
  {
    glCreateBuffers(1, &Id);
    glNamedBufferData(Id, count * sizeof(uint32), indices, GL_STATIC_DRAW);
  }

  GLIndexBuffer::~GLIndexBuffer()
  {
    glDeleteBuffers(1, &Id);
  }

  void GLIndexBuffer::Bind()
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Id);
  }

  void GLIndexBuffer::Unbind()
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }

  void GLIndexBuffer::SetData(const uint32 *indices, uint32 count)
  {
    glNamedBufferSubData(Id, 0, count * sizeof(GLuint), indices);
  }

  uint GLIndexBuffer::Size()
  {
    return Count;
  }

  GLVertexBuffer::GLVertexBuffer(uint32 size)
      : Id(0)
  {
    glCreateBuffers(1, &Id);
    glNamedBufferData(Id, size, nullptr, GL_DYNAMIC_DRAW);
  }

  GLVertexBuffer::GLVertexBuffer(float *vertices, uint32 size)
      : Id(0)
  {
    glCreateBuffers(1, &Id);
    glNamedBufferData(Id, size, vertices, GL_STATIC_DRAW);
  }

  GLVertexBuffer::~GLVertexBuffer()
  {
    glDeleteBuffers(1, &Id);
  }

  void GLVertexBuffer::Bind()
  {
    glBindBuffer(GL_ARRAY_BUFFER, Id);
  }

  void GLVertexBuffer::Unbind()
  {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  void GLVertexBuffer::SetData(const void *data, uint32 size)
  {
    glNamedBufferSubData(Id, 0, size, data);
  }

  const VertexBufferLayout &GLVertexBuffer::GetLayout() const
  {
    return Layout;
  }

  void GLVertexBuffer::SetLayout(const VertexBufferLayout &layout)
  {
    Layout = layout;
  }

  GLUniformBuffer::GLUniformBuffer(uint32 size, uint32 binding)
  {
    glCreateBuffers(1, &Id);
    glNamedBufferData(Id, size, nullptr, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, binding, Id);
  }

  Krys::GLUniformBuffer::GLUniformBuffer(uint32 binding, UniformBufferLayout layout)
  {
    glCreateBuffers(1, &Id);

    SetLayout(layout);
    auto &last = layout.GetElements().back();
    glNamedBufferData(Id, last.AlignedOffset + last.LayoutSize, nullptr, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, binding, Id);
  }

  GLUniformBuffer::~GLUniformBuffer()
  {
    glDeleteBuffers(1, &Id);
  }

  void GLUniformBuffer::Bind()
  {
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
  }

  void GLUniformBuffer::SetData(const void *data, uint32 size, uint32 offset)
  {
    glNamedBufferSubData(Id, offset, size, data);
  }

  void GLUniformBuffer::SetData(const string &name, const void *data)
  {
    for (auto element : Layout.GetElements())
    {
      if (name == element.Name)
      {
        glNamedBufferSubData(Id, element.AlignedOffset, element.LayoutSize, data);
        return;
      }
    }
    KRYS_ASSERT(false, "Unable to find element in layout with name %s", name.c_str());
  }

  const UniformBufferLayout &GLUniformBuffer::GetLayout() const
  {
    return Layout;
  }

  void GLUniformBuffer::SetLayout(const UniformBufferLayout &layout)
  {
    KRYS_ASSERT(layout.GetElements().size(), "Uniform buffer has no layout!", 0);
    Layout = layout;
  }

  GLInstanceArrayBuffer::GLInstanceArrayBuffer(uint32 size)
  {
    glCreateBuffers(1, &Id);
    glNamedBufferData(Id, size, nullptr, GL_DYNAMIC_DRAW);
  }

  GLInstanceArrayBuffer::GLInstanceArrayBuffer(void *data, uint32 size)
  {
    glCreateBuffers(1, &Id);
    glNamedBufferData(Id, size, data, GL_DYNAMIC_DRAW);
  }

  GLInstanceArrayBuffer::~GLInstanceArrayBuffer()
  {
    glDeleteBuffers(1, &Id);
  }

  void GLInstanceArrayBuffer::Bind()
  {
    glBindBuffer(GL_ARRAY_BUFFER, Id);
  }

  void GLInstanceArrayBuffer::Unbind()
  {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  void GLInstanceArrayBuffer::SetData(const void *data, uint32 size)
  {
    glNamedBufferSubData(Id, 0, size, data);
  }

  const InstanceArrayBufferLayout &GLInstanceArrayBuffer::GetLayout() const
  {
    return Layout;
  }

  void GLInstanceArrayBuffer::SetLayout(const InstanceArrayBufferLayout &layout)
  {
    Layout = layout;
  }
}
