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
    Ref<Texture2D> DepthAttachment;

  public:
    virtual ~Framebuffer() = default;
    virtual void Bind(FramebufferBindType bindType = FramebufferBindType::ReadAndDraw) noexcept = 0;
    virtual void Unbind() noexcept = 0;

    virtual void AddColorAttachment() noexcept = 0;
    virtual void AddDepthAttachment() noexcept = 0;
    virtual void AddDepthStencilAttachment() noexcept = 0;

    virtual void BlitTo(Ref<Framebuffer> other, RectBounds src, RectBounds dst, RenderBuffer mask) noexcept = 0;
    virtual void BlitFrom(Ref<Framebuffer> other, RectBounds src, RectBounds dst, RenderBuffer mask) noexcept = 0;

    virtual void BlitToScreen(RectBounds src, RectBounds dst, RenderBuffer mask) noexcept = 0;
    virtual void BlitFromScreen(RectBounds src, RectBounds dst, RenderBuffer mask) noexcept = 0;

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

    Ref<Texture2D> GetColorAttachment(uint index = 0)
    {
      KRYS_ASSERT(index < ColorAttachments.size(), "Index out of bounds", 0);
      return ColorAttachments[index];
    }

    Ref<Texture2D> GetDepthAttachment()
    {
      return DepthAttachment;
    }
  };
}