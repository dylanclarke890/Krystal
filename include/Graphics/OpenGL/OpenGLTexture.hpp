#pragma once

#include "Graphics/OpenGL/OpenGLSampler.hpp"
#include "Graphics/Textures/Texture.hpp"
#include "IO/Images.hpp"

#include <glad/gl.h>

namespace Krys::Gfx::OpenGL
{
  class OpenGLTexture : public Texture
  {
  public:
  OpenGLTexture(TextureHandle handle, const TextureDescriptor &descriptor, OpenGLSampler &sampler,
                      const List<byte> &data) noexcept;

  ~OpenGLTexture() noexcept override;

  /// @brief Gets the OpenGL texture handle.
  NO_DISCARD GLuint GetNativeHandle() const noexcept;

  /// @brief Gets the bindless handle of the texture.
  NO_DISCARD GLuint64 GetNativeBindlessHandle() const noexcept;

  void Bind(uint32 unit) const noexcept;

  /// @brief Checks if the texture is bindless.
  NO_DISCARD bool IsBindless() const noexcept;
  
private:
  GLuint _id {0};
  GLuint64 _bindlessHandle {0};
  };
}