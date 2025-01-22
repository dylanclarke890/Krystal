#pragma once

#include "Base/Types.hpp"
#include "Graphics/Handles.hpp"
#include "Graphics/Sampler.hpp"
#include "Graphics/Texture.hpp"
#include "Graphics/TextureManager.hpp"

namespace Krys::Gfx::OpenGL
{
  class OpenGLTextureManager : public TextureManager
  {
  public:
    OpenGLTextureManager() noexcept = default;
    ~OpenGLTextureManager() noexcept override = default;

  protected:
    NO_DISCARD virtual Unique<Sampler>
      CreateSamplerImpl(SamplerHandle handle, const SamplerDescriptor &descriptor) noexcept override;

    NO_DISCARD virtual Unique<Texture>
      CreateTextureImpl(const string &resourceName, TextureHandle handle, SamplerHandle sampler,
                        const IO::Image &data,
                        TextureUsageHint hint = TextureUsageHint::Image) noexcept override;
  };
}