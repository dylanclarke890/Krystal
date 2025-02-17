#pragma once

#include "Base/Macros.hpp"
#include "Graphics/Handles.hpp"
#include "Graphics/RenderTargets/Framebuffer.hpp"

namespace Krys::Gfx::OpenGL
{
  class OpenGLFramebuffer : public Framebuffer
  {
  public:
    OpenGLFramebuffer(FramebufferHandle handle, const FramebufferDescriptor& descriptor) noexcept;
    ~OpenGLFramebuffer() noexcept override;

    NO_COPY_MOVE(OpenGLFramebuffer);
  };
}