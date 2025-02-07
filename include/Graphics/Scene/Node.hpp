#pragma once

#include "Base/Pointers.hpp"
#include "Base/Types.hpp"
#include "Debug/Macros.hpp"
#include "Graphics/Transform.hpp"

namespace Krys::Gfx
{
  class Node : public std::enable_shared_from_this<Node>
  {
    using parent_t = WeakRef<Node>;
    using child_t = Ref<Node>;
    using children_t = List<child_t>;

  public:
    Node() noexcept
    {
    }

    virtual ~Node() noexcept = default;

    void AddChild(child_t child) noexcept
    {
      KRYS_ASSERT(!IsLeafOnly(), "Cannot add a child to a leaf node.");
      KRYS_ASSERT(child, "Cannot add a null child to a node.");

      child->_parent = parent_t(shared_from_this());
      _children.push_back(child);
    }

    parent_t GetParent() const noexcept
    {
      return _parent;
    }

    const children_t &GetChildren() const noexcept
    {
      KRYS_ASSERT(!IsLeafOnly(), "Cannot get children of a leaf node.");
      return _children;
    }

    children_t &GetChildren() noexcept
    {
      KRYS_ASSERT(!IsLeafOnly(), "Cannot get children of a leaf node.");
      return _children;
    }

    // TODO: I don't like the current implementation of transforms

    /// @brief Update the world transforms of this node and its children.
    void UpdateTransforms(const Transform &parentWorldTransform = {})
    {
      Transform worldTransform = ComputeWorldTransform(parentWorldTransform);
      for (auto &child : _children)
        child->UpdateTransforms(worldTransform);
    }

    /// @brief Compute the world transform of this node.
    /// @param parentWorldTransform The world transform of the parent node.
    /// @return The world transform of this node.
    virtual Transform ComputeWorldTransform(const Transform &parentWorldTransform) noexcept
    {
      return parentWorldTransform;
    }

    /// @brief Returns true if this node type can only be a leaf node.
    virtual bool IsLeafOnly() const noexcept
    {
      return false;
    }

  protected:
    parent_t _parent;
    children_t _children;
  };
}
