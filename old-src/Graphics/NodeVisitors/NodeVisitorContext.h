#pragma once

#include "Graphics/Renderer.h"

namespace Krys::Gfx
{
  struct NodeVisitorContext
  {
    typedef Ref<Renderer> RendererRef;

    RendererRef Renderer;
  };
}