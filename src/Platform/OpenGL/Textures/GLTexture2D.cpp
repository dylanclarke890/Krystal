#include "OpenGL/Textures/GLTexture2D.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace Krys::OpenGL
{
  GLTexture2D::GLTexture2D(const string &path)
  {
    _path = path;
    _width = 0;
    _height = 0;
    _samples = 1;
    _type = TextureType::Diffuse;
    _internalFormat = TextureInternalFormat::Auto;

    Load();
  }

  GLTexture2D::GLTexture2D(const string &path, TextureType type, TextureInternalFormat internalFormat)
  {
    _path = path;
    _width = 0;
    _height = 0;
    _samples = 1;
    _type = type;
    _internalFormat = internalFormat;

    Load();
  }

  GLTexture2D::GLTexture2D(int width, int height, int samples, TextureInternalFormat internalFormat)
  {
    KRYS_ASSERT(width <= MaxTextureSize, "Texture width exceeds Max Texture Size (Max %d, %d received).",
                MaxTextureSize, width);
    KRYS_ASSERT(height <= MaxTextureSize, "Texture height exceeds Max Texture Size (Max %d, %d received).",
                MaxTextureSize, height);
    KRYS_ASSERT(internalFormat != TextureInternalFormat::Depth || samples <= MaxDepthSamples,
                "Unable to create a depth texture with %d samples (max is %d)", samples, MaxDepthSamples);
    KRYS_ASSERT(internalFormat == TextureInternalFormat::Depth || samples <= MaxColorSamples,
                "Unable to create a color texture with %d samples (max is %d)", samples, MaxColorSamples);

    _path = "N/A";
    _width = width;
    _height = height;
    _samples = samples;
    _type = TextureType::Diffuse;

    _internalFormat = internalFormat;
    KRYS_ASSERT(_internalFormat != TextureInternalFormat::None && _internalFormat != TextureInternalFormat::Auto,
                "TextureInternal format cannot be deduced.", 0);

    if (IsMultisampled())
    {
      glCreateTextures(GL_TEXTURE_2D_MULTISAMPLE, 1, &_id);
      glTextureStorage2DMultisample(_id, samples, ToGLInternalFormat(_internalFormat), _width, _height, GL_TRUE);
    }
    else
    {
      glCreateTextures(GL_TEXTURE_2D, 1, &_id);
      glTextureStorage2D(_id, 1, ToGLInternalFormat(_internalFormat), _width, _height);

      glTextureParameteri(_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTextureParameteri(_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }
  }

  GLTexture2D::~GLTexture2D()
  {
    glDeleteTextures(1, &_id);
  }

  void GLTexture2D::Bind(uint32 slot) const noexcept
  {
    glBindTextureUnit(slot, _id);
  }

  void GLTexture2D::Unbind() const noexcept
  {
    glBindTextureUnit(0, _id);
  }

  void GLTexture2D::SetFilterModes(TextureMinifyMode min, TextureMagnifyMode mag) noexcept
  {
    glTextureParameteri(_id, GL_TEXTURE_MIN_FILTER, ToGLTextureMinifyMode(min));
    glTextureParameteri(_id, GL_TEXTURE_MAG_FILTER, ToGLTextureMagnifyMode(mag));
  }

  void GLTexture2D::SetMagnifyMode(TextureMagnifyMode mode) noexcept
  {
    glTextureParameteri(_id, GL_TEXTURE_MAG_FILTER, ToGLTextureMagnifyMode(mode));
  }

  void GLTexture2D::SetMinifyMode(TextureMinifyMode mode) noexcept
  {
    glTextureParameteri(_id, GL_TEXTURE_MIN_FILTER, ToGLTextureMinifyMode(mode));
  }

  void GLTexture2D::SetTextureWrapS(TextureWrapMode mode) noexcept
  {
    glTextureParameteri(_id, GL_TEXTURE_WRAP_S, ToGLTextureWrapMode(mode));
  }

  void GLTexture2D::SetTextureWrapT(TextureWrapMode mode) noexcept
  {
    glTextureParameteri(_id, GL_TEXTURE_WRAP_T, ToGLTextureWrapMode(mode));
  }

  void GLTexture2D::SetTextureWrapModes(TextureWrapMode s, TextureWrapMode t) noexcept
  {
    glTextureParameteri(_id, GL_TEXTURE_WRAP_S, ToGLTextureWrapMode(s));
    glTextureParameteri(_id, GL_TEXTURE_WRAP_T, ToGLTextureWrapMode(t));
  }

  void GLTexture2D::SetBorderColor(const Vec4 &color) noexcept
  {
    float borderColor[4] = {color.r, color.g, color.b, color.a};
    glTextureParameterfv(_id, GL_TEXTURE_BORDER_COLOR, borderColor);
  }

  void GLTexture2D::GenerateMipmaps(TextureMinifyMode mode) noexcept
  {
    glGenerateTextureMipmap(_id);
    glTextureParameteri(_id, GL_TEXTURE_MIN_FILTER, ToGLTextureMinifyMode(mode));
  }

  void GLTexture2D::Load()
  {
    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    stbi_uc *data = stbi_load(_path.c_str(), &width, &height, &channels, 0);

    KRYS_ASSERT(data, "Failed to load image!", 0);
    KRYS_ASSERT(channels == 3 || channels == 4, "Unsupported number of color channels.", 0);
    KRYS_ASSERT(width <= MaxTextureSize, "Texture width exceeds Max Texture Size (Max %d, %d received).",
                MaxTextureSize, width);
    KRYS_ASSERT(height <= MaxTextureSize, "Texture height exceeds Max Texture Size (Max %d, %d received).",
                MaxTextureSize, height);

    _width = width;
    _height = height;

    if (_internalFormat == TextureInternalFormat::Auto)
    {
      _internalFormat = TextureInternalFormat::RGBA;
      if (channels == 3)
      {
        _internalFormat = TextureInternalFormat::RGB;
      }
    }

    if (IsMultisampled())
    {
      KRYS_ASSERT(_internalFormat != TextureInternalFormat::Depth || static_cast<int>(_samples) <= MaxDepthSamples,
                  "Unable to create a depth texture with %d samples (max is %d)", _samples, MaxDepthSamples);
      KRYS_ASSERT(_internalFormat == TextureInternalFormat::Depth || static_cast<int>(_samples) <= MaxColorSamples,
                  "Unable to create a color texture with %d samples (max is %d)", _samples, MaxColorSamples);
      glCreateTextures(GL_TEXTURE_2D_MULTISAMPLE, 1, &_id);
      glTextureStorage2DMultisample(_id, _samples, ToGLInternalFormat(_internalFormat), _width, _height, GL_TRUE);
    }
    else
    {
      glCreateTextures(GL_TEXTURE_2D, 1, &_id);
      glTextureStorage2D(_id, 1, ToGLInternalFormat(_internalFormat), _width, _height);

      glTextureParameteri(_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTextureParameteri(_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

      glTextureParameteri(_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTextureParameteri(_id, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

    glTextureSubImage2D(_id, 0, 0, 0, _width, _height, ToGLDataFormat(_internalFormat), GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);
  }
}