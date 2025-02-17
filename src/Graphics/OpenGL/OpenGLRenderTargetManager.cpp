#include "Graphics/OpenGL/OpenGLRenderTargetManager.hpp"
#include "Graphics/Textures/TextureManager.hpp"

namespace Krys::Gfx::OpenGL
{
  OpenGLRenderTargetManager::OpenGLRenderTargetManager(WindowManager *windowManager,
                                                       TextureManager *textureManager) noexcept
      : RenderTargetManager(windowManager, textureManager)
  {
  }

  Unique<RenderTarget>
    OpenGLRenderTargetManager::CreateRenderTargetImpl(RenderTargetHandle handle,
                                                      const RenderTargetDescriptor &descriptor) noexcept
  {
    switch (descriptor.Type)
    {
      case RenderTargetType::Colour:       return CreateColourRenderTarget(handle, descriptor);
      case RenderTargetType::Depth:        return CreateDepthRenderTarget(handle, descriptor);
      case RenderTargetType::Stencil:      return CreateStencilRenderTarget(handle, descriptor);
      case RenderTargetType::DepthStencil: return CreateDepthStencilRenderTarget(handle, descriptor);
      default:                             KRYS_ASSERT(false, "Invalid RenderTargetType"); return nullptr;
    }
  }

  Unique<RenderTarget>
    OpenGLRenderTargetManager::CreateColourRenderTarget(RenderTargetHandle handle,
                                                        const RenderTargetDescriptor &descriptor) noexcept
  {
    auto sampler = _textureManager->CreateSampler(SamplerDescriptor {.UseMipmaps = false});
    auto texture = _textureManager->CreateTexture(TextureDescriptor {.Type = TextureType::RenderTargetColour,
                                                                     .Width = descriptor.Width,
                                                                     .Height = descriptor.Height,
                                                                     .Sampler = sampler});

    return CreateUnique<RenderTarget>(handle, texture, descriptor);
  }

  Unique<RenderTarget>
    OpenGLRenderTargetManager::CreateDepthRenderTarget(RenderTargetHandle handle,
                                                       const RenderTargetDescriptor &descriptor) noexcept
  {
    auto sampler =
      _textureManager->CreateSampler(SamplerDescriptor {.AddressModeS = SamplerAddressMode::ClampToBorder,
                                                        .AddressModeT = SamplerAddressMode::ClampToBorder,
                                                        .AddressModeR = SamplerAddressMode::ClampToBorder,
                                                        .BorderColour = Colour {1.0f, 1.0f, 1.0f, 1.0f},
                                                        .UseMipmaps = false});

    auto texture = _textureManager->CreateTexture(TextureDescriptor {.Type = TextureType::RenderTargetDepth,
                                                                     .Width = descriptor.Width,
                                                                     .Height = descriptor.Height,
                                                                     .Sampler = sampler});

    return CreateUnique<RenderTarget>(handle, texture, descriptor);
  }

  Unique<RenderTarget>
    OpenGLRenderTargetManager::CreateStencilRenderTarget(RenderTargetHandle handle,
                                                         const RenderTargetDescriptor &descriptor) noexcept
  {
    auto sampler =
      _textureManager->CreateSampler(SamplerDescriptor {.AddressModeS = SamplerAddressMode::ClampToBorder,
                                                        .AddressModeT = SamplerAddressMode::ClampToBorder,
                                                        .AddressModeR = SamplerAddressMode::ClampToBorder,
                                                        .BorderColour = Colour {1.0f, 1.0f, 1.0f, 1.0f},
                                                        .UseMipmaps = false});

    auto texture = _textureManager->CreateTexture(TextureDescriptor {.Type = TextureType::RenderTargetStencil,
                                                                     .Width = descriptor.Width,
                                                                     .Height = descriptor.Height,
                                                                     .Sampler = sampler});

    return CreateUnique<RenderTarget>(handle, texture, descriptor);
  }

  Unique<RenderTarget> OpenGLRenderTargetManager::CreateDepthStencilRenderTarget(
    RenderTargetHandle handle, const RenderTargetDescriptor &descriptor) noexcept
  {
    auto sampler =
      _textureManager->CreateSampler(SamplerDescriptor {.AddressModeS = SamplerAddressMode::ClampToBorder,
                                                        .AddressModeT = SamplerAddressMode::ClampToBorder,
                                                        .AddressModeR = SamplerAddressMode::ClampToBorder,
                                                        .BorderColour = Colour {1.0f, 1.0f, 1.0f, 1.0f},
                                                        .UseMipmaps = false});
    auto texture =
      _textureManager->CreateTexture(TextureDescriptor {.Type = TextureType::RenderTargetDepthStencil,
                                                        .Width = descriptor.Width,
                                                        .Height = descriptor.Height,
                                                        .Sampler = sampler});

    return CreateUnique<RenderTarget>(handle, texture, descriptor);
  }
}