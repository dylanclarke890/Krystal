#pragma once

#include "Base/Attributes.hpp"
#include "Base/Macros.hpp"
#include "Base/Types.hpp"
#include "Graphics/Handles.hpp"
#include "Graphics/Sampler.hpp"

namespace Krys::Gfx
{
  enum class TextureType : uint32
  {
    /// @brief A texture that stores arbitrary data.
    /// @note This type is suitable for storing data that isn't directly sampled, such as lookup tables,
    /// noise textures, or other data that you manipulate in your shaders.
    Data,

    /// @brief A standard image texture that’s typically loaded from a file. This type is meant for textures
    /// that you sample in your shaders, like diffuse, albedo, or normal maps.
    Image,

    /// @brief A render target that stores colour data.
    /// @note This type is used for off-screen rendering, post-processing, and other advanced rendering
    /// techniques. It is not meant for textures that you sample in your shaders.
    RenderTargetColour,

    /// @brief A render target that stores depth data.
    /// @note This type is used for off-screen rendering, post-processing, and other advanced rendering
    /// techniques. It is not meant for textures that you sample in your shaders.
    RenderTargetDepth,

    /// @brief A render target that stores stencil data.
    /// @note This type is used for off-screen rendering, post-processing, and other advanced rendering
    /// techniques. It is not meant for textures that you sample in your shaders.
    RenderTargetStencil,

    /// @brief A render target that stores both depth and stencil data.
    /// @note This type is used for off-screen rendering, post-processing, and other advanced rendering
    /// techniques. It is not meant for textures that you sample in your shaders.
    RenderTargetDepthStencil
  };

  struct TextureDescriptor
  {
    string Name;
    TextureType Type {TextureType::Image};
    uint32 Width {0}, Height {0}, Channels {0};
    SamplerHandle Sampler;
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