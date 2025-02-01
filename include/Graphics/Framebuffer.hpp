#pragma once

#include "Base/Attributes.hpp"
#include "Base/Types.hpp"
#include "Graphics/Handles.hpp"

namespace Krys::Gfx
{
  class Framebuffer
  {
  public:
    virtual ~Framebuffer() noexcept = default;

    NO_DISCARD FramebufferHandle GetHandle() const noexcept;

    NO_DISCARD RenderTargetHandle GetDepthAttachment() const noexcept;

    NO_DISCARD RenderTargetHandle GetColorAttachment(uint32 index) const noexcept;

    NO_DISCARD const List<RenderTargetHandle> &GetColorAttachments() const noexcept;

    NO_DISCARD bool HasColorAttachments() const noexcept;

    NO_DISCARD bool HasDepthAttachment() const noexcept;

  protected:
    NO_COPY_MOVE(Framebuffer);

    Framebuffer(FramebufferHandle handle, RenderTargetHandle colorAttachment,
                RenderTargetHandle depthAttachment) noexcept;

    FramebufferHandle _handle;
    RenderTargetHandle _depthAttachment;
    List<RenderTargetHandle> _colorAttachments;
  };
}