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
}