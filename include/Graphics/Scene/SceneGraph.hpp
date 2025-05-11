#pragma once

#include "Base/Macros.hpp"
#include "Base/Pointers.hpp"
#include "Base/Types.hpp"
#include "Graphics/Handles.hpp"
#include "Graphics/Scene/Node.hpp"

namespace Krys::Gfx
{
  class SceneGraph
  {
  public:
    NO_COPY_MOVE(SceneGraph)

    SceneGraph(SceneGraphHandle handle, const string &name) noexcept : _handle(handle), _name(name), _root(CreateUnique<Node>())
    {
    }

    ~SceneGraph() = default;

    void SetRoot(Unique<Node> root) noexcept
    {
      _root = std::move(root);
    }

    SceneGraphHandle GetHandle() const noexcept
    {
      return _handle;
    }

    const string &GetName() const noexcept
    {
      return _name;
    }

    Node *GetRoot() noexcept
    {
      return _root.get();
    }

  protected:
    SceneGraphHandle _handle;
    string _name;
    Unique<Node> _root;
  };
}