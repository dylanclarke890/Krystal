#pragma once

#include "Base/Types.hpp"
#include "Graphics/RenderTargets/RenderTargetType.hpp"

namespace Krys::Gfx
{
  struct RenderTargetDescriptor
  {
    uint32 Width;
    uint32 Height;
    RenderTargetType Type;
    bool Multisampled;
  };
}