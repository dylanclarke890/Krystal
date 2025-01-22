#include "IO/Images.hpp"
#include "MTL/Common/Rounding.hpp"

namespace Krys::IO
{
  // TODO: revisit this, it's not the best way to generate mipmaps.
  List<MipLevelData> GenerateMipmaps(const Image &image) noexcept
  {
    List<MipLevelData> levels;
    levels.push_back({image.Data, image.Width, image.Height});

    auto scale = 2u;

    uint32 width = image.Width / scale;
    uint32 height = image.Height / scale;
    while (width > 0 && height > 0)
    {
      const auto stride = image.Channels;
      const auto scaleX = static_cast<float>(levels.back().Width) / static_cast<float>(width);
      const auto scaleY = static_cast<float>(levels.back().Height) / static_cast<float>(height);

      ImageData data(width * height * stride);
      const auto *src = levels.back().Data.data();
      auto *dst = data.data();

      // simple downsize algorithm by skipping pixels, will produce aliasing
      for (auto y = 0u; y < height; ++y)
      {
        const auto yNearest = static_cast<int>(MTL::Floor(y * scaleY));

        for (auto x = 0u; x < width; ++x)
        {
          const auto xNearest = static_cast<int>(MTL::Floor(x * scaleX));
          std::memcpy(dst, src + ((yNearest * levels.back().Width) + xNearest) * stride, stride);
          dst += stride;
        }
      }

      levels.push_back({.Data = std::move(data), .Width = width, .Height = height});

      width /= scale;
      height /= scale;
    }
    return levels;
  }
}