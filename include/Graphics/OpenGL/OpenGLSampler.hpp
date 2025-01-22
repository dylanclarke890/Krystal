#pragma once

#include "Graphics/Sampler.hpp"

#include <glad/gl.h>

namespace Krys::Gfx::OpenGL
{
  class OpenGLSampler : public Sampler
  {
  public:
    OpenGLSampler(SamplerHandle handle, const SamplerDescriptor &descriptor) noexcept;
    ~OpenGLSampler() noexcept override;

    /// @brief Gets the OpenGL handle of the sampler.
    NO_DISCARD GLuint GetNativeHandle() const noexcept;

  private:
    /// @brief The OpenGL handle of the sampler.
    GLuint _sampler {0u};
  };
}