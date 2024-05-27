#include "GLTexture2D.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <glad/gl.h>

namespace Krys
{
  GLTexture2D::GLTexture2D(const char *path)
      : InternalFormat(0), DataFormat(0)
  {
    Path = path;
    Width = 0;
    Height = 0;
    // TODO: is this a safe assumption?
    Type = TextureType::Diffuse;

    Load();
  }

  GLTexture2D::GLTexture2D(TextureType type, const char *path)
      : InternalFormat(0), DataFormat(0)
  {
    Type = type;
    Path = path;
    Width = 0;
    Height = 0;

    Load();
  }

  GLTexture2D::~GLTexture2D()
  {
    glDeleteTextures(1, &Id);
  }

  void GLTexture2D::Bind(uint32 slot) const
  {
    glBindTextureUnit(slot, Id);
  }

  void GLTexture2D::SetData(void *data, uint32 size)
  {
    KRYS_ASSERT(Width * Height * (DataFormat == GL_RGBA ? 4 : 3) == size, "Data must be entire texture!", 0);
    //                                             ^ bytes per pixel
    glTextureSubImage2D(Id, 0, 0, 0, Width, Height, DataFormat, GL_UNSIGNED_BYTE, data);
  }

  void GLTexture2D::GenerateMipmaps()
  {
    glGenerateTextureMipmap(Id);
    // TODO: make this configurable
    glTextureParameteri(Id, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  }

  void GLTexture2D::Load()
  {
    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    stbi_uc *data = stbi_load(Path, &width, &height, &channels, 0);

    KRYS_ASSERT(data, "Failed to load image!", 0);

    Width = width;
    Height = height;

    if (channels == 4)
    {
      InternalFormat = GL_RGBA8;
      DataFormat = GL_RGBA;
    }
    else if (channels == 3)
    {
      InternalFormat = GL_RGB8;
      DataFormat = GL_RGB;
    }

    KRYS_ASSERT(InternalFormat, "UnsupportedFormat: Internal format.", 0);
    KRYS_ASSERT(DataFormat, "UnsupportedFormat: Data format.", 0);

    glCreateTextures(GL_TEXTURE_2D, 1, &Id);
    glTextureStorage2D(Id, 1, InternalFormat, Width, Height);

    glTextureParameteri(Id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(Id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTextureParameteri(Id, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(Id, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTextureSubImage2D(Id, 0, 0, 0, Width, Height, DataFormat, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);
  }

  GLenum GLTexture2D::ToGLDataFormat(Texture2DFormat format)
  {
    switch (format)
    {
    case Texture2DFormat::RGB8:
      return GL_RGB;
    case Texture2DFormat::RGBA8:
      return GL_RGBA;
    default:
      KRYS_ASSERT(false, "Unknown data format", 0);
      return 0;
    }
  }

  GLenum GLTexture2D::ToGLInternalDataFormat(Texture2DFormat format)
  {
    switch (format)
    {
    case Texture2DFormat::RGB8:
      return GL_RGB8;
    case Texture2DFormat::RGBA8:
      return GL_RGBA8;
    default:
      KRYS_ASSERT(false, "Unknown data format", 0);
      return 0;
    }
  }
}