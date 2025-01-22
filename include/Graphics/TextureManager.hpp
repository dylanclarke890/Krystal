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
  class TextureManager
  {
  public:
    TextureManager() noexcept = default;
    virtual ~TextureManager() noexcept = default;

    NO_DISCARD SamplerHandle DefaultTextureSampler() noexcept;

    NO_DISCARD SamplerHandle CreateSampler(const SamplerDescriptor &descriptor) noexcept;

    NO_DISCARD TextureHandle CreateTexture(const IO::Image &data,
                                           TextureUsageHint hint = TextureUsageHint::Image) noexcept;
    NO_DISCARD TextureHandle CreateTexture(const IO::Image &image, SamplerHandle sampler,
                                           TextureUsageHint hint = TextureUsageHint::Image) noexcept;

    NO_DISCARD Sampler &GetSampler(SamplerHandle handle) const noexcept;
    NO_DISCARD Texture &GetTexture(TextureHandle handle) const noexcept;

    NO_DISCARD TextureHandle LoadTexture(const string &path,
                                         TextureUsageHint hint = TextureUsageHint::Image) noexcept;
    NO_DISCARD TextureHandle LoadTexture(const string &path, SamplerHandle sampler,
                                         TextureUsageHint hint = TextureUsageHint::Image) noexcept;

    void Unload(SamplerHandle handle) noexcept;
    void Unload(TextureHandle handle) noexcept;

  protected:
    NO_DISCARD SamplerHandle NextSamplerHandle() noexcept;
    NO_DISCARD TextureHandle NextTextureHandle() noexcept;

    virtual void OnDestroy(SamplerHandle handle) noexcept;
    virtual void OnDestroy(TextureHandle handle) noexcept;

    NO_DISCARD virtual Unique<Sampler> CreateSamplerImpl(SamplerHandle handle,
                                                         const SamplerDescriptor &descriptor) noexcept = 0;

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

    SamplerHandle _nextSamplerHandle {0};
    Map<SamplerDescriptor, LoadedResource<Sampler>> _loadedSamplers;
    Map<SamplerHandle, Sampler *, SamplerHandle::Hash> _samplers;
    List<SamplerHandle> _recycledSamplerHandles;

    TextureHandle _nextTextureHandle {0};
    Map<string, LoadedResource<Texture>> _loadedTextures;
    Map<TextureHandle, Texture *, TextureHandle::Hash> _textures;
    List<TextureHandle> _recycledTextureHandles;

  private:
    TextureManager(const TextureManager &) = delete;
    TextureManager(TextureManager &&) = delete;
    TextureManager &operator=(const TextureManager &) = delete;
    TextureManager &operator=(TextureManager &&) = delete;
  };
}