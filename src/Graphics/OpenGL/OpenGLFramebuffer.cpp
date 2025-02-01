#include "Graphics/OpenGL/OpenGLFramebuffer.hpp"

namespace Krys::Gfx::OpenGL
{
  OpenGLFramebuffer::OpenGLFramebuffer(FramebufferHandle handle, RenderTargetHandle colorAttachment,
                                       RenderTargetHandle depthAttachment) noexcept
      : Framebuffer(handle, colorAttachment, depthAttachment)
  {
  }

  OpenGLFramebuffer::~OpenGLFramebuffer() noexcept
  {
  }
}