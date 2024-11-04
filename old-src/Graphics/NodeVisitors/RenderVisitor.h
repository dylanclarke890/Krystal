#pragma once

#include "Graphics/NodeVisitors/NodeVisitor.h"
#include "Graphics/Renderer.h"

namespace Krys::Graphics
{
  class RenderVisitor : public NodeVisitor
  {
  public:
    void Visit(const Node &node) noexcept override {}
    void Visit(const GeometryNode &node) noexcept override
    {
      _context.Renderer->Submit(node);
    }
  };
}