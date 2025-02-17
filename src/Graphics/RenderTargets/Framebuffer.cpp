#include "Graphics/RenderTargets/Framebuffer.hpp"

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

  RenderTargetHandle Framebuffer::GetDepthAttachment() const noexcept
  {
    return _depthAttachment;
  }

  RenderTargetHandle Framebuffer::GetColorAttachment(uint32 index) const noexcept
  {
    return _colorAttachments[index];
  }

  const List<RenderTargetHandle> &Framebuffer::GetColorAttachments() const noexcept
  {
    return _colorAttachments;
  }

  bool Framebuffer::HasColorAttachments() const noexcept
  {
    return !_colorAttachments.empty();
  }

  bool Framebuffer::HasDepthAttachment() const noexcept
  {
    return _depthAttachment.IsValid();
  }
}