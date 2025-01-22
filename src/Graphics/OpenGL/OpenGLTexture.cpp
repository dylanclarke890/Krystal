#include "Graphics/OpenGL/OpenGLTexture.hpp"
#include "Graphics/OpenGL/OpenGLSampler.hpp"

namespace Krys::Gfx::OpenGL
{
  /// @brief Creates an image texture using SRGB color space.
  static void CreateImageTexture(GLuint texture, const SamplerDescriptor &sampler,
                                 const IO::Image &img) noexcept
  {
    int levels = !sampler.UseMipmaps ? 1 : static_cast<int>(std::log2(std::max(img.Width, img.Height))) + 1;
    // TODO: this should be srgb instead.
    GLenum internalFormat = img.Channels == 4 ? GL_RGBA8 : GL_RGB8;
    GLenum format = img.Channels == 4 ? GL_RGBA : GL_RGB;

    ::glTextureStorage2D(texture, levels, internalFormat, img.Width, img.Height);
    ::glTextureSubImage2D(texture, 0, 0, 0, img.Width, img.Height, format, GL_UNSIGNED_BYTE, img.Data.data());

    if (sampler.UseMipmaps)
      ::glGenerateTextureMipmap(texture);
  }

  /// @brief Creates a data texture using RGB color space.
  static void CreateDataTexture(GLuint texture, const SamplerDescriptor &sampler,
                                const IO::Image &img) noexcept
  {
    int levels = !sampler.UseMipmaps ? 1 : static_cast<int>(std::log2(std::max(img.Width, img.Height))) + 1;
    GLenum format = img.Channels == 4 ? GL_RGBA : GL_RGB;
    GLenum internalFormat = img.Channels == 4 ? GL_RGBA8 : GL_RGB8;

    ::glTextureStorage2D(texture, levels, internalFormat, img.Width, img.Height);
    ::glTextureSubImage2D(texture, 0, 0, 0, img.Width, img.Height, format, GL_UNSIGNED_BYTE, img.Data.data());

    if (sampler.UseMipmaps)
      ::glGenerateTextureMipmap(texture);
  }

  /// @brief Creates a depth texture.
  static void CreateDepthTexture(GLuint texture, const IO::Image &img) noexcept
  {
    ::glTextureStorage2D(texture, 1, GL_DEPTH_COMPONENT, img.Width, img.Height);
  }

  /// @brief Creates a render target texture.
  static void CreateRenderTargetTexture(GLuint texture, const IO::Image &img) noexcept
  {
    ::glTextureStorage2D(texture, 1, GL_RGBA8, img.Width, img.Height);
  }

  static GLint CreateTexture(const SamplerDescriptor &sampler, TextureUsageHint hint,
                             const IO::Image &img) noexcept
  {
    GLuint texture;
    ::glCreateTextures(GL_TEXTURE_2D, 1, &texture);

    switch (hint)
    {
      case TextureUsageHint::Image:        CreateImageTexture(texture, sampler, img); break;
      case TextureUsageHint::Data:         CreateDataTexture(texture, sampler, img); break;
      case TextureUsageHint::Depth:        CreateDepthTexture(texture, img); break;
      case TextureUsageHint::RenderTarget: CreateRenderTargetTexture(texture, img); break;
      default:                             KRYS_ASSERT(false, "Unknown enum value: TextureUsageHint"); break;
    }

    return texture;
  }

  OpenGLTexture::OpenGLTexture(const string &name, TextureHandle handle, OpenGLSampler &sampler,
                               TextureUsageHint hint, const IO::Image &img) noexcept
      : Texture(name, handle, sampler.GetHandle(), hint),
        _texture(CreateTexture(sampler.GetDescriptor(), hint, img))
  {
    _bindlessHandle = ::glGetTextureSamplerHandleARB(_texture, sampler.GetNativeHandle());
    ::glMakeTextureHandleResidentARB(_bindlessHandle);

    KRYS_ASSERT(_bindlessHandle != 0 && ::glIsTextureHandleResidentARB(_bindlessHandle),
                "Failed to make texture handle resident");
  }

  OpenGLTexture::~OpenGLTexture() noexcept
  {
    ::glMakeTextureHandleNonResidentARB(_bindlessHandle);
    ::glDeleteTextures(1, &_texture);
  }

  GLuint OpenGLTexture::GetNativeHandle() const noexcept
  {
    return _texture;
  }

  GLuint64 OpenGLTexture::GetNativeBindlessHandle() const noexcept
  {
    return _bindlessHandle;
  }
}