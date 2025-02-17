#pragma once

#include "Base/Pointers.hpp"
#include "Base/Types.hpp"
#include "Graphics/Handles.hpp"
#include "Graphics/RenderTargets/RenderTarget.hpp"
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

      RenderTargetHandle Create(RenderTargetType type) noexcept;

      RenderTargetHandle Create(const RenderTargetDescriptor &descriptor) noexcept;

      NO_DISCARD RenderTarget *GetRenderTarget(RenderTargetHandle handle) noexcept;

    protected:
      RenderTargetManager(WindowManager &windowManager, TextureManager &textureManager) noexcept;

      virtual Unique<RenderTarget> CreateImpl(RenderTargetHandle handle,
                                              const RenderTargetDescriptor &descriptor) noexcept = 0;

      WindowManager &_windowManager;
      TextureManager &_textureManager;
      RenderTargetHandleMap<Unique<RenderTarget>> _renderTargets;
      RenderTargetHandleManager _renderTargetHandles {};
    };
  }
}
