#include "Graphics/OpenGL/OpenGLTextureManager.hpp"
#include "Graphics/OpenGL/OpenGLSampler.hpp"
#include "Graphics/OpenGL/OpenGLTexture.hpp"

namespace Krys::Gfx::OpenGL
{
  Unique<Sampler> OpenGLTextureManager::CreateSamplerImpl(SamplerHandle handle,
                                                          const SamplerDescriptor &descriptor) noexcept
  {
    return CreateUnique<OpenGLSampler>(handle, descriptor);
  }

  Unique<Texture> OpenGLTextureManager::CreateTextureImpl(const string &name, TextureHandle handle,
                                                          SamplerHandle samplerHandle, const IO::Image &data,
                                                          TextureUsageHint hint) noexcept
  {
    auto *sampler = GetSampler(samplerHandle);
    return CreateUnique<OpenGLTexture>(name, handle, static_cast<OpenGLSampler &>(*sampler), hint, data);
  }

}