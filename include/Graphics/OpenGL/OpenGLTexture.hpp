#pragma once

#include "Graphics/OpenGL/OpenGLSampler.hpp"
#include "Graphics/Texture.hpp"
#include "IO/Images.hpp"

#include <glad/gl.h>

namespace Krys::Gfx::OpenGL
{
  class OpenGLTexture : public Texture
  {
  public:
    OpenGLTexture(const string &resourceName, TextureHandle handle, OpenGLSampler &sampler,
                  TextureUsageHint hint, const IO::Image &data) noexcept;

    ~OpenGLTexture() noexcept override;

    /// @brief Gets the OpenGL texture handle.
    NO_DISCARD GLuint GetNativeHandle() const noexcept;

    /// @brief Gets the bindless handle of the texture.
    NO_DISCARD GLuint64 GetNativeBindlessHandle() const noexcept;

  private:
    GLuint _texture {0};
    GLuint64 _bindlessHandle {0};
  };
}