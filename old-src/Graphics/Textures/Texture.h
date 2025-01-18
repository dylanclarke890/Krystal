#pragma once

#include "Types.h"

namespace Krys::Gfx
{
  class Texture
  {
  protected:
    uint _id;
    inline static int MaxTextureSize = 0;
    inline static int MaxColorSamples = 0;
    inline static int MaxDepthSamples = 0;

  public:
    Texture() = default;
    virtual ~Texture() = default;

    NO_DISCARD uint GetId() const noexcept
    {
      return _id;
    }

    virtual void Bind(uint32 slot = 0) const noexcept = 0;
    virtual void Unbind() const noexcept = 0;

    static void SetDriverLimits(int maxTextureSize, int maxColorSamples, int maxDepthSamples) noexcept
    {
      MaxTextureSize = maxTextureSize;
      MaxColorSamples = maxColorSamples;
      MaxDepthSamples = maxDepthSamples;
    }
  };

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
    RGBA16F,
    SRGB,
    SRGBA,
    Depth
  };
}