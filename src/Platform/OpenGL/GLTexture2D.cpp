#include "GLTexture2D.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <gl.h>

namespace Krys
{
  GLTexture2D::GLTexture2D(Texture2DSettings settings)
      : m_RendererId(0), m_Path(nullptr),
        m_Width(settings.Width), m_Height(settings.Height),
        m_InternalFormat(0), m_DataFormat(0)
  {
    m_DataFormat = ToGLDataFormat(settings.Format);
    m_InternalFormat = ToGLInternalDataFormat(settings.Format);

    glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererId);
    glTextureStorage2D(m_RendererId, 1, m_InternalFormat, m_Width, m_Height);

    // TODO: make these configurable
    glTextureParameteri(m_RendererId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(m_RendererId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // TODO: make these configurable
    glTextureParameteri(m_RendererId, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(m_RendererId, GL_TEXTURE_WRAP_T, GL_REPEAT);

    if (settings.GenerateMipMaps)
      GenerateMipmaps();
  }

  GLTexture2D::GLTexture2D(const char *path)
      : m_RendererId(0), m_Path(path),
        m_Width(0), m_Height(0),
        m_InternalFormat(0), m_DataFormat(0)
  {
    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    stbi_uc *data = stbi_load(path, &width, &height, &channels, 0);

    KRYS_ASSERT(data, "Failed to load image!");

    m_Width = width;
    m_Height = height;

    if (channels == 4)
    {
      m_InternalFormat = GL_RGBA8;
      m_DataFormat = GL_RGBA;
    }
    else if (channels == 3)
    {
      m_InternalFormat = GL_RGB8;
      m_DataFormat = GL_RGB;
    }

    KRYS_ASSERT(m_InternalFormat, "UnsupportedFormat: Internal format.");
    KRYS_ASSERT(m_DataFormat, "UnsupportedFormat: Data format.");

    glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererId);
    glTextureStorage2D(m_RendererId, 1, m_InternalFormat, m_Width, m_Height);

    glTextureParameteri(m_RendererId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(m_RendererId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTextureParameteri(m_RendererId, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(m_RendererId, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTextureSubImage2D(m_RendererId, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);
  }

  GLTexture2D::~GLTexture2D()
  {
    glDeleteTextures(1, &m_RendererId);
  }

  void GLTexture2D::Bind(uint32 slot) const
  {
    glBindTextureUnit(slot, m_RendererId);
  }

  void GLTexture2D::SetData(void *data, uint32 size)
  {
    KRYS_ASSERT(m_Width * m_Height * (m_DataFormat == GL_RGBA ? 4 : 3) == size, "Data must be entire texture!");
    //                                             ^ bytes per pixel
    glTextureSubImage2D(m_RendererId, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
  }

  void GLTexture2D::GenerateMipmaps()
  {
    glGenerateTextureMipmap(m_RendererId);
    // TODO: make this configurable
    glTextureParameteri(m_RendererId, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
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
      KRYS_ASSERT(false, "Unknown data format");
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
      KRYS_ASSERT(false, "Unknown data format");
      return 0;
    }
  }
}