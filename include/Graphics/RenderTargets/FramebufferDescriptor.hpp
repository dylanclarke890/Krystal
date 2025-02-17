#pragma once

#include "Base/Types.hpp"
#include "Graphics/Handles.hpp"

namespace Krys::Gfx
{
  struct FramebufferDescriptor
  {
    uint32 Width;
    uint32 Height;
    bool Multisampled;
    RenderTargetHandle DepthAttachment;
    RenderTargetHandle StencilAttachment;
    List<RenderTargetHandle> ColourAttachments;
  };
}