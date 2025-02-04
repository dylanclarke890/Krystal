#pragma once

#include "Debug/Macros.hpp"
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
    OpenGLBuffer(THandle handle, uint32 capacity,
                 BufferUsageHint usageHint = BufferUsageHint::Static) noexcept
        : Buffer<THandle>(handle, capacity, usageHint), _id(0)
    {
      ::glCreateBuffers(1, &_id);
      ::glNamedBufferData(_id, this->_capacity, nullptr, BufferUsageHintToOpenGL(this->_usageHint));
    }

    ~OpenGLBuffer() override
    {
      ::glDeleteBuffers(1, &_id);
    }

    void Write(const void *data, size_t size, size_t offset) noexcept override
    {
      KRYS_ASSERT(offset + size <= this->_capacity, "Data size exceeds buffer capacity");
      ::glNamedBufferSubData(_id, offset, size, data);
    }

    void Bind() noexcept override
    {
      ::glBindBuffer(Target, _id);
    }

    void Unbind() noexcept override
    {
      ::glBindBuffer(Target, 0);
    }

    void Bind(uint32 index) noexcept
    requires(Target == GL_UNIFORM_BUFFER || Target == GL_SHADER_STORAGE_BUFFER)
    {
      ::glBindBufferBase(Target, index, _id);
    }

    NO_DISCARD GLuint GetNativeHandle() const noexcept
    {
      return _id;
    }

  private:
    GLuint _id;
  };

  using OpenGLVertexBuffer = OpenGLBuffer<VertexBufferHandle, GL_ARRAY_BUFFER>;
  using OpenGLIndexBuffer = OpenGLBuffer<IndexBufferHandle, GL_ELEMENT_ARRAY_BUFFER>;
  using OpenGLUniformBuffer = OpenGLBuffer<UniformBufferHandle, GL_UNIFORM_BUFFER>;
  using OpenGLShaderStorageBuffer = OpenGLBuffer<ShaderStorageBufferHandle, GL_SHADER_STORAGE_BUFFER>;
}