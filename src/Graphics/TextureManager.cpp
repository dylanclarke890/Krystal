#include "Graphics/TextureManager.hpp"
#include "Core/Logger.hpp"

#include <sstream>

namespace Krys::Gfx
{
  SamplerHandle TextureManager::DefaultTextureSampler() noexcept
  {
    return CreateSampler(SamplerDescriptor {});
  }

  SamplerHandle TextureManager::CreateSampler(const SamplerDescriptor &descriptor) noexcept
  {
    if (_loadedSamplers.contains(descriptor))
    {
      auto &loaded = _loadedSamplers[descriptor];
      loaded.ReferenceCount++;
      Logger::Info("TextureManager: Loaded sampler from cache ({0} references).", loaded.ReferenceCount);

      return loaded.Resource->GetHandle();
    }

    auto handle = _samplerHandles.Next();
    auto sampler = CreateSamplerImpl(handle, descriptor);

    _loadedSamplers[descriptor] = {1u, std::move(sampler)};
    _samplers[handle] = _loadedSamplers[descriptor].Resource.get();

    Logger::Info("TextureManager: Created new sampler.");

    return handle;
  }

  TextureHandle TextureManager::CreateTexture(const IO::Image &image, TextureUsageHint hint) noexcept
  {
    return CreateTexture(image, {}, hint);
  }

  TextureHandle TextureManager::CreateTexture(const IO::Image &image, SamplerHandle sampler,
                                              TextureUsageHint hint) noexcept
  {
    static uint32 counter = 0;

    std::stringstream strm;
    strm << "T" << counter;
    counter++;

    const auto resourceName = strm.str();
    Logger::Info("TextureManager: Created '{0}' ({1}x{2}).", resourceName, image.Width, image.Height);

    auto handle = _textureHandles.Next();
    auto texture = CreateTextureImpl(resourceName, handle,
                                     sampler.IsValid() ? sampler : DefaultTextureSampler(), image, hint);

    _loadedTextures[resourceName] = {1u, std::move(texture)};
    _textures[handle] = _loadedTextures[resourceName].Resource.get();

    return handle;
  }

  TextureHandle TextureManager::LoadTexture(const string &path, TextureUsageHint hint) noexcept
  {
    return LoadTexture(path, {}, hint);
  }

  TextureHandle TextureManager::LoadTexture(const string &path, SamplerHandle sampler,
                                            TextureUsageHint hint) noexcept
  {
    KRYS_ASSERT(hint == TextureUsageHint::Image || hint == TextureUsageHint::Data,
                "TextureManager: Can only load image or data textures from file.");

    if (_loadedTextures.contains(path))
    {
      auto &loaded = _loadedTextures[path];
      loaded.ReferenceCount++;
      Logger::Info("TextureManager: Loaded '{0}' from cache ({1} references).", path, loaded.ReferenceCount);

      return loaded.Resource->GetHandle();
    }

    auto loadedImage = IO::LoadImage(path);
    KRYS_ASSERT(loadedImage, "TextureManager: Failed to load '{0}': {1}", path, loadedImage.error());

    auto handle = _textureHandles.Next();
    auto texture = CreateTextureImpl(path, handle, sampler.IsValid() ? sampler : DefaultTextureSampler(),
                                     loadedImage.value(), hint);

    _loadedTextures[path] = {1u, std::move(texture)};
    _textures[handle] = _loadedTextures[path].Resource.get();

    Logger::Info("TextureManager: Loaded '{0}' into memory ({1}x{2}).", path, loadedImage.value().Width,
                 loadedImage.value().Height);

    return handle;
  }

  Sampler *TextureManager::GetSampler(SamplerHandle handle) const noexcept
  {
    KRYS_ASSERT(handle.IsValid(), "TextureManager: Invalid sampler handle.");

    auto it = _samplers.find(handle);
    return it == _samplers.end() ? nullptr : it->second;
  }

  Texture *TextureManager::GetTexture(TextureHandle handle) const noexcept
  {
    KRYS_ASSERT(handle.IsValid(), "TextureManager: Invalid texture handle.");

    auto it = _textures.find(handle);
    return it == _textures.end() ? nullptr : it->second;
  }

  bool TextureManager::Unload(TextureHandle handle) noexcept
  {
    KRYS_ASSERT(handle.IsValid(), "TextureManager: Invalid texture handle.");

    auto it = _textures.find(handle);
    if (it == _textures.end())
      return false;

    const auto &resourceName = it->second->GetName();
    auto &loaded = _loadedTextures.find(resourceName)->second;

    auto refCount = --loaded.ReferenceCount;
    Logger::Info("TextureManager: Unloaded '{0}' ({1} references remaining).", resourceName, refCount);

    if (refCount == 0)
    {
      OnDestroy(handle);

      _loadedTextures.erase(resourceName);
      _textures.erase(it);
      _textureHandles.Recycle(handle);
      Logger::Info("TextureManager: Recycled handle for '{0}'.", resourceName);
    }

    return true;
  }

  bool TextureManager::Unload(SamplerHandle handle) noexcept
  {
    // TODO: remember to add the check for the default cube map sampler when we add that.
    if (handle == DefaultTextureSampler())
    {
      Logger::Warn("TextureManager: Cannot unload a default texture sampler.");
      return false;
    }

    auto it = _samplers.find(handle);
    if (it == _samplers.end())
      return false;

    const auto &descriptor = it->second->GetDescriptor();
    auto &loaded = _loadedSamplers.find(descriptor)->second;

    auto refCount = --loaded.ReferenceCount;
    Logger::Info("TextureManager: Unloaded sampler ({0} references remaining).", refCount);

    if (refCount == 0)
    {
      OnDestroy(handle);

      _loadedSamplers.erase(descriptor);
      _samplers.erase(it);
      _samplerHandles.Recycle(handle);
      Logger::Info("TextureManager: Recycled handle for sampler.");
    }

    return true;
  }

  void TextureManager::OnDestroy(SamplerHandle) noexcept
  {
  }

  void TextureManager::OnDestroy(TextureHandle) noexcept
  {
  }
}