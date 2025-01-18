#pragma once

#include "Types.h"
#include "Graphics/NodeVisitors/NodeVisitorContext.h"

namespace Krys::Gfx
{
  class NodeVisitorFactory
  {
  private:
    NodeVisitorContext _context;

  public:
    NodeVisitorFactory(NodeVisitorContext context) noexcept
        : _context(context) {}

    template <typename T, typename... Args>
    Unique<T> CreateVisitor(Args &&...args) noexcept
    {
      return CreateRef<T>(_context, std::forward<Args>(args)...);
    }
  };
}