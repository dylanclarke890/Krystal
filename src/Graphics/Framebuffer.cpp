#include "Graphics/Framebuffer.hpp"

namespace Krys::Gfx
{
  Framebuffer::Framebuffer(FramebufferHandle handle, RenderTargetHandle colorAttachment,
                           RenderTargetHandle depthAttachment) noexcept
      : _handle(handle), _colorAttachments({colorAttachment}), _depthAttachment(depthAttachment)
  {
  }

  FramebufferHandle Framebuffer::GetHandle() const noexcept
  {
    return _handle;
  }
}