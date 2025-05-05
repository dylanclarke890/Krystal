#include "Graphics/Textures/TextureManager.hpp"
#include "Graphics/Colours.hpp"
#include "IO/Logger.hpp"

#include <sstream>

namespace Krys::Gfx
{
#pragma region Samplers

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

  Sampler *TextureManager::GetSampler(SamplerHandle handle) const noexcept
  {
    KRYS_ASSERT(handle.IsValid(), "TextureManager: Invalid sampler handle.");

    auto it = _samplers.find(handle);
    return it == _samplers.end() ? nullptr : it->second;
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

#pragma endregion Samplers

  TextureHandle TextureManager::CreateTexture(const TextureDescriptor &descriptor,
                                              const List<byte> &data) noexcept
  {
    auto desc = descriptor; // Copy to modify
    if (desc.Name.empty())
    {
      static uint32 counter = 0;
      std::stringstream strm;
      strm << "Texture_" << counter;
      counter++;
      desc.Name = strm.str();
    }

    if (_loadedTextures.contains(desc.Name))
    {
      auto &loaded = _loadedTextures[desc.Name];
      loaded.ReferenceCount++;
      Logger::Info("TextureManager: Loaded '{0}' from cache ({1} references).", desc.Name,
                   loaded.ReferenceCount);

      return loaded.Resource->GetHandle();
    }

    if (!desc.Sampler.IsValid())
      desc.Sampler = DefaultTextureSampler();

    KRYS_ASSERT(GetSampler(desc.Sampler) != nullptr, "TextureManager: Invalid sampler handle.");

    auto handle = _textureHandles.Next();
    auto texture = CreateTextureImpl(handle, desc, data);

    Logger::Info("TextureManager: Created '{0}' ({1}x{2}).", desc.Name, desc.Width, desc.Height);

    _loadedTextures[desc.Name] = {1u, std::move(texture)};
    _textures[handle] = _loadedTextures[desc.Name].Resource.get();

    return handle;
  }

  TextureHandle TextureManager::LoadTexture(const string &path, const TextureDescriptor &descriptor) noexcept
  {
    auto desc = descriptor; // Copy to modify
    KRYS_ASSERT(desc.Type == TextureType::Image || desc.Type == TextureType::Data,
                "TextureManager: Can only load image or data textures from file.");

    if (_loadedTextures.contains(path))
    {
      auto &loaded = _loadedTextures[path];
      loaded.ReferenceCount++;
      Logger::Info("TextureManager: Loaded '{0}' from cache ({1} references).", path, loaded.ReferenceCount);

      return loaded.Resource->GetHandle();
    }

    auto loadedImage = IO::LoadImage(path);
    // TODO: handle this more gracefully
    KRYS_ASSERT(loadedImage.has_value(), "TextureManager: Failed to load '{0}': {1}", path,
                loadedImage.error());
    auto &image = loadedImage.value();
    desc.Width = image.Width;
    desc.Height = image.Height;
    desc.Channels = image.Channels;

    auto handle = _textureHandles.Next();
    if (desc.Name.empty())
      desc.Name = path;

    if (!desc.Sampler.IsValid())
      desc.Sampler = DefaultTextureSampler();

    auto texture = CreateTextureImpl(handle, desc, image.Data);

    _loadedTextures[path] = {1u, std::move(texture)};
    _textures[handle] = _loadedTextures[path].Resource.get();

    Logger::Info("TextureManager: Loaded '{0}' into memory ({1}x{2}).", path, desc.Width, desc.Height);

    return handle;
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

  void TextureManager::OnDestroy(SamplerHandle) noexcept
  {
  }

  void TextureManager::OnDestroy(TextureHandle) noexcept
  {
  }

  TextureHandleMap<Texture *> &TextureManager::GetTextures() noexcept
  {
    return _textures;
  }

  TextureHandle TextureManager::CreateFlatColourTexture(const Colour &colour) noexcept
  {
    auto name = std::format("FlatColour_{0}", colour);
    return CreateTexture(TextureDescriptor {.Name = name,
                                            .Type = TextureType::Image,
                                            .Width = 1,
                                            .Height = 1,
                                            .Channels = 4,
                                            .Sampler = DefaultTextureSampler()},
                         {Colour::AsBytes(colour)});
  }
}