#include "Graphics/OpenGL/OpenGLFramebuffer.hpp"

namespace Krys::Gfx::OpenGL
{
  OpenGLFramebuffer::OpenGLFramebuffer(const OpenGLFramebufferDescriptor &descriptor) noexcept
      : _descriptor(descriptor), _framebuffer(0)
  {
    ::glCreateFramebuffers(1, &_framebuffer);

    ::glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);

    for (const auto &texture : _descriptor.ColourAttachments)
      ::glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

    if (_descriptor.DepthStencilAttachment != 0)
      ::glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D,
                               _descriptor.DepthStencilAttachment, 0);
    else
    {
      if (_descriptor.DepthAttachment != 0)
        ::glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D,
                                 _descriptor.DepthAttachment, 0);

      if (_descriptor.StencilAttachment != 0)
        ::glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D,
                                 _descriptor.StencilAttachment, 0);
    }

    KRYS_ASSERT(::glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE,
                "Framebuffer is incomplete");

    ::glBindFramebuffer(GL_FRAMEBUFFER, 0);
  }

  OpenGLFramebuffer::~OpenGLFramebuffer() noexcept
  {
    ::glDeleteFramebuffers(1, &_framebuffer);
  }

  GLuint OpenGLFramebuffer::GetNativeHandle() const noexcept
  {
    return _framebuffer;
  }

  OpenGLFramebufferDescriptor OpenGLFramebuffer::GetDescriptor() const noexcept
  {
    return _descriptor;
  }

  void OpenGLFramebuffer::Bind() const noexcept
  {
    ::glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);
  }

  void OpenGLFramebuffer::Unbind() const noexcept
  {
    ::glBindFramebuffer(GL_FRAMEBUFFER, 0);
  }
}