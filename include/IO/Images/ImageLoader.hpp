#include "Base/Attributes.hpp"
#include "Base/Types.hpp"
#include "IO/IO.hpp"

#pragma warning(push)
#pragma warning(disable : 4'505) // Suppress "unreferenced function with internal linkage" warnings
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#pragma warning(pop)

#include <concepts>

namespace Krys::IO
{
  template <typename T>
  concept ImageLoadPolicy = requires(T) {
    { T::FlipImageVerticallyOnLoad } -> std::convertible_to<bool>;
  };

  struct ImageLoadResult
  {
    uchar *Data;
    int Width;
    int Height;
    int Channels;
  };

  struct DefaultImageLoadPolicy
  {
    static constexpr bool FlipImageVerticallyOnLoad = true;
  };

  template <ImageLoadPolicy Policy = DefaultImageLoadPolicy>
  class ImageLoader
  {
  public:
    ImageLoader(string path) noexcept : _path(path)
    {
    }

    ~ImageLoader() noexcept
    {
      if (_loaded && _data != nullptr)
        stbi_image_free(_data);
    }

    NO_DISCARD Expected<ImageLoadResult> Load(int desiredChannels = 0) noexcept
    {
      if (!IO::PathExists(_path))
        return Unexpected<string>("File does not exist");

      stbi_set_flip_vertically_on_load(Policy::FlipImageVerticallyOnLoad);

      int width, height, channels;

      _data = stbi_load(_path.c_str(), &width, &height, &channels, desiredChannels);
      _loaded = true;

      if (_data == nullptr)
        return Unexpected<string>(stbi_failure_reason());
      return ImageLoadResult {_data, width, height, channels};
    }

  private:
    string _path;
    bool _loaded {false};
    uchar *_data {nullptr};
  };

}