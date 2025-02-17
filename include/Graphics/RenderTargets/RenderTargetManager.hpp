#pragma once

#include "Base/Pointers.hpp"
#include "Base/Types.hpp"
#include "Graphics/Handles.hpp"
#include "Graphics/RenderTargets/Framebuffer.hpp"
#include "Graphics/RenderTargets/FramebufferDescriptor.hpp"
#include "Graphics/RenderTargets/RenderTarget.hpp"
#include "Graphics/RenderTargets/RenderTargetDescriptor.hpp"
#include "Graphics/RenderTargets/RenderTargetType.hpp"

namespace Krys
{
  class WindowManager;

  namespace Gfx
  {
    class TextureManager;

    class RenderTargetManager
    {
    public:
      virtual ~RenderTargetManager() noexcept = default;

      RenderTargetHandle CreateRenderTarget(RenderTargetType type) noexcept;

      RenderTargetHandle CreateRenderTarget(const RenderTargetDescriptor &descriptor) noexcept;

      NO_DISCARD RenderTarget *GetRenderTarget(RenderTargetHandle handle) noexcept;

      bool DeleteRenderTarget(RenderTargetHandle handle) noexcept;

      NO_DISCARD FramebufferHandle CreateFramebuffer(const FramebufferDescriptor &descriptor) noexcept;

      NO_DISCARD Framebuffer *GetFramebuffer(FramebufferHandle handle) noexcept;

      bool DeleteFramebuffer(FramebufferHandle handle) noexcept;

    protected:
      RenderTargetManager(Ptr<WindowManager> windowManager, Ptr<TextureManager> textureManager) noexcept;

      virtual Unique<RenderTarget>
        CreateRenderTargetImpl(RenderTargetHandle handle,
                               const RenderTargetDescriptor &descriptor) noexcept = 0;

      virtual Unique<Framebuffer> CreateFramebufferImpl(FramebufferHandle handle,
                                                        const FramebufferDescriptor &descriptor) noexcept = 0;

      Ptr<WindowManager> _windowManager;
      Ptr<TextureManager> _textureManager;
      RenderTargetHandleMap<Unique<RenderTarget>> _renderTargets;
      RenderTargetHandleManager _renderTargetHandles {};
    };
  }
}
