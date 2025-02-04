#pragma once

#include "Base/Attributes.hpp"
#include "Base/Pointers.hpp"
#include "Base/Types.hpp"
#include "Debug/Macros.hpp"

#include "IO/IO.hpp"

#include "stb_image.h"

#include <concepts>

namespace Krys::IO::Impl
{
  struct stbiCustomDeleter
  {
    void operator()(stbi_uc *data) const noexcept
    {
      stbi_image_free(data);
    }
  };
}

namespace Krys::IO
{
  /// @brief Represents image data.
  using ImageData = List<byte>;

  /// @brief Represents an image.
  struct Image
  {
    /// @brief Image data.
    ImageData Data;

    /// @brief Width of image (in pixels).
    uint32 Width;

    /// @brief Height of image (in pixels).
    uint32 Height;

    /// @brief Number of channels.
    uint8 Channels;
  };

  /// @brief Represents a mip level of an image.
  struct MipLevelData
  {
    /// @brief Image data.
    ImageData Data;

    /// @brief Width of level (in pixels).
    uint32 Width;

    /// @brief Height of level (in pixels).
    uint32 Height;
  };

  /// @brief Generates mipmaps down to a 1x1 pixel.
  /// @details The supplied level will always be the first entry in the returned collection.
  /// The algorithm used is a simple downsize by averaging the values of a 2x2 kernel.
  /// @return Collection of MipLevelData objects where each subsequent entry is half the size of the preceding
  /// one.
  List<MipLevelData> GenerateMipmaps(const Image &image) noexcept;

  template <typename T>
  concept LoadImageSettings = requires(T) {
    { T::FlipImageVerticallyOnLoad } -> std::convertible_to<bool>;
    { T::DesiredChannels } -> std::convertible_to<uint8>;
  };

  struct DefaultLoadImageSettings
  {
    static constexpr bool FlipImageVerticallyOnLoad = true;
    static constexpr uint8 DesiredChannels = 0;
  };

  /// @brief Loads an image into memory and frees it when the object is destroyed.
  /// Useful for loading textures into the GPU.
  /// @tparam Settings The settings to use when loading the image.
  template <LoadImageSettings Settings = DefaultLoadImageSettings>
  NO_DISCARD Expected<Image> LoadImage(const string &path) noexcept
  {
    KRYS_SCOPED_PROFILER("IO::LoadImage");

    if (!IO::PathExists(path))
      return Unexpected<string>("File does not exist");

    stbi_set_flip_vertically_on_load(Settings::FlipImageVerticallyOnLoad);

    int width, height, channels;
    using AutoFree = Unique<stbi_uc[], Impl::stbiCustomDeleter>;
    AutoFree data(stbi_load(path.c_str(), &width, &height, &channels, Settings::DesiredChannels));
    if (data == nullptr)
      return Unexpected<string>(stbi_failure_reason());

    Image result;
    result.Width = static_cast<uint32>(width);
    result.Height = static_cast<uint32>(height);
    result.Channels = static_cast<uint8>(channels);
    result.Data.resize(result.Width * result.Height * result.Channels);
    std::memcpy(result.Data.data(), data.get(), result.Data.size());

    return result;
  }
}