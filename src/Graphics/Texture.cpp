#include "Graphics/Texture.hpp"

namespace Krys::Gfx
{
  Texture::Texture(const string &name, TextureHandle handle, SamplerHandle sampler,
                   TextureUsageHint usageHint) noexcept
      : _resourceName(name), _handle(handle), _sampler(sampler), _usageHint(usageHint)
  {
  }

  const string &Texture::GetName() const noexcept
  {
    return _resourceName;
  }

  const TextureHandle &Texture::GetHandle() const noexcept
  {
    return _handle;
  }

  const SamplerHandle &Texture::GetSampler() const noexcept
  {
    return _sampler;
  }

  TextureUsageHint Texture::GetUsageHint() const noexcept
  {
    return _usageHint;
  }

  uint32 Texture::GetWidth() const noexcept
  {
    return _width;
  }

  uint32 Texture::GetHeight() const noexcept
  {
    return _height;
  }

  uint32 Texture::GetChannels() const noexcept
  {
    return _channels;
  }
}