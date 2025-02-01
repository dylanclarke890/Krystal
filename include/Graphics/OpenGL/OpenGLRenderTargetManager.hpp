#pragma once

#include "Base/Types.hpp"
#include "Graphics/RenderTargetManager.hpp"

namespace Krys::Gfx::OpenGL
{
  class OpenGLRenderTargetManager : public RenderTargetManager
  {
  public:
    OpenGLRenderTargetManager(WindowManager &windowManager, TextureManager &textureManager) noexcept;

  protected:
    Unique<RenderTarget> CreateImpl(RenderTargetHandle handle,
                                    const RenderTargetDescriptor &descriptor) noexcept override;

    Unique<RenderTarget> CreateColourRenderTarget(RenderTargetHandle handle,
                                                 const RenderTargetDescriptor &descriptor) noexcept;

    Unique<RenderTarget> CreateDepthRenderTarget(RenderTargetHandle handle,
                                                 const RenderTargetDescriptor &descriptor) noexcept;

    Unique<RenderTarget> CreateStencilRenderTarget(RenderTargetHandle handle,
                                                   const RenderTargetDescriptor &descriptor) noexcept;

    Unique<RenderTarget> CreateDepthStencilRenderTarget(RenderTargetHandle handle,
                                                        const RenderTargetDescriptor &descriptor) noexcept;
  };
}