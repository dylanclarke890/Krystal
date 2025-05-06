#pragma once

#include "Graphics/OpenGL/OpenGLSampler.hpp"
#include "Graphics/Textures/Texture.hpp"
#include "IO/Images.hpp"

#include <glad/gl.h>

namespace Krys::Gfx::OpenGL
{
  class OpenGLBindlessTexture : public Texture
  {
  public:
    OpenGLBindlessTexture(TextureHandle handle, const TextureDescriptor &descriptor, OpenGLSampler &sampler,
                  const List<byte> &data) noexcept;

    ~OpenGLBindlessTexture() noexcept override;

    /// @brief Gets the OpenGL texture handle.
    NO_DISCARD GLuint GetNativeHandle() const noexcept;

    /// @brief Gets the bindless handle of the texture.
    NO_DISCARD GLuint64 GetNativeBindlessHandle() const noexcept;

  private:
    GLuint _id {0};
    GLuint64 _bindlessHandle {0};
  };
}