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

    Ref<Texture2D> AddColorAttachment() noexcept override
    {
      return AddColorAttachment(TextureInternalFormat::RGBA);
    }

    Ref<Texture2D> AddColorAttachment(TextureInternalFormat internalFormat) noexcept override
    {
      KRYS_ASSERT(ColorAttachments.size() < MaxColorAttachments, "Maximum Color Attachments exceeded.", 0);

      Ref<Texture2D> texture = CreateRef<GLTexture2D>(Width, Height, Samples, internalFormat);
      if (Samples == 1)
        texture->SetTextureWrapModes(TextureWrapMode::ClampToEdge, TextureWrapMode::ClampToEdge);

      glNamedFramebufferTexture(Id, static_cast<GLenum>(GL_COLOR_ATTACHMENT0 + ColorAttachments.size()), texture->GetId(), 0);
      ColorAttachments.push_back(texture);

      return texture;
    }

    Ref<Texture2D> AddDepthAttachment() noexcept override
    {
      KRYS_ASSERT(!DepthAttachment, "Already has a depth attachment", 0);

      Ref<Texture2D> texture = CreateRef<GLTexture2D>(Width, Height, Samples, TextureInternalFormat::Depth);
      texture->SetTextureWrapModes(TextureWrapMode::ClampToBorder, TextureWrapMode::ClampToBorder);
      texture->SetBorderColor({1.0f, 1.0f, 1.0f, 1.0f});

      glNamedFramebufferTexture(Id, GL_DEPTH_ATTACHMENT, texture->GetId(), 0);

      DepthAttachment = texture;

      return texture;
    }

    Ref<TextureCubemap> AddDepthCubemapAttachment() noexcept override
    {
      KRYS_ASSERT(!DepthAttachment, "Already has a depth attachment", 0);

      Ref<GLTextureCubemap> texture = CreateRef<GLTextureCubemap>(Width, Height, TextureInternalFormat::Depth);
      texture->SetTextureWrapModes(TextureWrapMode::ClampToBorder, TextureWrapMode::ClampToBorder, TextureWrapMode::ClampToBorder);
      texture->SetBorderColor({1.0f, 1.0f, 0.0f, 1.0f});

      glNamedFramebufferTexture(Id, GL_DEPTH_ATTACHMENT, texture->GetId(), 0);

      DepthAttachment = texture;

      return texture;
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

    void DisableReadBuffer() noexcept override
    {
      glNamedFramebufferReadBuffer(Id, GL_NONE);
    }

    void DisableWriteBuffers() noexcept override
    {
      glNamedFramebufferDrawBuffer(Id, GL_NONE);
    }

    void SetReadBuffer(uint attachmentIndex) noexcept override
    {
      KRYS_ASSERT(attachmentIndex >= 0 && attachmentIndex < ColorAttachments.size(), "Index out of range: Max is %d, %d received", ColorAttachments.size() - 1, attachmentIndex);
      glNamedFramebufferReadBuffer(Id, GL_COLOR_ATTACHMENT0 + attachmentIndex);
    }

    void SetWriteBuffer(uint attachmentIndex) noexcept override
    {
      KRYS_ASSERT(attachmentIndex >= 0 && attachmentIndex < ColorAttachments.size(), "Index out of range: Max is %d, %d received", ColorAttachments.size() - 1, attachmentIndex);
      glNamedFramebufferDrawBuffer(Id, GL_COLOR_ATTACHMENT0 + attachmentIndex);
    }

    void SetWriteBuffers(const List<uint> &attachmentIndices) noexcept override
    {
      KRYS_ASSERT(attachmentIndices.size(), "No attachments specified.", 0);
      KRYS_ASSERT(attachmentIndices.size() <= MaxDrawBuffers, "Unable to bind to more than %d draw buffers at one time.", MaxDrawBuffers);

      List<GLenum> attachments;
      for (auto i : attachmentIndices)
      {
        KRYS_ASSERT(i >= 0 && i < ColorAttachments.size(), "Index out of range: %d items, %d received", ColorAttachments.size() - 1, i);
        attachments.push_back(GL_COLOR_ATTACHMENT0 + i);
      }

      glNamedFramebufferDrawBuffers(Id, static_cast<GLsizei>(attachments.size()), attachments.data());
    }

    NO_DISCARD bool IsComplete() noexcept override
    {
      GLenum status = glCheckNamedFramebufferStatus(Id, GL_FRAMEBUFFER);
      return status == GL_FRAMEBUFFER_COMPLETE;
    }

#pragma region Blitting

    void BlitTo(Ref<Framebuffer> other, BoundingBox<int> src, BoundingBox<int> dst, RenderBuffer mask) noexcept override
    {
      Blit(Id, other->GetId(), src, dst, mask);
    }

    void BlitTo(Ref<Framebuffer> other, int width, int height, RenderBuffer mask) noexcept override
    {
      BoundingBox<int> bounds = {0, width, 0, height};
      Blit(Id, other->GetId(), bounds, bounds, mask);
    }

    void BlitToScreen(BoundingBox<int> src, BoundingBox<int> dst, RenderBuffer mask) noexcept override
    {
      Blit(Id, 0, src, dst, mask);
    }

    void BlitToScreen(int width, int height, RenderBuffer mask) noexcept override
    {
      BoundingBox<int> bounds = {0, width, 0, height};
      Blit(Id, 0, bounds, bounds, mask);
    }

    void BlitFrom(Ref<Framebuffer> other, BoundingBox<int> src, BoundingBox<int> dst, RenderBuffer mask) noexcept override
    {
      Blit(other->GetId(), Id, src, dst, mask);
    }

    void BlitFrom(Ref<Framebuffer> other, int width, int height, RenderBuffer mask) noexcept override
    {
      BoundingBox<int> bounds = {0, width, 0, height};
      Blit(other->GetId(), Id, bounds, bounds, mask);
    }

    void BlitFromScreen(BoundingBox<int> src, BoundingBox<int> dst, RenderBuffer mask) noexcept override
    {
      Blit(0, Id, src, dst, mask);
    }

    void BlitFromScreen(int width, int height, RenderBuffer mask) noexcept override
    {
      BoundingBox<int> bounds = {0, width, 0, height};
      Blit(0, Id, bounds, bounds, mask);
    }

    static void Blit(uint32 a, uint32 b, BoundingBox<int> src, BoundingBox<int> dst, RenderBuffer mask) noexcept
    {
      glBlitNamedFramebuffer(a, b,
                             src.Left, src.Bottom, src.Right, src.Top,
                             dst.Left, dst.Bottom, dst.Right, dst.Top,
                             ToGLBufferFlags(mask), GL_NEAREST);
    }

#pragma endregion Blitting
  };
}