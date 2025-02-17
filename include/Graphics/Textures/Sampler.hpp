#pragma once

#include "Base/Types.hpp"
#include "Graphics/Colour.hpp"
#include "Graphics/Handles.hpp"
#include "Utils/Hash.hpp"

namespace Krys::Gfx
{
  /// @brief Available modes when sampling outside of the range (0, 0) to (1, 1).
  enum class SamplerAddressMode : uint8
  {
    /// @brief Repeats the texture.
    Repeat,

    /// @brief Mirrors the texture.
    Mirror,

    /// @brief Clamps the texture to the edge, using the texture's edge colour.
    ClampToEdge,

    /// @brief Clamps the texture to the border, using the border colour.
    ClampToBorder,
  };

  /// @brief Available filters for sampling a texture.
  enum class SamplerFilter : uint8
  {
    /// @brief Nearest neighbour sampling.
    Nearest,

    /// @brief Linear interpolation sampling.
    Linear,
  };

  /// @brief The available settings of a sampler.
  struct SamplerDescriptor
  {
    SamplerAddressMode AddressModeS {SamplerAddressMode::Repeat};
    SamplerAddressMode AddressModeT {SamplerAddressMode::Repeat};
    SamplerAddressMode AddressModeR {SamplerAddressMode::Repeat};

    Colour BorderColour {0.0f, 0.0f, 0.0f, 1.0f};

    SamplerFilter MinFilter {SamplerFilter::Linear};
    SamplerFilter MagFilter {SamplerFilter::Linear};

    bool UseMipmaps {false};
    SamplerFilter MipmapFilter {SamplerFilter::Linear};

    bool operator==(const SamplerDescriptor &other) const noexcept = default;
    bool operator!=(const SamplerDescriptor &other) const noexcept = default;
  };

  /// @brief Represents a texture sampler.
  class Sampler
  {
  public:
    virtual ~Sampler() noexcept = default;

    /// @brief Gets the descriptor of the sampler.
    const SamplerDescriptor &GetDescriptor() const noexcept;

    /// @brief Gets the handle of the sampler.
    SamplerHandle GetHandle() const noexcept;

  protected:
    /// @brief Constructs a sampler.
    /// @param descriptor The descriptor of the sampler.
    /// @param handle The handle of the sampler.
    Sampler(SamplerHandle handle, const SamplerDescriptor &descriptor) noexcept;

    SamplerHandle _handle;
    SamplerDescriptor _descriptor;

  private:
    Sampler(const Sampler &other) = delete;
    Sampler(Sampler &&other) = delete;
    Sampler &operator=(const Sampler &other) = delete;
    Sampler &operator=(Sampler &&other) = delete;
  };
}

namespace std
{
  template <>
  struct hash<Krys::Gfx::SamplerDescriptor>
  {
    size_t operator()(const Krys::Gfx::SamplerDescriptor &descriptor) const noexcept
    {
      return Krys::HashCombine(descriptor.AddressModeS, descriptor.AddressModeT, descriptor.AddressModeR,
                               descriptor.BorderColour, descriptor.MinFilter, descriptor.MagFilter,
                               descriptor.UseMipmaps, descriptor.MipmapFilter);
    }
  };
}