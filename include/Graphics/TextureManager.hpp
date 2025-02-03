#pragma once

#include "Base/Attributes.hpp"
#include "Base/Macros.hpp"
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

    /// @brief Gets a sampler by its handle.
    /// @param handle The handle of the sampler.
    /// @return The sampler or nullptr if the handle is invalid.
    NO_DISCARD Sampler *GetSampler(SamplerHandle handle) const noexcept;

    /// @brief Unloads a sampler.
    /// @param handle The handle of the sampler.
    /// @return True if the sampler was found, false otherwise.
    /// @note Will only destroy the sampler if its' reference count is 0.
    bool Unload(SamplerHandle handle) noexcept;

    /// @brief Create a texture.
    /// @param descriptor The descriptor of the texture.
    /// @param data Optional data to initialise the texture with.
    NO_DISCARD TextureHandle CreateTexture(const TextureDescriptor &descriptor,
                                           const List<byte> &data = {}) noexcept;

    /// @brief Loads a texture from a file.
    /// @param path The path to the file.
    /// @param descriptor The descriptor of the texture. Can be left empty to use defaults.
    /// @note The width, height and channels with automatically be set using the loaded image data, if you set
    /// them they will be overridden.
    NO_DISCARD TextureHandle LoadTexture(const string &path,
                                         const TextureDescriptor &descriptor = {}) noexcept;

    /// @brief Gets a texture by its handle.
    /// @param handle The handle of the texture.
    /// @return The texture or nullptr if the handle is invalid.
    NO_DISCARD Texture *GetTexture(TextureHandle handle) const noexcept;

    /// @brief Unloads a texture.
    /// @param handle The handle of the texture.
    /// @return True if the texture was found, false otherwise.
    /// @note Will only destroy the texture if its' reference count is 0.
    bool Unload(TextureHandle handle) noexcept;

    NO_DISCARD TextureHandleMap<Texture *> &GetTextures() noexcept;

    NO_DISCARD TextureHandle GetBlankTexture() noexcept;

  protected:
    TextureManager() noexcept = default;

    /// @brief Implementation-specific creation of a sampler.
    /// @param handle The handle of the sampler.
    /// @param descriptor The descriptor of the sampler.
    NO_DISCARD virtual Unique<Sampler> CreateSamplerImpl(SamplerHandle handle,
                                                         const SamplerDescriptor &descriptor) noexcept = 0;

    /// @brief Implementation-specific creation of a texture.
    /// @param handle The handle of the texture.
    /// @param descriptor The descriptor of the texture.
    /// @param data Optional data to initialise the texture with.
    NO_DISCARD virtual Unique<Texture> CreateTextureImpl(TextureHandle handle,
                                                         const TextureDescriptor &descriptor,
                                                         const List<byte> &data = {}) noexcept = 0;

    /// @brief Optional hook for implementation. Called when a sampler is destroyed (ref count hits zero).
    virtual void OnDestroy(SamplerHandle handle) noexcept;

    /// @brief Optional hook for implementation. Called when a texture is destroyed (ref count hits zero).
    virtual void OnDestroy(TextureHandle handle) noexcept;

  protected:
    NO_COPY_MOVE(TextureManager);

    template <class T>
    struct LoadedResource
    {
      size_t ReferenceCount;
      Unique<T> Resource;
    };

    SamplerHandleMap<Sampler *> _samplers;
    SamplerHandleManager _samplerHandles;
    Map<SamplerDescriptor, LoadedResource<Sampler>> _loadedSamplers;

    TextureHandleMap<Texture *> _textures;
    TextureHandleManager _textureHandles;
    Map<string, LoadedResource<Texture>> _loadedTextures;
  };
}