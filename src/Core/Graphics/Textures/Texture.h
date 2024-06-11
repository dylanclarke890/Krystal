#pragma once

#include "Core.h"

namespace Krys
{
  enum class TextureMagnifyMode : ushort
  {
    None = 0,
    Nearest,
    Linear
  };

  enum class TextureMinifyMode : ushort
  {
    None = 0,
    Nearest,
    NearestMipmapNearest,
    NearestMipmapLinear,
    Linear,
    LinearMipmapNearest,
    LinearMipmapLinear,
  };

  enum class TextureWrapMode : ushort
  {
    None = 0,
    Repeat,
    MirroredRepeat,
    ClampToEdge,
    MirroredClampToEdge,
    ClampToBorder
  };

  enum class TextureType
  {
    None = 0,
    Diffuse,
    Specular,
    Emission
  };

  enum class TextureInternalFormat
  {
    None = 0,
    Auto,
    RGB,
    RGBA,
    SRGB,
    SRGBA
  };
}