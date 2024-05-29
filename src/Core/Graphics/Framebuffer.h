#pragma once

#include <vector>
#include "Core.h"
#include "Texture2D.h"

namespace Krys
{
  class Framebuffer
  {
  protected:
    std::vector<Ref<Texture2D>> ColorAttachments;

  public:
    virtual ~Framebuffer() = default;
    virtual void Bind() noexcept = 0;
    virtual void Unbind() noexcept = 0;

    virtual void AddColorAttachment(int width, int height) noexcept = 0;
    virtual void AddDepthStencilAttachment(int width, int height) noexcept = 0;

    Ref<Texture2D> GetColorAttachment(uint index = 0)
    {
      KRYS_ASSERT(index < ColorAttachments.size(), "Index out of bounds", 0);
      return ColorAttachments[index];
    }
  };
}