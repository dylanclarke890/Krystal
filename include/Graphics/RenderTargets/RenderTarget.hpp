#pragma once

#include "Base/Macros.hpp"
#include "Graphics/Handles.hpp"
#include "Graphics/RenderTargets/RenderTargetDescriptor.hpp"
#include "Graphics/RenderTargets/RenderTargetType.hpp"

namespace Krys::Gfx
{
  class RenderTarget
  {
  public:
    NO_COPY_MOVE(RenderTarget);

    RenderTarget(RenderTargetHandle handle, TextureHandle texture,
                 const RenderTargetDescriptor &descriptor) noexcept;

    virtual ~RenderTarget() noexcept = default;

    NO_DISCARD RenderTargetHandle GetHandle() const noexcept;

    NO_DISCARD TextureHandle GetTexture() const noexcept;

    NO_DISCARD RenderTargetType GetType() const noexcept;

    NO_DISCARD uint32 GetWidth() const noexcept;

    NO_DISCARD uint32 GetHeight() const noexcept;

    NO_DISCARD bool IsMultisampled() const noexcept;

  protected:
    RenderTargetHandle _handle;
    TextureHandle _texture;
    RenderTargetDescriptor _descriptor;
  };
}