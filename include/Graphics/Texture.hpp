#pragma once

#include "Base/Attributes.hpp"
#include "Graphics/Handles.hpp"
#include "Graphics/Sampler.hpp"

namespace Krys::Gfx
{
  enum class TextureUsageHint
  {
    Data,
    Image,
    RenderTarget,
    Depth
  };

  class Texture
  {
  public:
    Texture() noexcept = default;
    ~Texture() noexcept = default;

    NO_DISCARD TextureUsageHint GetUsageHint() const noexcept
    {
      return _usageHint;
    }

  private:
    TextureHandle _handle;
    TextureUsageHint _usageHint;
  };
}