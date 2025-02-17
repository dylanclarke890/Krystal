#pragma once

#include "Base/Attributes.hpp"
#include "Base/Macros.hpp"
#include "Base/Types.hpp"
#include "Graphics/Handles.hpp"
#include "Graphics/Sampler.hpp"
#include "Graphics/TextureDescriptor.hpp"
#include "Graphics/TextureType.hpp"

namespace Krys::Gfx
{

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

    /// @brief Gets the type of texture.
    NO_DISCARD TextureType GetType() const noexcept;

    /// @brief Gets the width of the texture.
    NO_DISCARD uint32 GetWidth() const noexcept;

    /// @brief Gets the height of the texture.
    NO_DISCARD uint32 GetHeight() const noexcept;

    /// @brief Gets the number of channels of the texture.
    NO_DISCARD uint32 GetChannels() const noexcept;

  protected:
    /// @brief Constructs a texture.
    /// @param handle The handle of the texture.
    /// @param descriptor The descriptor of the texture.
    Texture(TextureHandle handle, const TextureDescriptor &descriptor) noexcept;

    TextureHandle _handle;
    TextureDescriptor _descriptor;
  };
}