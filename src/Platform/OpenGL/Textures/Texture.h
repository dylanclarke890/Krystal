#pragma once

#include "Graphics/Textures/Texture.h"
#include "../GL.h"

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

  static auto ToGLDataFormat = [](TextureInternalFormat internalFormat)
  {
    switch (internalFormat)
    {
    case TextureInternalFormat::RGB:
    case TextureInternalFormat::SRGB:
      return GL_RGB;
    case TextureInternalFormat::RGBA:
    case TextureInternalFormat::SRGBA:
      return GL_RGBA;
    case TextureInternalFormat::Depth:
      return GL_DEPTH_COMPONENT;
    case TextureInternalFormat::Auto:
    default:
    {
      KRYS_ASSERT(false, "Unsupported TextureInternalFormat", 0);
      return 0;
    }
    }
  };

  static auto ToGLInternalFormat = [](TextureInternalFormat internalFormat)
  {
    switch (internalFormat)
    {
    case TextureInternalFormat::RGB:
      return GL_RGB8;
    case TextureInternalFormat::SRGB:
      return GL_SRGB8;
    case TextureInternalFormat::RGBA:
      return GL_RGBA8;
    case TextureInternalFormat::RGBA16F:
      return GL_RGBA16F;
    case TextureInternalFormat::SRGBA:
      return GL_SRGB8_ALPHA8;
    case TextureInternalFormat::Depth:
      return GL_DEPTH_COMPONENT24;
    case TextureInternalFormat::Auto:
    default:
    {
      KRYS_ASSERT(false, "Unsupported TextureInternalFormat", 0);
      return 0;
    }
    }
  };
}