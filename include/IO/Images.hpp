#include "Base/Attributes.hpp"
#include "Base/Pointers.hpp"
#include "Base/Types.hpp"
#include "Core/Debug/Macros.hpp"

#include "IO/IO.hpp"

#pragma warning(push)
#pragma warning(disable : 4'505) // Suppress "unreferenced function with internal linkage" warnings
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#pragma warning(pop)

#include <concepts>

namespace Krys::IO::Impl
{
  struct stbiCustomDeleter
  {
    void operator()(byte *data) const noexcept
    {
      stbi_image_free(data);
    }
  };
}

namespace Krys::IO
{
  template <typename T>
  concept ImageLoadPolicy = requires(T) {
    { T::FlipImageVerticallyOnLoad } -> std::convertible_to<bool>;
  };

  struct DefaultImageLoadPolicy
  {
    static constexpr bool FlipImageVerticallyOnLoad = true;
  };

  using ImageData = Unique<byte[], Impl::stbiCustomDeleter>;

  struct ImageLoadResult
  {
    ImageData Data;
    int Width;
    int Height;
    int Channels;
  };

  /// @brief Loads an image into memory and frees it when the object is destroyed.
  /// Useful for loading textures into the GPU.
  /// @tparam Policy
  template <ImageLoadPolicy Policy = DefaultImageLoadPolicy>
  NO_DISCARD Expected<ImageLoadResult> LoadImage(const string &path, int desiredChannels = 0) noexcept
  {
    KRYS_SCOPED_PROFILER("IO::LoadImage");

    if (!IO::PathExists(path))
      return Unexpected<string>("File does not exist");

    stbi_set_flip_vertically_on_load(Policy::FlipImageVerticallyOnLoad);

    int width, height, channels;
    auto *rawData = stbi_load(path.c_str(), &width, &height, &channels, desiredChannels);
    if (rawData == nullptr)
      return Unexpected<string>(stbi_failure_reason());

    ImageLoadResult result;
    result.Data = ImageData(reinterpret_cast<byte *>(rawData));

    return result;
  }
}