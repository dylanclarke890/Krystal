#include "GLBuffer.h"

namespace Krys
{
  GLIndexBuffer::GLIndexBuffer(uint32 *indices, uint32 count)
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

  const BufferLayout &GLVertexBuffer::GetLayout() const
  {
    return Layout;
  }

  // TODO: this should also take a BufferLayoutType, which can be interleaved
  // TODO: (e.g. [[pos1, color1], [pos2, color2]])
  // TODO: Or "Continugous" or whatever name we choose
  // TODO: (e.g. [[pos1, pos2], [color1, color2]])
  void GLVertexBuffer::SetLayout(const BufferLayout &layout)
  {
    Layout = layout;
  }
}
