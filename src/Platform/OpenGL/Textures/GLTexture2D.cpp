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
    // TODO: is this a safe assumption?
    Type = TextureType::Diffuse;

    Load();
  }

  GLTexture2D::GLTexture2D(TextureType type, const string &path)
  {
    Type = type;
    Path = path;
    Width = 0;
    Height = 0;
    Samples = 1;

    Load();
  }

  GLTexture2D::GLTexture2D(int width, int height, int samples)
  {
    Type = TextureType::Diffuse;
    Path = "N/A";
    Width = width;
    Height = height;
    Samples = samples;

    if (IsMultisampled())
    {
      glCreateTextures(GL_TEXTURE_2D_MULTISAMPLE, 1, &Id);
      glTextureStorage2DMultisample(Id, samples, GL_RGBA8, width, height, GL_TRUE);
    }
    else
    {
      glCreateTextures(GL_TEXTURE_2D, 1, &Id);
      glTextureStorage2D(Id, 1, GL_RGBA8, Width, Height);

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

    Width = width;
    Height = height;

    auto internalFormat = GL_RGBA8;
    auto dataFormat = GL_RGBA;
    if (channels == 3)
    {
      internalFormat = GL_RGB8;
      dataFormat = GL_RGB;
    }

    if (IsMultisampled())
    {
      glCreateTextures(GL_TEXTURE_2D_MULTISAMPLE, 1, &Id);
      glTextureStorage2DMultisample(Id, Samples, internalFormat, width, height, GL_TRUE);
    }
    else
    {
      glCreateTextures(GL_TEXTURE_2D, 1, &Id);
      glTextureStorage2D(Id, 1, GL_RGB8, Width, Height);

      glTextureParameteri(Id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTextureParameteri(Id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

      glTextureParameteri(Id, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTextureParameteri(Id, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

    glTextureSubImage2D(Id, 0, 0, 0, Width, Height, dataFormat, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);
  }
}