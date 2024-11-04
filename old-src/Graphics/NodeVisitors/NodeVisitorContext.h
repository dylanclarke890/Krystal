#pragma once

#include "Graphics/Renderer.h"

namespace Krys::Graphics
{
  struct NodeVisitorContext
  {
    typedef Ref<Renderer> RendererRef;

    RendererRef Renderer;
  };
}