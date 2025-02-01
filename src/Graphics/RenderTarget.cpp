#include "Graphics/RenderTarget.hpp"

namespace Krys::Gfx
{
  RenderTarget::RenderTarget(RenderTargetHandle handle, TextureHandle texture,
                             const RenderTargetDescriptor &descriptor) noexcept
      : _handle(handle), _texture(texture), _descriptor(descriptor)
  {
  }

  RenderTargetHandle RenderTarget::GetHandle() const noexcept
  {
    return _handle;
  }

  TextureHandle RenderTarget::GetTexture() const noexcept
  {
    return _texture;
  }

  RenderTargetType RenderTarget::GetType() const noexcept
  {
    return _descriptor.Type;
  }
}