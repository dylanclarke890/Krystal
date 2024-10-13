#pragma once

#include "Graphics/NodeVisitors/NodeVisitor.h"

namespace Krys::Graphics
{
  class RenderVisitor : public NodeVisitor
  {
  public:
    void Visit(const Node &node) override {}
    void Visit(const GeometryNode &node) override {}
  };
}