#pragma once

#include "Base/Types.hpp"
#include "Graphics/Handles.hpp"
#include "Graphics/Textures/Sampler.hpp"
#include "Graphics/Textures/Texture.hpp"
#include "Graphics/Textures/TextureManager.hpp"

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

    NO_DISCARD virtual Unique<Texture> CreateTextureImpl(TextureHandle handle,
                                                         const TextureDescriptor &descriptor,
                                                         const List<byte> &data = {}) noexcept override;
  };
}