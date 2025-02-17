#pragma once

#include "Base/Macros.hpp"
#include "Graphics/Handles.hpp"
#include "Graphics/RenderTargetType.hpp"

namespace Krys::Gfx
{
  struct RenderTargetDescriptor
  {
    uint32 Width;
    uint32 Height;
    RenderTargetType Type;
    bool Multisampled;
  };

  class RenderTarget
  {
  public:
    virtual ~RenderTarget() noexcept = default;

    RenderTarget(RenderTargetHandle handle, TextureHandle texture, const RenderTargetDescriptor& descriptor) noexcept;

    NO_DISCARD RenderTargetHandle GetHandle() const noexcept;

    NO_DISCARD TextureHandle GetTexture() const noexcept;

    NO_DISCARD RenderTargetType GetType() const noexcept;

    NO_DISCARD uint32 GetWidth() const noexcept;

    NO_DISCARD uint32 GetHeight() const noexcept;

    NO_DISCARD bool IsMultisampled() const noexcept;

  protected:
    NO_COPY_MOVE(RenderTarget);

    RenderTargetHandle _handle;
    TextureHandle _texture;
    RenderTargetDescriptor _descriptor;
  };
}