#include "Graphics/RenderTargets/RenderTargetManager.hpp"
#include "Core/WindowManager.hpp"
#include "Graphics/OpenGL/OpenGLFramebuffer.hpp"
#include "Graphics/RenderTargets/RenderTarget.hpp"
#include "Graphics/Textures/TextureManager.hpp"

namespace
{
  using namespace Krys;
  using namespace Krys::Gfx;

  static Unique<RenderTarget> CreateColourRenderTarget(RenderTargetHandle handle,
                                                       const RenderTargetDescriptor &descriptor,
                                                       TextureManager *textureManager) noexcept
  {
    auto sampler = textureManager->CreateSampler(SamplerDescriptor {.UseMipmaps = false});
    auto texture = textureManager->CreateTexture(TextureDescriptor {.Type = TextureType::RenderTargetColour,
                                                                    .Width = descriptor.Width,
                                                                    .Height = descriptor.Height,
                                                                    .Sampler = sampler});

    return CreateUnique<RenderTarget>(handle, texture, descriptor);
  }

  static Unique<RenderTarget> CreateDepthRenderTarget(RenderTargetHandle handle,
                                                      const RenderTargetDescriptor &descriptor,
                                                      TextureManager *textureManager) noexcept
  {
    auto sampler =
      textureManager->CreateSampler(SamplerDescriptor {.AddressModeS = SamplerAddressMode::ClampToBorder,
                                                       .AddressModeT = SamplerAddressMode::ClampToBorder,
                                                       .AddressModeR = SamplerAddressMode::ClampToBorder,
                                                       .BorderColour = Colour {1.0f, 1.0f, 1.0f, 1.0f},
                                                       .UseMipmaps = false});

    auto texture = textureManager->CreateTexture(TextureDescriptor {.Type = TextureType::RenderTargetDepth,
                                                                    .Width = descriptor.Width,
                                                                    .Height = descriptor.Height,
                                                                    .Sampler = sampler});

    return CreateUnique<RenderTarget>(handle, texture, descriptor);
  }

  static Unique<RenderTarget> CreateStencilRenderTarget(RenderTargetHandle handle,
                                                        const RenderTargetDescriptor &descriptor,
                                                        TextureManager *textureManager) noexcept
  {
    auto sampler =
      textureManager->CreateSampler(SamplerDescriptor {.AddressModeS = SamplerAddressMode::ClampToBorder,
                                                       .AddressModeT = SamplerAddressMode::ClampToBorder,
                                                       .AddressModeR = SamplerAddressMode::ClampToBorder,
                                                       .BorderColour = Colour {1.0f, 1.0f, 1.0f, 1.0f},
                                                       .UseMipmaps = false});

    auto texture = textureManager->CreateTexture(TextureDescriptor {.Type = TextureType::RenderTargetStencil,
                                                                    .Width = descriptor.Width,
                                                                    .Height = descriptor.Height,
                                                                    .Sampler = sampler});

    return CreateUnique<RenderTarget>(handle, texture, descriptor);
  }

  static Unique<RenderTarget> CreateDepthStencilRenderTarget(RenderTargetHandle handle,
                                                             const RenderTargetDescriptor &descriptor,
                                                             TextureManager *textureManager) noexcept
  {
    auto sampler =
      textureManager->CreateSampler(SamplerDescriptor {.AddressModeS = SamplerAddressMode::ClampToBorder,
                                                       .AddressModeT = SamplerAddressMode::ClampToBorder,
                                                       .AddressModeR = SamplerAddressMode::ClampToBorder,
                                                       .BorderColour = Colour {1.0f, 1.0f, 1.0f, 1.0f},
                                                       .UseMipmaps = false});
    auto texture =
      textureManager->CreateTexture(TextureDescriptor {.Type = TextureType::RenderTargetDepthStencil,
                                                       .Width = descriptor.Width,
                                                       .Height = descriptor.Height,
                                                       .Sampler = sampler});

    return CreateUnique<RenderTarget>(handle, texture, descriptor);
  }
}

namespace Krys::Gfx
{
  RenderTargetManager::RenderTargetManager(Ptr<WindowManager> windowManager,
                                           Ptr<TextureManager> textureManager) noexcept
      : _windowManager(windowManager), _textureManager(textureManager)
  {
  }

  RenderTargetHandle RenderTargetManager::CreateRenderTarget(RenderTargetType type) noexcept
  {
    auto handle = _renderTargetHandles.Next();
    auto *window = _windowManager->GetCurrentWindow();
    _renderTargets[handle] = CreateRenderTargetImpl(handle, {window->GetWidth(), window->GetHeight(), type});
    return handle;
  }

  RenderTargetHandle
    RenderTargetManager::CreateRenderTarget(const RenderTargetDescriptor &descriptor) noexcept
  {
    auto handle = _renderTargetHandles.Next();
    _renderTargets[handle] = CreateRenderTargetImpl(handle, descriptor);
    return handle;
  }

  RenderTarget *RenderTargetManager::GetRenderTarget(RenderTargetHandle handle) noexcept
  {
    if (const auto it = _renderTargets.find(handle); it != _renderTargets.end())
      return it->second.get();
    return nullptr;
  }

  bool RenderTargetManager::DeleteRenderTarget(RenderTargetHandle handle) noexcept
  {
    if (const auto it = _renderTargets.find(handle); it != _renderTargets.end())
    {
      _renderTargets.erase(it);
      _renderTargetHandles.Recycle(handle);
      return true;
    }
    return false;
  }

  Unique<RenderTarget>
    RenderTargetManager::CreateRenderTargetImpl(RenderTargetHandle handle,
                                                const RenderTargetDescriptor &descriptor) noexcept
  {
    switch (descriptor.Type)
    {
      case RenderTargetType::Colour:  return CreateColourRenderTarget(handle, descriptor, _textureManager);
      case RenderTargetType::Depth:   return CreateDepthRenderTarget(handle, descriptor, _textureManager);
      case RenderTargetType::Stencil: return CreateStencilRenderTarget(handle, descriptor, _textureManager);
      case RenderTargetType::DepthStencil:
        return CreateDepthStencilRenderTarget(handle, descriptor, _textureManager);
      default: KRYS_ASSERT(false, "Invalid RenderTargetType"); return nullptr;
    }
  }
}