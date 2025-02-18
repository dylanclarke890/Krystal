#pragma once

#include "Base/Pointers.hpp"
#include "Base/Types.hpp"
#include "Graphics/Handles.hpp"
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
      RenderTargetManager(Ptr<WindowManager> windowManager, Ptr<TextureManager> textureManager) noexcept;
      
      ~RenderTargetManager() noexcept = default;

      RenderTargetHandle CreateRenderTarget(RenderTargetType type) noexcept;

      RenderTargetHandle CreateRenderTarget(const RenderTargetDescriptor &descriptor) noexcept;

      NO_DISCARD RenderTarget *GetRenderTarget(RenderTargetHandle handle) noexcept;

      bool DeleteRenderTarget(RenderTargetHandle handle) noexcept;

    protected:

      Unique<RenderTarget> CreateRenderTargetImpl(RenderTargetHandle handle,
                                                  const RenderTargetDescriptor &descriptor) noexcept;

      Ptr<WindowManager> _windowManager;
      Ptr<TextureManager> _textureManager;
      RenderTargetHandleMap<Unique<RenderTarget>> _renderTargets;
      RenderTargetHandleManager _renderTargetHandles {};
    };
  }
}
