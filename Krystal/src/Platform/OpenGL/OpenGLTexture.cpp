#include "krys-pch.h"
#include "Platform/OpenGL/OpenGLTexture.h"

#include <stb_image.h>
#include <glad/glad.h>

namespace Krys
{
  OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
    : m_RendererId(0), m_Path(""), m_Width(width), m_Height(height), m_InternalFormat(GL_RGBA8), m_DataFormat(GL_RGBA)
  {
    KRYS_PROFILE_FUNCTION();

    glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererId);
    glTextureStorage2D(m_RendererId, 1, m_InternalFormat, m_Width, m_Height);

    glTextureParameteri(m_RendererId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(m_RendererId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTextureParameteri(m_RendererId, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(m_RendererId, GL_TEXTURE_WRAP_T, GL_REPEAT);
  }

  OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
    : m_RendererId(0), m_Path(path), m_Width(0), m_Height(0), m_InternalFormat(0), m_DataFormat(0)
  {
    KRYS_PROFILE_FUNCTION();
    
    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    stbi_uc* data = nullptr;
    {
      KRYS_PROFILE_SCOPE("stbi_load - OpenGLTexture2D::OpenGLTexture2D(const std::string&)");
      data = stbi_load(path.c_str(), &width, &height, &channels, 0);
    }
    
    KRYS_CORE_ASSERT(data, "Failed to load image!");

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

    KRYS_CORE_ASSERT(m_InternalFormat, "UnsupportedFormat: Internal format.");
    KRYS_CORE_ASSERT(m_DataFormat, "UnsupportedFormat: Data format.");

    glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererId);
    glTextureStorage2D(m_RendererId, 1, m_InternalFormat, m_Width, m_Height);

    glTextureParameteri(m_RendererId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(m_RendererId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTextureParameteri(m_RendererId, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(m_RendererId, GL_TEXTURE_WRAP_T, GL_REPEAT);
 
    glTextureSubImage2D(m_RendererId, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
  
    stbi_image_free(data);
  }

  OpenGLTexture2D::~OpenGLTexture2D()
  {
    KRYS_PROFILE_FUNCTION();

    glDeleteTextures(1, &m_RendererId);
  }

  void OpenGLTexture2D::Bind(uint32_t slot) const
  {
    KRYS_PROFILE_FUNCTION();

    glBindTextureUnit(slot, m_RendererId);
  }

  void OpenGLTexture2D::SetData(void* data, uint32_t size)
  {
    KRYS_PROFILE_FUNCTION();

    KRYS_CORE_ASSERT(m_Width * m_Height * (m_DataFormat == GL_RGBA ? 4 : 3) == size, "Data must be entire texture!");
    //                                             ^ bytes per pixel

    glTextureSubImage2D(m_RendererId, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
  }
}