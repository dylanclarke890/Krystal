#pragma once

#include "Graphics/Framebuffer.h"
#include "GLTexture2D.h"

namespace Krys
{
  class GLFramebuffer : public Framebuffer
  {
  private:
    uint Id;

  public:
    GLFramebuffer()
    {
      glCreateFramebuffers(1, &Id);
    }

    ~GLFramebuffer() override
    {
      glDeleteFramebuffers(1, &Id);
    }

    void Bind() noexcept override
    {
      glBindFramebuffer(GL_FRAMEBUFFER, Id);
    }

    void Unbind() noexcept override
    {
      glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void AddColorAttachment(int width, int height) noexcept override
    {
      Ref<Texture2D> texture = CreateRef<GLTexture2D>(width, height);
      texture->SetTextureWrapModes(TextureWrapMode::ClampToEdge, TextureWrapMode::ClampToEdge);

      glNamedFramebufferTexture(Id, static_cast<GLenum>(GL_COLOR_ATTACHMENT0 + ColorAttachments.size()), texture->GetId(), 0);
      ColorAttachments.push_back(texture);
    }

    void AddDepthStencilAttachment(int width, int height) noexcept override
    {
      // TODO: this is created assuming it isn't being sampled.
      uint rbo;
      glCreateRenderbuffers(1, &rbo);
      glNamedRenderbufferStorage(rbo, GL_DEPTH24_STENCIL8, width, height);
      glNamedFramebufferRenderbuffer(Id, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
    }
  };
}