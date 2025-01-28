#pragma once

#include "Base/Attributes.hpp"
#include "Base/Pointers.hpp"
#include "Base/Types.hpp"
#include "Graphics/Handles.hpp"
#include "Graphics/Sampler.hpp"
#include "Graphics/Texture.hpp"
#include "IO/Images.hpp"

namespace Krys::Gfx
{
  // TODO: add cubemaps
  /// @brief Manages textures and samplers.
  class TextureManager
  {
  public:
    virtual ~TextureManager() noexcept = default;

    /// @brief Gets the default texture sampler.
    NO_DISCARD SamplerHandle DefaultTextureSampler() noexcept;

    /// @brief Creates a sampler.
    /// @param descriptor The descriptor of the sampler.
    NO_DISCARD SamplerHandle CreateSampler(const SamplerDescriptor &descriptor) noexcept;

    /// @brief Creates a texture with the default sampler.
    /// @param image Image settings to create the texture.
    /// @param hint Texture usage hint.
    NO_DISCARD TextureHandle CreateTexture(const IO::Image &image,
                                           TextureUsageHint hint = TextureUsageHint::Image) noexcept;

    /// @brief Creates a texture with a custom sampler.
    /// @param image Image settings to create the texture.
    /// @param sampler Sampler to use with the texture.
    /// @param hint Texture usage hint.
    NO_DISCARD TextureHandle CreateTexture(const IO::Image &image, SamplerHandle sampler,
                                           TextureUsageHint hint = TextureUsageHint::Image) noexcept;

    /// @brief Gets a sampler by its handle.
    /// @param handle The handle of the sampler.
    /// @return The sampler or nullptr if the handle is invalid.
    NO_DISCARD Sampler *GetSampler(SamplerHandle handle) const noexcept;

    /// @brief Gets a texture by its handle.
    /// @param handle The handle of the texture.
    /// @return The texture or nullptr if the handle is invalid.
    NO_DISCARD Texture *GetTexture(TextureHandle handle) const noexcept;

    /// @brief Loads a texture from a file. The loaded texture will use the default sampler.
    /// @param path The path to the file.
    /// @param hint Texture usage hint.
    NO_DISCARD TextureHandle LoadTexture(const string &path,
                                         TextureUsageHint hint = TextureUsageHint::Image) noexcept;

    /// @brief Loads a texture from a file with a custom sampler.
    /// @param path The path to the file.
    /// @param sampler Sampler to use with the texture.
    NO_DISCARD TextureHandle LoadTexture(const string &path, SamplerHandle sampler,
                                         TextureUsageHint hint = TextureUsageHint::Image) noexcept;

    /// @brief Unloads a sampler.
    /// @param handle The handle of the sampler.
    /// @return True if the sampler was found, false otherwise.
    /// @note Will only fully unload the sampler if its' reference count is 0.
    bool Unload(SamplerHandle handle) noexcept;

    /// @brief Unloads a texture.
    /// @param handle The handle of the texture.
    /// @return True if the texture was found, false otherwise.
    /// @note Will only fully unload the texture if its' reference count is 0.
    bool Unload(TextureHandle handle) noexcept;

  protected:
    TextureManager() noexcept = default;

    /// @brief Optional hook for implementation. Called when a sampler is destroyed.
    virtual void OnDestroy(SamplerHandle handle) noexcept;

    /// @brief Optional hook for implementation. Called when a texture is destroyed.
    virtual void OnDestroy(TextureHandle handle) noexcept;

    /// @brief Implementation-specific creation of a sampler.
    /// @param handle The handle of the sampler.
    /// @param descriptor The descriptor of the sampler.
    NO_DISCARD virtual Unique<Sampler> CreateSamplerImpl(SamplerHandle handle,
                                                         const SamplerDescriptor &descriptor) noexcept = 0;

    /// @brief Implementation-specific creation of a texture.
    /// @param resourceName The name of the resource.
    /// @param handle The handle of the texture.
    NO_DISCARD virtual Unique<Texture>
      CreateTextureImpl(const string &resourceName, TextureHandle handle, SamplerHandle sampler,
                        const IO::Image &data, TextureUsageHint hint = TextureUsageHint::Image) noexcept = 0;

  protected:
    template <class T>
    struct LoadedResource
    {
      size_t ReferenceCount;
      Unique<T> Resource;
    };

    Map<SamplerDescriptor, LoadedResource<Sampler>> _loadedSamplers;
    Map<SamplerHandle, Sampler *, SamplerHandle::Hash> _samplers;
    HandleManager<SamplerHandle> _samplerHandles;

    Map<string, LoadedResource<Texture>> _loadedTextures;
    Map<TextureHandle, Texture *, TextureHandle::Hash> _textures;
    HandleManager<TextureHandle> _textureHandles;

  private:
    TextureManager(const TextureManager &) = delete;
    TextureManager(TextureManager &&) = delete;
    TextureManager &operator=(const TextureManager &) = delete;
    TextureManager &operator=(TextureManager &&) = delete;
  };
}