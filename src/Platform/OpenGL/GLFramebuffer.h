#pragma once

#include "Graphics/Framebuffer.h"
#include "Textures/GLTexture2D.h"

namespace Krys
{
  static auto ToGLFramebufferBindType = [](FramebufferBindType bindType) -> int
  {
    switch (bindType)
    {
    case FramebufferBindType::Draw:
      return GL_DRAW_FRAMEBUFFER;

    case FramebufferBindType::Read:
      return GL_READ_FRAMEBUFFER;

    case FramebufferBindType::ReadAndDraw:
      return GL_FRAMEBUFFER;

    default:
    {
      KRYS_ASSERT(false, "Unknown FramebufferBindType!", 0);
      return 0;
    }
    }
  };

  static auto ToGLBufferFlags = [](RenderBuffer buffers) -> int
  {
    int glBufferFlags = 0;
    if (buffers & RenderBuffer::Color)
      glBufferFlags |= GL_COLOR_BUFFER_BIT;

    if (buffers & RenderBuffer::Depth)
      glBufferFlags |= GL_DEPTH_BUFFER_BIT;

    if (buffers & RenderBuffer::Stencil)
      glBufferFlags |= GL_STENCIL_BUFFER_BIT;

    KRYS_ASSERT(glBufferFlags, "Invalid flags!", 0);

    return glBufferFlags;
  };

  class GLFramebuffer : public Framebuffer
  {
  private:
    FramebufferBindType BoundAs;

  public:
    GLFramebuffer(int width, int height, int samples = 1)
    {
      glCreateFramebuffers(1, &Id);
      Width = width;
      Height = height;
      Samples = samples;
    }

    ~GLFramebuffer() override
    {
      glDeleteFramebuffers(1, &Id);
    }

    void Bind(FramebufferBindType bindType) noexcept override
    {
      glBindFramebuffer(ToGLFramebufferBindType(bindType), Id);
      BoundAs = bindType;
    }

    void Unbind() noexcept override
    {
      KRYS_ASSERT(BoundAs != FramebufferBindType::None, "Framebuffer was not bound!", 0);
      glBindFramebuffer(ToGLFramebufferBindType(BoundAs), 0);
      BoundAs = FramebufferBindType::None;
    }

    void AddColorAttachment() noexcept override
    {
      Ref<Texture2D> texture = CreateRef<GLTexture2D>(Width, Height, Samples);
      if (Samples == 1)
        texture->SetTextureWrapModes(TextureWrapMode::ClampToEdge, TextureWrapMode::ClampToEdge);

      glNamedFramebufferTexture(Id, static_cast<GLenum>(GL_COLOR_ATTACHMENT0 + ColorAttachments.size()), texture->GetId(), 0);
      ColorAttachments.push_back(texture);
    }

    void AddDepthAttachment() noexcept override
    {
      KRYS_ASSERT(!DepthAttachment, "Already has a depth attachment", 0);

      Ref<Texture2D> texture = CreateRef<GLTexture2D>(Width, Height, Samples, TextureInternalFormat::Depth);
      glNamedFramebufferTexture(Id, GL_DEPTH_ATTACHMENT, texture->GetId(), 0);
      // TODO: we're assuming that this is a depth only framebuffer.
      glNamedFramebufferDrawBuffer(Id, GL_NONE);
      glNamedFramebufferReadBuffer(Id, GL_NONE);

      DepthAttachment = texture;
    }

    void AddDepthStencilAttachment() noexcept override
    {
      // TODO: this is created assuming it isn't being sampled from as we don't have a class to represent this with yet.
      // Also we can't actually sample render buffer objects, consider having ColorAttachmentType so we can
      // optimise where possible
      uint rbo;
      glCreateRenderbuffers(1, &rbo);
      if (Samples > 1)
        glNamedRenderbufferStorageMultisample(rbo, Samples, GL_DEPTH24_STENCIL8, Width, Height);
      else
        glNamedRenderbufferStorage(rbo, GL_DEPTH24_STENCIL8, Width, Height);
      glNamedFramebufferRenderbuffer(Id, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
    }

    NO_DISCARD bool IsComplete() noexcept override
    {
      GLenum status = glCheckNamedFramebufferStatus(Id, GL_FRAMEBUFFER);
      return status == GL_FRAMEBUFFER_COMPLETE;
    }

    void BlitTo(Ref<Framebuffer> other, RectBounds src, RectBounds dst, RenderBuffer mask) noexcept override
    {
      Blit(Id, other->GetId(), src, dst, mask);
    }

    void BlitTo(Ref<Framebuffer> other, int width, int height, RenderBuffer mask) noexcept override
    {
      RectBounds bounds = {0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height)};
      Blit(Id, other->GetId(), bounds, bounds, mask);
    }

    void BlitToScreen(RectBounds src, RectBounds dst, RenderBuffer mask) noexcept override
    {
      Blit(Id, 0, src, dst, mask);
    }

    void BlitToScreen(int width, int height, RenderBuffer mask) noexcept override
    {
      RectBounds bounds = {0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height)};
      Blit(Id, 0, bounds, bounds, mask);
    }

    void BlitFrom(Ref<Framebuffer> other, RectBounds src, RectBounds dst, RenderBuffer mask) noexcept override
    {
      Blit(other->GetId(), Id, src, dst, mask);
    }

    void BlitFrom(Ref<Framebuffer> other, int width, int height, RenderBuffer mask) noexcept override
    {
      RectBounds bounds = {0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height)};
      Blit(other->GetId(), Id, bounds, bounds, mask);
    }

    void BlitFromScreen(RectBounds src, RectBounds dst, RenderBuffer mask) noexcept override
    {
      Blit(0, Id, src, dst, mask);
    }

    void BlitFromScreen(int width, int height, RenderBuffer mask) noexcept override
    {
      RectBounds bounds = {0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height)};
      Blit(0, Id, bounds, bounds, mask);
    }

    static void Blit(uint32 a, uint32 b, RectBounds src, RectBounds dst, RenderBuffer mask) noexcept
    {
      auto IntCast = [](float val)
      { return static_cast<int>(val); };

      glBlitNamedFramebuffer(a, b,
                             IntCast(src.Left), IntCast(src.Bottom), IntCast(src.Right), IntCast(src.Top),
                             IntCast(dst.Left), IntCast(dst.Bottom), IntCast(dst.Right), IntCast(dst.Top),
                             ToGLBufferFlags(mask), GL_NEAREST);
    }
  };
}