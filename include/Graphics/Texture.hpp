#pragma once

#include "Base/Attributes.hpp"
#include "Base/Types.hpp"
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

  /// @brief Represents a GPU texture.
  class Texture
  {
  public:
    virtual ~Texture() noexcept = default;

    /// @brief Gets the name of the texture.
    NO_DISCARD const string &GetName() const noexcept;

    /// @brief Gets the handle of the texture.
    NO_DISCARD const TextureHandle &GetHandle() const noexcept;

    /// @brief Gets the handle of the sampler.
    NO_DISCARD const SamplerHandle &GetSampler() const noexcept;

    /// @brief Gets the usage hint of the texture.
    NO_DISCARD TextureUsageHint GetUsageHint() const noexcept;

    /// @brief Gets the width of the texture.
    NO_DISCARD uint32 GetWidth() const noexcept;

    /// @brief Gets the height of the texture.
    NO_DISCARD uint32 GetHeight() const noexcept;

    /// @brief Gets the number of channels of the texture.
    NO_DISCARD uint32 GetChannels() const noexcept;

  protected:
    /// @brief Constructs a texture.
    /// @param resourceName The name of the resource.
    /// @param handle The handle of the texture.
    /// @param hint The usage hint of the texture.
    Texture(const string &name, TextureHandle handle, SamplerHandle sampler, TextureUsageHint hint) noexcept;

    string _resourceName;
    TextureHandle _handle;
    SamplerHandle _sampler;
    TextureUsageHint _usageHint;
    uint32 _width {0}, _height {0}, _channels {0};
  };
}