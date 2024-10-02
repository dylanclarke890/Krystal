#include "GLTexture2D.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace Krys
{
  GLTexture2D::GLTexture2D(const string &path)
  {
    Path = path;
    Width = 0;
    Height = 0;
    Samples = 1;
    Type = TextureType::Diffuse;
    InternalFormat = TextureInternalFormat::Auto;

    Load();
  }

  GLTexture2D::GLTexture2D(const string &path, TextureType type, TextureInternalFormat internalFormat)
  {
    Path = path;
    Width = 0;
    Height = 0;
    Samples = 1;
    Type = type;
    InternalFormat = internalFormat;

    Load();
  }

  GLTexture2D::GLTexture2D(int width, int height, int samples, TextureInternalFormat internalFormat)
  {
    KRYS_ASSERT(width <= MaxTextureSize, "Texture width exceeds Max Texture Size (Max %d, %d received).", MaxTextureSize, width);
    KRYS_ASSERT(height <= MaxTextureSize, "Texture height exceeds Max Texture Size (Max %d, %d received).", MaxTextureSize, height);
    KRYS_ASSERT(internalFormat != TextureInternalFormat::Depth || samples <= MaxDepthSamples, "Unable to create a depth texture with %d samples (max is %d)", samples, MaxDepthSamples);
    KRYS_ASSERT(internalFormat == TextureInternalFormat::Depth || samples <= MaxColorSamples, "Unable to create a color texture with %d samples (max is %d)", samples, MaxColorSamples);

    Path = "N/A";
    Width = width;
    Height = height;
    Samples = samples;
    Type = TextureType::Diffuse;

    InternalFormat = internalFormat;
    KRYS_ASSERT(InternalFormat != TextureInternalFormat::None && InternalFormat != TextureInternalFormat::Auto, "TextureInternal format cannot be deduced.", 0);

    if (IsMultisampled())
    {
      glCreateTextures(GL_TEXTURE_2D_MULTISAMPLE, 1, &Id);
      glTextureStorage2DMultisample(Id, samples, ToGLInternalFormat(InternalFormat), width, height, GL_TRUE);
    }
    else
    {
      glCreateTextures(GL_TEXTURE_2D, 1, &Id);
      glTextureStorage2D(Id, 1, ToGLInternalFormat(InternalFormat), Width, Height);

      glTextureParameteri(Id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTextureParameteri(Id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }
  }

  GLTexture2D::~GLTexture2D()
  {
    glDeleteTextures(1, &Id);
  }

  void GLTexture2D::Bind(uint32 slot) const noexcept
  {
    glBindTextureUnit(slot, Id);
  }

  void GLTexture2D::Unbind() const noexcept
  {
    glBindTextureUnit(0, Id);
  }

  void GLTexture2D::SetFilterModes(TextureMinifyMode min, TextureMagnifyMode mag) noexcept
  {
    glTextureParameteri(Id, GL_TEXTURE_MIN_FILTER, ToGLTextureMinifyMode(min));
    glTextureParameteri(Id, GL_TEXTURE_MAG_FILTER, ToGLTextureMagnifyMode(mag));
  }

  void GLTexture2D::SetMagnifyMode(TextureMagnifyMode mode) noexcept
  {
    glTextureParameteri(Id, GL_TEXTURE_MAG_FILTER, ToGLTextureMagnifyMode(mode));
  }

  void GLTexture2D::SetMinifyMode(TextureMinifyMode mode) noexcept
  {
    glTextureParameteri(Id, GL_TEXTURE_MIN_FILTER, ToGLTextureMinifyMode(mode));
  }

  void GLTexture2D::SetTextureWrapS(TextureWrapMode mode) noexcept
  {
    glTextureParameteri(Id, GL_TEXTURE_WRAP_S, ToGLTextureWrapMode(mode));
  }

  void GLTexture2D::SetTextureWrapT(TextureWrapMode mode) noexcept
  {
    glTextureParameteri(Id, GL_TEXTURE_WRAP_T, ToGLTextureWrapMode(mode));
  }

  void GLTexture2D::SetTextureWrapModes(TextureWrapMode s, TextureWrapMode t) noexcept
  {
    glTextureParameteri(Id, GL_TEXTURE_WRAP_S, ToGLTextureWrapMode(s));
    glTextureParameteri(Id, GL_TEXTURE_WRAP_T, ToGLTextureWrapMode(t));
  }

  void GLTexture2D::SetBorderColor(const Vec4 &color) noexcept
  {
    float borderColor[4] = {color.r, color.g, color.b, color.a};
    glTextureParameterfv(Id, GL_TEXTURE_BORDER_COLOR, borderColor);
  }

  void GLTexture2D::GenerateMipmaps(TextureMinifyMode mode) noexcept
  {
    glGenerateTextureMipmap(Id);
    glTextureParameteri(Id, GL_TEXTURE_MIN_FILTER, ToGLTextureMinifyMode(mode));
  }

  void GLTexture2D::Load()
  {
    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    stbi_uc *data = stbi_load(Path.c_str(), &width, &height, &channels, 0);

    KRYS_ASSERT(data, "Failed to load image!", 0);
    KRYS_ASSERT(channels == 3 || channels == 4, "Unsupported number of color channels.", 0);
    KRYS_ASSERT(width <= MaxTextureSize, "Texture width exceeds Max Texture Size (Max %d, %d received).", MaxTextureSize, width);
    KRYS_ASSERT(height <= MaxTextureSize, "Texture height exceeds Max Texture Size (Max %d, %d received).", MaxTextureSize, height);

    Width = width;
    Height = height;

    if (InternalFormat == TextureInternalFormat::Auto)
    {
      InternalFormat = TextureInternalFormat::RGBA;
      if (channels == 3)
      {
        InternalFormat = TextureInternalFormat::RGB;
      }
    }

    if (IsMultisampled())
    {
      KRYS_ASSERT(InternalFormat != TextureInternalFormat::Depth || static_cast<int>(Samples) <= MaxDepthSamples, "Unable to create a depth texture with %d samples (max is %d)", Samples, MaxDepthSamples);
      KRYS_ASSERT(InternalFormat == TextureInternalFormat::Depth || static_cast<int>(Samples) <= MaxColorSamples, "Unable to create a color texture with %d samples (max is %d)", Samples, MaxColorSamples);
      glCreateTextures(GL_TEXTURE_2D_MULTISAMPLE, 1, &Id);
      glTextureStorage2DMultisample(Id, Samples, ToGLInternalFormat(InternalFormat), width, height, GL_TRUE);
    }
    else
    {
      glCreateTextures(GL_TEXTURE_2D, 1, &Id);
      glTextureStorage2D(Id, 1, ToGLInternalFormat(InternalFormat), Width, Height);

      glTextureParameteri(Id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTextureParameteri(Id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

      glTextureParameteri(Id, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTextureParameteri(Id, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

    glTextureSubImage2D(Id, 0, 0, 0, Width, Height, ToGLDataFormat(InternalFormat), GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);
  }
}