#include "GLTexture2D.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <glad/gl.h>

namespace Krys
{
  static auto ToGLTextureMagnifyMode = [](TextureMagnifyMode mode)
  {
    switch (mode)
    {
    case TextureMagnifyMode::Nearest:
      return GL_NEAREST;
    case TextureMagnifyMode::Linear:
      return GL_LINEAR;
    default:
    {
      KRYS_ASSERT(false, "Unknown TextureMagnifyMode", 0);
      return 0;
    }
    }
  };

  static auto ToGLTextureMinifyMode = [](TextureMinifyMode mode)
  {
    switch (mode)
    {
    case TextureMinifyMode::Nearest:
      return GL_NEAREST;
    case TextureMinifyMode::NearestMipmapNearest:
      return GL_NEAREST_MIPMAP_NEAREST;
    case TextureMinifyMode::NearestMipmapLinear:
      return GL_NEAREST_MIPMAP_LINEAR;
    case TextureMinifyMode::Linear:
      return GL_LINEAR;
    case TextureMinifyMode::LinearMipmapNearest:
      return GL_LINEAR_MIPMAP_NEAREST;
    case TextureMinifyMode::LinearMipmapLinear:
      return GL_LINEAR_MIPMAP_LINEAR;
    default:
    {
      KRYS_ASSERT(false, "Unknown TextureMinifyMode", 0);
      return 0;
    }
    }
  };

  static auto ToGLTextureWrapMode = [](TextureWrapMode mode)
  {
    switch (mode)
    {
    case TextureWrapMode::Repeat:
      return GL_REPEAT;
    case TextureWrapMode::MirroredRepeat:
      return GL_MIRRORED_REPEAT;
    case TextureWrapMode::ClampToEdge:
      return GL_CLAMP_TO_EDGE;
    case TextureWrapMode::MirroredClampToEdge:
      return GL_MIRROR_CLAMP_TO_EDGE;
    case TextureWrapMode::ClampToBorder:
      return GL_CLAMP_TO_BORDER;
    default:
    {
      KRYS_ASSERT(false, "Unknown TextureWrapMode", 0);
      return 0;
    }
    }
  };

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

  void GLTexture2D::Bind(uint32 slot) const noexcept
  {
    glBindTextureUnit(slot, Id);
  }

  void GLTexture2D::SetData(void *data, uint32 size) noexcept
  {
    KRYS_ASSERT(Width * Height * (DataFormat == GL_RGBA ? 4 : 3) == size, "Data must be entire texture!", 0);
    //                                             ^ bytes per pixel
    glTextureSubImage2D(Id, 0, 0, 0, Width, Height, DataFormat, GL_UNSIGNED_BYTE, data);
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