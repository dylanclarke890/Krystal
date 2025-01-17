#pragma once

#include "Core/Debug/Macros.hpp"
#include "Graphics/Buffer.hpp"
#include "Graphics/Handles.hpp"

#include <glad/gl.h>

namespace Krys::Gfx::OpenGL
{
  constexpr GLuint BufferUsageHintToOpenGL(BufferUsageHint hint) noexcept
  {
    switch (hint)
    {
      case BufferUsageHint::Static:  return GL_STATIC_DRAW;
      case BufferUsageHint::Dynamic: return GL_DYNAMIC_DRAW;
      case BufferUsageHint::Stream:  return GL_STREAM_DRAW;
      default:                       return GL_STATIC_DRAW;
    }
  }

  template <typename THandle, GLenum Target>
  class OpenGLBuffer : public Buffer<THandle>
  {
  public:
    OpenGLBuffer(uint32 capacity, BufferUsageHint usageHint = BufferUsageHint::Static) noexcept
        : Buffer<THandle>(capacity, usageHint), _glHandle(0)
    {
      ::glCreateBuffers(1, &_glHandle);
      ::glNamedBufferData(_glHandle, this->_capacity, nullptr, BufferUsageHintToOpenGL(this->_usageHint));
      this->_handle = THandle(static_cast<THandle::handle_t>(_glHandle));
    }

    ~OpenGLBuffer() override
    {
      ::glDeleteBuffers(1, &_glHandle);
    }

    void Write(const void *data, size_t size, size_t offset) noexcept override
    {
      KRYS_ASSERT(offset + size <= this->_capacity, "Data size exceeds buffer capacity");
      ::glNamedBufferSubData(_glHandle, offset, size, data);
    }

    void Bind() noexcept override
    {
      ::glBindBuffer(Target, _glHandle);
    }

    void Unbind() noexcept override
    {
      ::glBindBuffer(Target, 0);
    }

  private:
    GLuint _glHandle;
  };

  using OpenGLVertexBuffer = OpenGLBuffer<VertexBufferHandle, GL_ARRAY_BUFFER>;
  using OpenGLIndexBuffer = OpenGLBuffer<IndexBufferHandle, GL_ELEMENT_ARRAY_BUFFER>;
  using OpenGLUniformBuffer = OpenGLBuffer<UniformHandle, GL_UNIFORM_BUFFER>;
}