#pragma once

#include "Base/Macros.hpp"
#include "Graphics/Framebuffer.hpp"
#include "Graphics/Handles.hpp"

namespace Krys::Gfx::OpenGL
{
  class OpenGLFramebuffer : public Framebuffer
  {
  public:
    OpenGLFramebuffer(FramebufferHandle handle, RenderTargetHandle colorAttachment,
                      RenderTargetHandle depthAttachment) noexcept;
    ~OpenGLFramebuffer() noexcept override;

    NO_COPY_MOVE(OpenGLFramebuffer);
  };
}