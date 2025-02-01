#include "Graphics/OpenGL/OpenGLTextureManager.hpp"
#include "Graphics/OpenGL/OpenGLSampler.hpp"
#include "Graphics/OpenGL/OpenGLTexture.hpp"

namespace Krys::Gfx::OpenGL
{
  Unique<Sampler> OpenGLTextureManager::CreateSamplerImpl(SamplerHandle handle,
                                                          const SamplerDescriptor &descriptor) noexcept
  {
    KRYS_ASSERT(handle.IsValid(), "Sampler handle is not valid");
    return CreateUnique<OpenGLSampler>(handle, descriptor);
  }

  Unique<Texture> OpenGLTextureManager::CreateTextureImpl(TextureHandle handle,
                                                          const TextureDescriptor &descriptor,
                                                          const List<byte> &data) noexcept
  {
    KRYS_ASSERT(handle.IsValid(), "Texture handle is not valid");
    KRYS_ASSERT(descriptor.Sampler.IsValid(), "Sampler handle is not valid");

    auto *sampler = GetSampler(descriptor.Sampler);
    KRYS_ASSERT(sampler != nullptr, "Sampler not found");

    return CreateUnique<OpenGLTexture>(handle, descriptor, static_cast<OpenGLSampler &>(*sampler), data);
  }

}