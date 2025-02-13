#include "Graphics/RenderTargetManager.hpp"
#include "Core/WindowManager.hpp"
#include "Graphics/TextureManager.hpp"

namespace Krys::Gfx
{
  RenderTargetManager::RenderTargetManager(WindowManager &windowManager,
                                           TextureManager &textureManager) noexcept
      : _windowManager(windowManager), _textureManager(textureManager)
  {
  }

  RenderTargetHandle RenderTargetManager::Create(RenderTargetType type) noexcept
  {
    auto handle = _renderTargetHandles.Next();
    auto *window = _windowManager.GetCurrentWindow();
    _renderTargets[handle] = CreateImpl(handle, {window->GetWidth(), window->GetHeight(), type});
    return handle;
  }

  RenderTargetHandle RenderTargetManager::Create(const RenderTargetDescriptor &descriptor) noexcept
  {
    auto handle = _renderTargetHandles.Next();
    _renderTargets[handle] = CreateImpl(handle, descriptor);
    return handle;
  }

  RenderTarget *RenderTargetManager::GetRenderTarget(RenderTargetHandle handle) noexcept
  {
    if (const auto it = _renderTargets.find(handle); it != _renderTargets.end())
      return it->second.get();
    return nullptr;
  }
}