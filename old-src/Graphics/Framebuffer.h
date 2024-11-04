#pragma once

#include "Core.h"

#include "Graphics/Textures/Texture2D.h"
#include "Graphics/Textures/TextureCubemap.h"
#include "Graphics/Enums.h"
#include "Maths/BoundingBox.h"

#include <functional>

namespace Krys::Graphics
{
  class Framebuffer
  {
  protected:
    inline static int MaxColorAttachments = 0;
    inline static int MaxDrawBuffers = 0;

    uint32 _id;
    uint32 _width, _height, _samples;
    List<Ref<Texture2D>> _colorAttachments;
    Ref<Texture> _depthAttachment;

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

    virtual void BlitTo(Ref<Framebuffer> other, BoundingBox<int> src, BoundingBox<int> dst, RenderBuffer mask) noexcept = 0;
    virtual void BlitTo(Ref<Framebuffer> other, int width, int height, RenderBuffer mask) noexcept = 0;
    virtual void BlitToScreen(BoundingBox<int> src, BoundingBox<int> dst, RenderBuffer mask) noexcept = 0;
    virtual void BlitToScreen(int width, int height, RenderBuffer mask) noexcept = 0;

    virtual void BlitFrom(Ref<Framebuffer> other, BoundingBox<int> src, BoundingBox<int> dst, RenderBuffer mask) noexcept = 0;
    virtual void BlitFrom(Ref<Framebuffer> other, int width, int height, RenderBuffer mask) noexcept = 0;
    virtual void BlitFromScreen(BoundingBox<int> src, BoundingBox<int> dst, RenderBuffer mask) noexcept = 0;
    virtual void BlitFromScreen(int width, int height, RenderBuffer mask) noexcept = 0;

    NO_DISCARD uint32 GetId() const noexcept
    {
      return _id;
    }

    NO_DISCARD uint32 GetWidth() const noexcept
    {
      return _width;
    }

    NO_DISCARD uint32 GetHeight() const noexcept
    {
      return _height;
    }

    NO_DISCARD Ref<Texture2D> GetColorAttachment(uint index = 0)
    {
      KRYS_ASSERT(index < _colorAttachments.size(), "Index out of bounds", 0);
      return _colorAttachments[index];
    }

    NO_DISCARD Ref<Texture> GetDepthAttachment()
    {
      return _depthAttachment;
    }

    static void SetDriverLimits(int maxColorAttachments, int maxDrawBuffers) noexcept
    {
      MaxColorAttachments = maxColorAttachments;
      MaxDrawBuffers = maxDrawBuffers;
    }
  };

  class PingPongFramebuffer
  {
  private:
    Ref<Framebuffer> _a, _b;
    std::function<void()> _onBeforeRenderPasses;
    std::function<void()> _onRenderStep;
    std::function<void()> _onAfterRenderPasses;

  public:
    PingPongFramebuffer(Ref<Framebuffer> a, Ref<Framebuffer> b)
        : _a(a), _b(b), _onBeforeRenderPasses(nullptr), _onRenderStep(nullptr), _onAfterRenderPasses(nullptr)
    {
      KRYS_ASSERT(a->GetWidth() == b->GetWidth() && a->GetHeight() == b->GetHeight(), "Framebuffers must be the same size", 0);
    }

    Ref<Texture> ExecutePasses(Ref<Texture> initialTexture, uint amount)
    {
      KRYS_ASSERT(initialTexture && amount > 0, "invalid arguments", 0);
      KRYS_ASSERT(_onRenderStep, "OnRenderStep must be set", 0);

      if (_onBeforeRenderPasses)
        _onBeforeRenderPasses();

      auto current = _a;
      auto other = _b;
      bool first = true;
      for (uint i = 0; i < amount; i++)
      {
        current->Bind(FramebufferBindType::Draw);
        if (first)
          initialTexture->Bind();
        else
          other->GetColorAttachment()->Bind();

        _onRenderStep();

        if (i != amount)
        {
          if (current == _a)
          {
            current = _b;
            other = _a;
          }
          else
          {
            current = _a;
            other = _b;
          }
        }

        first = false;
      }

      if (_onAfterRenderPasses)
        _onAfterRenderPasses();

      current->Unbind();
      return current->GetColorAttachment();
    }

    void SetBeforeRenderPassesCallback(std::function<void()> func)
    {
      KRYS_ASSERT(func, "func must not be null", 0);
      _onBeforeRenderPasses = func;
    }

    void SetRenderStepCallback(std::function<void()> func)
    {
      KRYS_ASSERT(func, "func must not be null", 0);
      _onRenderStep = func;
    }

    void SetAfterRenderPassesCallback(std::function<void()> func)
    {
      KRYS_ASSERT(func, "func must not be null", 0);
      _onAfterRenderPasses = func;
    }

    NO_DISCARD bool IsComplete() noexcept
    {
      KRYS_ASSERT(_a && _b, "A or B framebuffer is null", 0);
      return _a->IsComplete() && _b->IsComplete();
    }

    NO_DISCARD uint32 GetWidth() const noexcept
    {
      return _a->GetWidth();
    }

    NO_DISCARD uint32 GetHeight() const noexcept
    {
      return _a->GetHeight();
    }
  };
}