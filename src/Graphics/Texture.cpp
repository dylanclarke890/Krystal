#include "Graphics/Texture.hpp"

namespace Krys::Gfx
{
  Texture::Texture(TextureHandle handle, const TextureDescriptor& descriptor) noexcept
      : _descriptor(descriptor), _handle(handle)
  {
  }

  const string &Texture::GetName() const noexcept
  {
    return _descriptor.Name;
  }

  const TextureHandle &Texture::GetHandle() const noexcept
  {
    return _handle;
  }

  const SamplerHandle &Texture::GetSampler() const noexcept
  {
    return _descriptor.Sampler;
  }

  TextureType Texture::GetType() const noexcept
  {
    return _descriptor.Type;
  }

  uint32 Texture::GetWidth() const noexcept
  {
    return _descriptor.Width;
  }

  uint32 Texture::GetHeight() const noexcept
  {
    return _descriptor.Height;
  }

  uint32 Texture::GetChannels() const noexcept
  {
    return _descriptor.Channels;
  }
}