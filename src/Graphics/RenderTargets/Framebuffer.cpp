#include "Graphics/RenderTargets/Framebuffer.hpp"

namespace Krys::Gfx
{
  Framebuffer::Framebuffer(FramebufferHandle handle, const FramebufferDescriptor &descriptor) noexcept
      : _handle(handle), _descriptor(descriptor)
  {
  }

  FramebufferHandle Framebuffer::GetHandle() const noexcept
  {
    return _handle;
  }

  RenderTargetHandle Framebuffer::GetColorAttachment(uint32 index) const noexcept
  {
    return _descriptor.ColourAttachments[index];
  }

  const List<RenderTargetHandle> &Framebuffer::GetColorAttachments() const noexcept
  {
    return _descriptor.ColourAttachments;
  }

  RenderTargetHandle Framebuffer::GetDepthAttachment() const noexcept
  {
    return _descriptor.DepthAttachment;
  }

  RenderTargetHandle Framebuffer::GetStencilAttachment() const noexcept
  {
    return _descriptor.StencilAttachment;
  }

  bool Framebuffer::HasColorAttachments() const noexcept
  {
    return !_descriptor.ColourAttachments.empty();
  }

  bool Framebuffer::HasDepthAttachment() const noexcept
  {
    return _descriptor.DepthAttachment.IsValid();
  }

  bool Framebuffer::HasStencilAttachment() const noexcept
  {
    return _descriptor.StencilAttachment.IsValid();
  }
}