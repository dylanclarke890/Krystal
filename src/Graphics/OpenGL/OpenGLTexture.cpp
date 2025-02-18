#include "Graphics/OpenGL/OpenGLTexture.hpp"
#include "Graphics/OpenGL/OpenGLSampler.hpp"

namespace Krys::Gfx::OpenGL
{
  /// @brief Creates an image texture using SRGB color space.
  static void CreateImageTexture(GLuint texture, const TextureDescriptor &desc,
                                 const SamplerDescriptor &sampler, const List<byte> &data) noexcept
  {
    int levels = !sampler.UseMipmaps ? 1 : static_cast<int>(std::log2(std::max(desc.Width, desc.Height))) + 1;
    // TODO: this should be srgb instead.
    GLenum internalFormat = desc.Channels == 4 ? GL_RGBA8 : GL_RGB8;
    GLenum format = desc.Channels == 4 ? GL_RGBA : GL_RGB;

    ::glTextureStorage2D(texture, levels, internalFormat, desc.Width, desc.Height);
    ::glTextureSubImage2D(texture, 0, 0, 0, desc.Width, desc.Height, format, GL_UNSIGNED_BYTE, data.data());

    if (sampler.UseMipmaps)
      ::glGenerateTextureMipmap(texture);
  }

  /// @brief Creates a data texture using RGB color space.
  static void CreateDataTexture(GLuint texture, const TextureDescriptor &desc,
                                const SamplerDescriptor &sampler, const List<byte> &data) noexcept
  {
    int levels = !sampler.UseMipmaps ? 1 : static_cast<int>(std::log2(std::max(desc.Width, desc.Height))) + 1;
    GLenum format = desc.Channels == 4 ? GL_RGBA : GL_RGB;
    GLenum internalFormat = desc.Channels == 4 ? GL_RGBA8 : GL_RGB8;

    ::glTextureStorage2D(texture, levels, internalFormat, desc.Width, desc.Height);
    ::glTextureSubImage2D(texture, 0, 0, 0, desc.Width, desc.Height, format, GL_UNSIGNED_BYTE, data.data());

    if (sampler.UseMipmaps)
      ::glGenerateTextureMipmap(texture);
  }

  /// @brief Creates a depth texture.
  static void CreateRenderTargetDepthTexture(GLuint texture, const TextureDescriptor &desc) noexcept
  {
    ::glTextureStorage2D(texture, 1, GL_DEPTH_COMPONENT24, desc.Width, desc.Height);
  }

  /// @brief Creates a render target texture.
  static void CreateRenderTargetColourTexture(GLuint texture, const TextureDescriptor &desc) noexcept
  {
    ::glTextureStorage2D(texture, 1, GL_RGBA8, desc.Width, desc.Height);
  }

  /// @brief Creates a stencil texture.
  static void CreateRenderTargetStencilTexture(GLuint texture, const TextureDescriptor &desc) noexcept
  {
    ::glTextureStorage2D(texture, 1, GL_STENCIL_INDEX8, desc.Width, desc.Height);
  }

  /// @brief Creates a depth stencil texture.
  static void CreateRenderTargetDepthStencilTexture(GLuint texture, const TextureDescriptor &desc) noexcept
  {
    ::glTextureStorage2D(texture, 1, GL_DEPTH24_STENCIL8, desc.Width, desc.Height);
  }

  static GLint CreateTexture(const TextureDescriptor &descriptor, const SamplerDescriptor &sampler,
                             const List<byte> &data) noexcept
  {
    GLuint texture;
    ::glCreateTextures(GL_TEXTURE_2D, 1, &texture);

    switch (descriptor.Type)
    {
      case TextureType::Image:               CreateImageTexture(texture, descriptor, sampler, data); break;
      case TextureType::Data:                CreateDataTexture(texture, descriptor, sampler, data); break;
      case TextureType::RenderTargetDepth:   CreateRenderTargetDepthTexture(texture, descriptor); break;
      case TextureType::RenderTargetColour:  CreateRenderTargetColourTexture(texture, descriptor); break;
      case TextureType::RenderTargetStencil: CreateRenderTargetStencilTexture(texture, descriptor); break;
      case TextureType::RenderTargetDepthStencil:
        CreateRenderTargetDepthStencilTexture(texture, descriptor);
        break;
      default: KRYS_ASSERT(false, "Unknown enum value: TextureType"); break;
    }

    return texture;
  }

  static GLuint64 CreateBindlessHandle(GLuint textureHandle, GLuint samplerHandle) noexcept
  {
    GLuint64 handle = ::glGetTextureSamplerHandleARB(textureHandle, samplerHandle);
    ::glMakeTextureHandleResidentARB(handle);
    KRYS_ASSERT(handle != 0 && ::glIsTextureHandleResidentARB(handle),
                "Failed to make texture handle resident");
    return handle;
  }

  OpenGLTexture::OpenGLTexture(TextureHandle handle, const TextureDescriptor &descriptor,
                               OpenGLSampler &sampler, const List<byte> &data) noexcept
      : Texture(handle, descriptor), _id(CreateTexture(descriptor, sampler.GetDescriptor(), data))
  {
    _bindlessHandle = CreateBindlessHandle(_id, sampler.GetNativeHandle());
  }

  OpenGLTexture::~OpenGLTexture() noexcept
  {
    ::glMakeTextureHandleNonResidentARB(_bindlessHandle);
    ::glDeleteTextures(1, &_id);
  }

  GLuint OpenGLTexture::GetNativeHandle() const noexcept
  {
    return _id;
  }

  GLuint64 OpenGLTexture::GetNativeBindlessHandle() const noexcept
  {
    return _bindlessHandle;
  }
}