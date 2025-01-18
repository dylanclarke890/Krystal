#pragma once

#include "Core.h"
#include "Graphics/Enums.h"
#include "Graphics/Framebuffer.h"
#include "OpenGL/Textures/GLTexture2D.h"

namespace Krys::OpenGL
{
  using namespace Krys::Gfx;

  static auto ToGLFramebufferBindType = [](FramebufferBindType bindType) -> int
  {
    switch (bindType)
    {
      case FramebufferBindType::Draw:        return GL_DRAW_FRAMEBUFFER;

      case FramebufferBindType::Read:        return GL_READ_FRAMEBUFFER;

      case FramebufferBindType::ReadAndDraw: return GL_FRAMEBUFFER;

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
    FramebufferBindType _boundAs;

  public:
    GLFramebuffer(int width, int height, int samples = 1)
    {
      glCreateFramebuffers(1, &_id);
      _width = width;
      _height = height;
      _samples = samples;
    }

    ~GLFramebuffer() override
    {
      glDeleteFramebuffers(1, &_id);
    }

    void Bind(FramebufferBindType bindType) noexcept override
    {
      glBindFramebuffer(ToGLFramebufferBindType(bindType), _id);
      _boundAs = bindType;
    }

    void Unbind() noexcept override
    {
      KRYS_ASSERT(_boundAs != FramebufferBindType::None, "Framebuffer was not bound!", 0);
      glBindFramebuffer(ToGLFramebufferBindType(_boundAs), 0);
      _boundAs = FramebufferBindType::None;
    }

    Ref<Texture2D> AddColorAttachment() noexcept override
    {
      return AddColorAttachment(TextureInternalFormat::RGBA);
    }

    Ref<Texture2D> AddColorAttachment(TextureInternalFormat internalFormat) noexcept override
    {
      KRYS_ASSERT(_colorAttachments.size() < MaxColorAttachments, "Maximum Color Attachments exceeded.", 0);

      Ref<Texture2D> texture = CreateRef<GLTexture2D>(_width, _height, _samples, internalFormat);
      if (_samples == 1)
        texture->SetTextureWrapModes(TextureWrapMode::ClampToEdge, TextureWrapMode::ClampToEdge);

      glNamedFramebufferTexture(_id, static_cast<GLenum>(GL_COLOR_ATTACHMENT0 + _colorAttachments.size()),
                                texture->GetId(), 0);
      _colorAttachments.push_back(texture);

      return texture;
    }

    Ref<Texture2D> AddDepthAttachment() noexcept override
    {
      KRYS_ASSERT(!_depthAttachment, "Already has a depth attachment", 0);

      Ref<Texture2D> texture = CreateRef<GLTexture2D>(_width, _height, _samples, TextureInternalFormat::Depth);
      texture->SetTextureWrapModes(TextureWrapMode::ClampToBorder, TextureWrapMode::ClampToBorder);
      texture->SetBorderColor({1.0f, 1.0f, 1.0f, 1.0f});

      glNamedFramebufferTexture(_id, GL_DEPTH_ATTACHMENT, texture->GetId(), 0);

      _depthAttachment = texture;

      return texture;
    }

    Ref<TextureCubemap> AddDepthCubemapAttachment() noexcept override
    {
      KRYS_ASSERT(!_depthAttachment, "Already has a depth attachment", 0);

      Ref<GLTextureCubemap> texture = CreateRef<GLTextureCubemap>(_width, _height, TextureInternalFormat::Depth);
      texture->SetTextureWrapModes(TextureWrapMode::ClampToBorder, TextureWrapMode::ClampToBorder,
                                   TextureWrapMode::ClampToBorder);
      texture->SetBorderColor({1.0f, 1.0f, 0.0f, 1.0f});

      glNamedFramebufferTexture(_id, GL_DEPTH_ATTACHMENT, texture->GetId(), 0);

      _depthAttachment = texture;

      return texture;
    }

    void AddDepthStencilAttachment() noexcept override
    {
      // TODO: this is created assuming it isn't being sampled from as we don't have a class to represent this with yet.
      // Also we can't actually sample render buffer objects, consider having ColorAttachmentType so we can
      // optimise where possible
      uint rbo;
      glCreateRenderbuffers(1, &rbo);
      if (_samples > 1)
        glNamedRenderbufferStorageMultisample(rbo, _samples, GL_DEPTH24_STENCIL8, _width, _height);
      else
        glNamedRenderbufferStorage(rbo, GL_DEPTH24_STENCIL8, _width, _height);
      glNamedFramebufferRenderbuffer(_id, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
    }

    void DisableReadBuffer() noexcept override
    {
      glNamedFramebufferReadBuffer(_id, GL_NONE);
    }

    void DisableWriteBuffers() noexcept override
    {
      glNamedFramebufferDrawBuffer(_id, GL_NONE);
    }

    void SetReadBuffer(uint attachmentIndex) noexcept override
    {
      KRYS_ASSERT(attachmentIndex >= 0 && attachmentIndex < _colorAttachments.size(),
                  "Index out of range: Max is %d, %d received", _colorAttachments.size() - 1, attachmentIndex);
      glNamedFramebufferReadBuffer(_id, GL_COLOR_ATTACHMENT0 + attachmentIndex);
    }

    void SetWriteBuffer(uint attachmentIndex) noexcept override
    {
      KRYS_ASSERT(attachmentIndex >= 0 && attachmentIndex < _colorAttachments.size(),
                  "Index out of range: Max is %d, %d received", _colorAttachments.size() - 1, attachmentIndex);
      glNamedFramebufferDrawBuffer(_id, GL_COLOR_ATTACHMENT0 + attachmentIndex);
    }

    void SetWriteBuffers(const List<uint> &attachmentIndices) noexcept override
    {
      KRYS_ASSERT(attachmentIndices.size(), "No attachments specified.", 0);
      KRYS_ASSERT(attachmentIndices.size() <= MaxDrawBuffers,
                  "Unable to bind to more than %d draw buffers at one time.", MaxDrawBuffers);

      List<GLenum> attachments;
      for (auto i : attachmentIndices)
      {
        KRYS_ASSERT(i >= 0 && i < _colorAttachments.size(), "Index out of range: %d items, %d received",
                    _colorAttachments.size() - 1, i);
        attachments.push_back(GL_COLOR_ATTACHMENT0 + i);
      }

      glNamedFramebufferDrawBuffers(_id, static_cast<GLsizei>(attachments.size()), attachments.data());
    }

    NO_DISCARD bool IsComplete() noexcept override
    {
      GLenum status = glCheckNamedFramebufferStatus(_id, GL_FRAMEBUFFER);
      return status == GL_FRAMEBUFFER_COMPLETE;
    }

#pragma region Blitting

    void BlitTo(Ref<Framebuffer> other, BoundingBox<int> src, BoundingBox<int> dst, RenderBuffer mask) noexcept override
    {
      Blit(_id, other->GetId(), src, dst, mask);
    }

    void BlitTo(Ref<Framebuffer> other, int width, int height, RenderBuffer mask) noexcept override
    {
      BoundingBox<int> bounds = {0, width, 0, height};
      Blit(_id, other->GetId(), bounds, bounds, mask);
    }

    void BlitToScreen(BoundingBox<int> src, BoundingBox<int> dst, RenderBuffer mask) noexcept override
    {
      Blit(_id, 0, src, dst, mask);
    }

    void BlitToScreen(int width, int height, RenderBuffer mask) noexcept override
    {
      BoundingBox<int> bounds = {0, width, 0, height};
      Blit(_id, 0, bounds, bounds, mask);
    }

    void BlitFrom(Ref<Framebuffer> other, BoundingBox<int> src, BoundingBox<int> dst,
                  RenderBuffer mask) noexcept override
    {
      Blit(other->GetId(), _id, src, dst, mask);
    }

    void BlitFrom(Ref<Framebuffer> other, int width, int height, RenderBuffer mask) noexcept override
    {
      BoundingBox<int> bounds = {0, width, 0, height};
      Blit(other->GetId(), _id, bounds, bounds, mask);
    }

    void BlitFromScreen(BoundingBox<int> src, BoundingBox<int> dst, RenderBuffer mask) noexcept override
    {
      Blit(0, _id, src, dst, mask);
    }

    void BlitFromScreen(int width, int height, RenderBuffer mask) noexcept override
    {
      BoundingBox<int> bounds = {0, width, 0, height};
      Blit(0, _id, bounds, bounds, mask);
    }

    static void Blit(uint32 a, uint32 b, BoundingBox<int> src, BoundingBox<int> dst, RenderBuffer mask) noexcept
    {
      glBlitNamedFramebuffer(a, b, src.Left, src.Bottom, src.Right, src.Top, dst.Left, dst.Bottom, dst.Right, dst.Top,
                             ToGLBufferFlags(mask), GL_NEAREST);
    }

#pragma endregion Blitting
  };
}