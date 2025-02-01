#pragma once

#include "Base/Macros.hpp"
#include "Graphics/Framebuffer.hpp"
#include "Graphics/Handles.hpp"

namespace Krys::Gfx::OpenGL
{
  class OpenGLFramebuffer
  {
  public:
    OpenGLFramebuffer(FramebufferHandle handle, uint32 width, uint32 height) noexcept;
    ~OpenGLFramebuffer() noexcept override;

    NO_COPY_MOVE(OpenGLFramebuffer);
  };
}