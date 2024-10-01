#pragma once

#include "Core.h"

#include "Graphics/Textures/Texture2D.h"
#include "Graphics/Textures/TextureCubemap.h"
#include "Graphics/Enums.h"
#include "Maths/Maths.h"

#include <functional>

namespace Krys
{
  class Framebuffer
  {
  protected:
    uint32 Id;
    uint32 Width, Height, Samples;
    List<Ref<Texture2D>> ColorAttachments;
    Ref<Texture> DepthAttachment;

  public:
    virtual ~Framebuffer() = default;
    virtual void Bind(FramebufferBindType bindType = FramebufferBindType::ReadAndDraw) noexcept = 0;
    virtual void Unbind() noexcept = 0;

    virtual Ref<Texture2D> AddColorAttachment() noexcept = 0;
    virtual Ref<Texture2D> AddColorAttachment(TextureInternalFormat internalFormat) noexcept = 0;
    virtual Ref<Texture2D> AddDepthAttachment() noexcept = 0;
    virtual Ref<TextureCubemap> AddDepthCubemapAttachment() noexcept = 0;
    virtual void AddDepthStencilAttachment() noexcept = 0;

    virtual void DisableReadBuffer() noexcept = 0;
    virtual void DisableWriteBuffers() noexcept = 0;
    virtual void SetReadBuffer(uint attachmentIndex) noexcept = 0;
    virtual void SetWriteBuffer(uint attachmentIndex) noexcept = 0;
    virtual void SetWriteBuffers(const List<uint> &attachmentIndices) noexcept = 0;

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

  class PingPongFramebuffer
  {
  private:
    Ref<Framebuffer> A, B;
    std::function<void()> OnBeforeRenderPasses;
    std::function<void()> OnRenderStep;
    std::function<void()> OnAfterRenderPasses;

  public:
    PingPongFramebuffer(Ref<Framebuffer> a, Ref<Framebuffer> b)
        : A(a), B(b), OnBeforeRenderPasses(nullptr), OnRenderStep(nullptr), OnAfterRenderPasses(nullptr)
    {
      KRYS_ASSERT(a->GetWidth() == b->GetWidth() && a->GetHeight() == b->GetHeight(), "Framebuffers must be the same size", 0);
    }

    Ref<Texture> ExecutePasses(Ref<Texture> initialTexture, uint amount)
    {
      KRYS_ASSERT(initialTexture && amount > 0, "invalid arguments", 0);
      KRYS_ASSERT(OnRenderStep, "OnRenderStep must be set", 0);

      if (OnBeforeRenderPasses)
        OnBeforeRenderPasses();

      auto current = A;
      auto other = B;
      bool first = true;
      for (uint i = 0; i < amount; i++)
      {
        current->Bind(FramebufferBindType::Draw);
        if (first)
          initialTexture->Bind();
        else
          other->GetColorAttachment()->Bind();

        OnRenderStep();

        if (i != amount)
        {
          if (current == A)
          {
            current = B;
            other = A;
          }
          else
          {
            current = A;
            other = B;
          }
        }

        first = false;
      }

      if (OnAfterRenderPasses)
        OnAfterRenderPasses();

      current->Unbind();
      return current->GetColorAttachment();
    }

    void SetBeforeRenderPassesCallback(std::function<void()> func)
    {
      KRYS_ASSERT(func, "func must not be null", 0);
      OnBeforeRenderPasses = func;
    }

    void SetRenderStepCallback(std::function<void()> func)
    {
      KRYS_ASSERT(func, "func must not be null", 0);
      OnRenderStep = func;
    }

    void SetAfterRenderPassesCallback(std::function<void()> func)
    {
      KRYS_ASSERT(func, "func must not be null", 0);
      OnAfterRenderPasses = func;
    }

    NO_DISCARD bool IsComplete() noexcept
    {
      KRYS_ASSERT(A && B, "A or B framebuffer is null", 0);
      return A->IsComplete() && B->IsComplete();
    }

    NO_DISCARD uint32 GetWidth() const noexcept
    {
      return A->GetWidth();
    }

    NO_DISCARD uint32 GetHeight() const noexcept
    {
      return A->GetHeight();
    }
  };
}