#pragma once

#include <vector>
#include "Core.h"
#include "Textures/Texture2D.h"
#include "Graphics/Enums.h"
#include "Maths/Maths.h"

namespace Krys
{
  class Framebuffer
  {
  protected:
    uint32 Id;
    uint32 Width, Height, Samples;
    std::vector<Ref<Texture2D>> ColorAttachments;
    Ref<Texture> DepthAttachment;

  public:
    virtual ~Framebuffer() = default;
    virtual void Bind(FramebufferBindType bindType = FramebufferBindType::ReadAndDraw) noexcept = 0;
    virtual void Unbind() noexcept = 0;

    virtual void AddColorAttachment() noexcept = 0;
    virtual void AddDepthAttachment() noexcept = 0;
    virtual void AddDepthCubemapAttachment() noexcept = 0;
    virtual void AddDepthStencilAttachment() noexcept = 0;

    virtual void DisableReadBuffer() noexcept = 0;
    virtual void DisableWriteBuffers() noexcept = 0;
    virtual void SetReadBuffer(uint attachmentIndex) noexcept = 0;
    virtual void SetWriteBuffer(uint attachmentIndex) noexcept = 0;
    
    // TODO: something like the following - SetWriteBuffers(uint* attachmentIndices, uint count) noexcept = 0;

    NO_DISCARD virtual bool IsComplete() noexcept = 0;

    virtual void BlitTo(Ref<Framebuffer> other, RectBounds src, RectBounds dst, RenderBuffer mask) noexcept = 0;
    virtual void BlitTo(Ref<Framebuffer> other, int width, int height, RenderBuffer mask) noexcept = 0;
    virtual void BlitToScreen(RectBounds src, RectBounds dst, RenderBuffer mask) noexcept = 0;
    virtual void BlitToScreen(int width, int height, RenderBuffer mask) noexcept = 0;

    virtual void BlitFrom(Ref<Framebuffer> other, RectBounds src, RectBounds dst, RenderBuffer mask) noexcept = 0;
    virtual void BlitFrom(Ref<Framebuffer> other, int width, int height, RenderBuffer mask) noexcept = 0;
    virtual void BlitFromScreen(RectBounds src, RectBounds dst, RenderBuffer mask) noexcept = 0;
    virtual void BlitFromScreen(int width, int height, RenderBuffer mask) noexcept = 0;

    NO_DISCARD uint32 GetId() const noexcept
    {
      return Id;
    }

    NO_DISCARD uint32 GetWidth() const noexcept
    {
      return Width;
    }

    NO_DISCARD uint32 GetHeight() const noexcept
    {
      return Height;
    }

    NO_DISCARD Ref<Texture2D> GetColorAttachment(uint index = 0)
    {
      KRYS_ASSERT(index < ColorAttachments.size(), "Index out of bounds", 0);
      return ColorAttachments[index];
    }

    NO_DISCARD Ref<Texture> GetDepthAttachment()
    {
      return DepthAttachment;
    }
  };
}