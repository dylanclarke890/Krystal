#include <stb_image.h>

#include "OpenGL/Textures/GLTextureCubemap.h"

namespace Krys::OpenGL
{
  GLTextureCubemap::GLTextureCubemap(std::array<string, 6> faces, TextureInternalFormat internalFormat)
  {
    _internalFormat = internalFormat;

    glCreateTextures(GL_TEXTURE_CUBE_MAP, 1, &_id);

    stbi_set_flip_vertically_on_load(false);

    int width, height, channels;
    auto data = stbi_load(faces[0].c_str(), &width, &height, &channels, 0);

    KRYS_ASSERT(data[0], "Failed to load first face!", 0);
    KRYS_ASSERT(channels == 3 || channels == 4, "Unsupported number of color channels.", 0);
    KRYS_ASSERT(width <= MaxTextureSize, "Texture width exceeds Max Texture Size (Max %d, %d received).",
                MaxTextureSize, width);
    KRYS_ASSERT(height <= MaxTextureSize, "Texture height exceeds Max Texture Size (Max %d, %d received).",
                MaxTextureSize, height);

    if (_internalFormat == TextureInternalFormat::Auto)
    {
      _internalFormat = TextureInternalFormat::RGBA;
      if (channels == 3)
      {
        _internalFormat = TextureInternalFormat::RGB;
      }
    }

    glTextureStorage2D(_id, 1, ToGLInternalFormat(_internalFormat), width, height);
    glTextureSubImage3D(_id, 0, 0, 0, 0, width, height, 1, ToGLDataFormat(_internalFormat), GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);

    for (uint i = 1; i < faces.size(); i++)
    {
      int fWidth, fHeight, fChannels;
      data = stbi_load(faces[i].c_str(), &fWidth, &fHeight, &fChannels, 0);
      KRYS_ASSERT(fWidth == width && fHeight == height && fChannels == channels,
                  "Face %d does not have matching dimensions or channels", i);

      glTextureSubImage3D(_id, 0, 0, 0, i, width, height, 1, ToGLDataFormat(_internalFormat), GL_UNSIGNED_BYTE, data);
      stbi_image_free(data);
    }

    glTextureParameteri(_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(_id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTextureParameteri(_id, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTextureParameteri(_id, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTextureParameteri(_id, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
  }

  GLTextureCubemap::GLTextureCubemap(uint width, uint height, TextureInternalFormat internalFormat)
  {
    KRYS_ASSERT(static_cast<int>(width) <= MaxTextureSize,
                "Texture width exceeds Max Texture Size (Max %d, %d received).", MaxTextureSize, width);
    KRYS_ASSERT(static_cast<int>(height) <= MaxTextureSize,
                "Texture height exceeds Max Texture Size (Max %d, %d received).", MaxTextureSize, height);

    _internalFormat = internalFormat;

    glCreateTextures(GL_TEXTURE_CUBE_MAP, 1, &_id);

    glTextureStorage2D(_id, 1, ToGLInternalFormat(_internalFormat), width, height);

    glTextureParameteri(_id, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTextureParameteri(_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTextureParameteri(_id, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTextureParameteri(_id, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTextureParameteri(_id, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
  }

  GLTextureCubemap::~GLTextureCubemap()
  {
    glDeleteTextures(1, &_id);
  }

  void GLTextureCubemap::Bind(uint32 slot) const noexcept
  {
    glBindTextureUnit(slot, _id);
  }

  void GLTextureCubemap::Unbind() const noexcept
  {
    glBindTextureUnit(0, _id);
  }

  void GLTextureCubemap::SetFilterModes(TextureMinifyMode min, TextureMagnifyMode mag) noexcept
  {
    glTextureParameteri(_id, GL_TEXTURE_MIN_FILTER, ToGLTextureMinifyMode(min));
    glTextureParameteri(_id, GL_TEXTURE_MAG_FILTER, ToGLTextureMagnifyMode(mag));
  }

  void GLTextureCubemap::SetMagnifyMode(TextureMagnifyMode mode) noexcept
  {
    glTextureParameteri(_id, GL_TEXTURE_MAG_FILTER, ToGLTextureMagnifyMode(mode));
  }

  void GLTextureCubemap::SetMinifyMode(TextureMinifyMode mode) noexcept
  {
    glTextureParameteri(_id, GL_TEXTURE_MIN_FILTER, ToGLTextureMinifyMode(mode));
  }

  void GLTextureCubemap::SetTextureWrapS(TextureWrapMode mode) noexcept
  {
    glTextureParameteri(_id, GL_TEXTURE_WRAP_S, ToGLTextureWrapMode(mode));
  }

  void GLTextureCubemap::SetTextureWrapT(TextureWrapMode mode) noexcept
  {
    glTextureParameteri(_id, GL_TEXTURE_WRAP_T, ToGLTextureWrapMode(mode));
  }

  void GLTextureCubemap::SetTextureWrapR(TextureWrapMode mode) noexcept
  {
    glTextureParameteri(_id, GL_TEXTURE_WRAP_R, ToGLTextureWrapMode(mode));
  }

  void GLTextureCubemap::SetTextureWrapModes(TextureWrapMode s, TextureWrapMode t, TextureWrapMode r) noexcept
  {
    glTextureParameteri(_id, GL_TEXTURE_WRAP_S, ToGLTextureWrapMode(s));
    glTextureParameteri(_id, GL_TEXTURE_WRAP_T, ToGLTextureWrapMode(t));
    glTextureParameteri(_id, GL_TEXTURE_WRAP_R, ToGLTextureWrapMode(r));
  }

  void GLTextureCubemap::SetBorderColor(const Maths::Vec4 &color) noexcept
  {
    float borderColor[4] = {color.r, color.g, color.b, color.a};
    glTextureParameterfv(_id, GL_TEXTURE_BORDER_COLOR, borderColor);
  }

  void GLTextureCubemap::Load()
  {
    // TODO: implement?
  }
}