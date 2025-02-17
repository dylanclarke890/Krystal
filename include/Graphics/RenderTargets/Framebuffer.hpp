#pragma once

#include "Base/Attributes.hpp"
#include "Base/Types.hpp"
#include "Graphics/Handles.hpp"
#include "Graphics/RenderTargets/FramebufferDescriptor.hpp"

namespace Krys::Gfx
{
  class Framebuffer
  {
  public:
    virtual ~Framebuffer() noexcept = default;

    NO_DISCARD FramebufferHandle GetHandle() const noexcept;

    NO_DISCARD RenderTargetHandle GetDepthAttachment() const noexcept;

    NO_DISCARD RenderTargetHandle GetStencilAttachment() const noexcept;

    NO_DISCARD RenderTargetHandle GetColorAttachment(uint32 index) const noexcept;

    NO_DISCARD const List<RenderTargetHandle> &GetColorAttachments() const noexcept;

    NO_DISCARD bool HasDepthAttachment() const noexcept;

    NO_DISCARD bool HasStencilAttachment() const noexcept;

    NO_DISCARD bool HasColorAttachments() const noexcept;

  protected:
    NO_COPY_MOVE(Framebuffer);

    Framebuffer(FramebufferHandle handle, const FramebufferDescriptor &descriptor) noexcept;

    FramebufferHandle _handle;
    FramebufferDescriptor _descriptor;
  };
}