#pragma once

#include "Base/Types.hpp"
#include "Graphics/Colour.hpp"
#include "Graphics/Handles.hpp"

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

  /// @brief Describes various aspects of a sampler.
  struct SamplerDescriptor
  {
    SamplerAddressMode AddressModeU;
    SamplerAddressMode AddressModeV;
    SamplerAddressMode AddressModeW;

    Colour BorderColour;

    SamplerFilter MinFilter;
    SamplerFilter MagFilter;

    bool UseMipmaps;
    SamplerFilter MipmapFilter;
  };

  /// @brief Represents a texture sampler.
  class Sampler
  {
  public:
    virtual ~Sampler() noexcept = default;

    /// @brief Constructs a sampler.
    /// @param descriptor The descriptor of the sampler.
    /// @param handle The handle of the sampler.
    Sampler(SamplerHandle handle, const SamplerDescriptor &descriptor) noexcept;

    /// @brief Gets the descriptor of the sampler.
    const SamplerDescriptor &GetDescriptor() const noexcept;

    /// @brief Gets the handle of the sampler.
    SamplerHandle GetHandle() const noexcept;

  private:
    SamplerDescriptor _descriptor;
    SamplerHandle _handle;

    Sampler(const Sampler &other) = delete;
    Sampler(Sampler &&other) = delete;
    Sampler &operator=(const Sampler &other) = delete;
    Sampler &operator=(Sampler &&other) = delete;
  };
}