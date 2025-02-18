#pragma once

#include "Base/Macros.hpp"
#include "Base/Types.hpp"
#include "Graphics/Handles.hpp"

#include <glad/gl.h>

namespace Krys::Gfx::OpenGL
{
  struct OpenGLFramebufferDescriptor
  {
    List<GLuint> ColourAttachments {0};
    GLuint DepthAttachment {0};
    GLuint StencilAttachment {0};
    GLuint DepthStencilAttachment {0};
    int Width {0}, Height {0};
  };

  class OpenGLFramebuffer
  {
  public:
    OpenGLFramebuffer(const OpenGLFramebufferDescriptor &descriptor) noexcept;
    ~OpenGLFramebuffer() noexcept;

    NO_COPY_MOVE(OpenGLFramebuffer);

    NO_DISCARD GLuint GetNativeHandle() const noexcept;

    NO_DISCARD OpenGLFramebufferDescriptor GetDescriptor() const noexcept;

    void Bind() const noexcept;

    void Unbind() const noexcept;

  protected:
    GLuint _framebuffer {0};
    OpenGLFramebufferDescriptor _descriptor;
  };
}