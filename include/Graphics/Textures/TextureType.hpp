#pragma once

#include "Base/Types.hpp"

namespace Krys::Gfx
{
  enum class TextureType : uint32
  {
    /// @brief A texture that stores arbitrary data.
    /// @note This type is suitable for storing data that isn't directly sampled, such as lookup tables,
    /// noise textures, or other data that you manipulate in your shaders.
    Data,

    /// @brief A standard image texture that’s typically loaded from a file. This type is meant for textures
    /// that you sample in your shaders, like diffuse, albedo, or normal maps.
    Image,

    /// @brief A texture that stores font data such as glyphs and kerning information.
    /// @note This type is used for rendering text in your application. It is not meant for textures that
    /// you sample in your shaders.
    Font,

    /// @brief A render target that stores colour data.
    /// @note This type is used for off-screen rendering, post-processing, and other advanced rendering
    /// techniques. It is not meant for textures that you sample in your shaders.
    RenderTargetColour,

    /// @brief A render target that stores depth data.
    /// @note This type is used for off-screen rendering, post-processing, and other advanced rendering
    /// techniques. It is not meant for textures that you sample in your shaders.
    RenderTargetDepth,

    /// @brief A render target that stores stencil data.
    /// @note This type is used for off-screen rendering, post-processing, and other advanced rendering
    /// techniques. It is not meant for textures that you sample in your shaders.
    RenderTargetStencil,

    /// @brief A render target that stores both depth and stencil data.
    /// @note This type is used for off-screen rendering, post-processing, and other advanced rendering
    /// techniques. It is not meant for textures that you sample in your shaders.
    RenderTargetDepthStencil
  };
}