#pragma once

#include "Base/Types.hpp"

namespace Krys::Gfx
{
  enum class RenderTargetType : uint8
  {
    Colour,
    Depth,
    Stencil,
    DepthStencil
  };
}