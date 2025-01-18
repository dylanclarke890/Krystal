#include "Graphics/OpenGL/OpenGLGraphicsContext.hpp"
#include "Graphics/OpenGL/OpenGLBuffer.hpp"

#include <glad/gl.h>

namespace Krys::Graphics::OpenGL
{
  OpenGLGraphicsContext::~OpenGLGraphicsContext() noexcept
  {
  }

  void OpenGLGraphicsContext::SetClearColor(const Vec3 &rgb) noexcept
  {
    glClearColor(rgb.x, rgb.y, rgb.z, 1.0f);
  }

  void OpenGLGraphicsContext::SetClearColor(const Vec4 &rgba) noexcept
  {
    glClearColor(rgba.x, rgba.y, rgba.z, rgba.w);
  }

  void OpenGLGraphicsContext::Clear() noexcept
  {
    glClear(GL_COLOR_BUFFER_BIT);
  }

  VertexBufferHandle OpenGLGraphicsContext::CreateVertexBuffer(uint32 size) noexcept
  {
    auto buffer = CreateUnique<OpenGLVertexBuffer>(size);
    _vertexBuffers[buffer->GetHandle()] = std::move(buffer);
    return buffer->GetHandle();
  }
}