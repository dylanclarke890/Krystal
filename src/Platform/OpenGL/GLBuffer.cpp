#include "GLBuffer.h"

namespace Krys
{
  GLIndexBuffer::GLIndexBuffer(uint32 *indices, uint32 count)
      : Id(0), Count(count)
  {
    glCreateBuffers(1, &Id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count, indices, GL_STATIC_DRAW);
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
}
