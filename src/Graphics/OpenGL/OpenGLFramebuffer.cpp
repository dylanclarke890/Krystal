#include "Graphics/OpenGL/OpenGLFramebuffer.hpp"

namespace Krys::Gfx::OpenGL
{
  OpenGLFramebuffer::OpenGLFramebuffer(FramebufferHandle handle,
                                       const FramebufferDescriptor &descriptor) noexcept
      : Framebuffer(handle, descriptor)
  {
  }

  OpenGLFramebuffer::~OpenGLFramebuffer() noexcept
  {
  }
}