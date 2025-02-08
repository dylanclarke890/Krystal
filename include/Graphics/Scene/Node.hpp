#pragma once

#include "Base/Attributes.hpp"
#include "Base/Pointers.hpp"
#include "Base/Types.hpp"
#include "Debug/Macros.hpp"
#include "Graphics/Transform.hpp"
#include "Utils/StringId.hpp"

namespace Krys::Gfx
{
  typedef StringId NodeType;
  typedef StringIdHasher NodeTypeHasher;

/// @brief Convenience macro for setting up the node type for a derived `Node`.
/// @param nodeTypeName Must be a string literal. Must be unique across nodes.
#define KRYS_NODE_CLASS_TYPE(nodeTypeName)                                                                   \
  NO_DISCARD static NodeType GetStaticType() noexcept                                                        \
  {                                                                                                          \
    return SID(nodeTypeName);                                                                                \
  }                                                                                                          \
  NO_DISCARD virtual NodeType GetNodeType() const noexcept override                                          \
  {                                                                                                          \
    return GetStaticType();                                                                                  \
  }

  class Node
  {
    using parent_t = Node *;
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

      child->_parent = parent_t(this);
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

    /// @brief Returns the local transform of this node.
    virtual const Transform &GetLocalTransform() const noexcept
    {
      // Identity transform for non-transform nodes.
      static Transform localTransform;
      return localTransform;
    }

    /// @brief Returns true if this node type can only be a leaf node.
    virtual bool IsLeafOnly() const noexcept
    {
      return false;
    }

    /// @brief Returns true if this node is currently a leaf node.
    NO_DISCARD bool IsLeaf() const noexcept
    {
      return _children.empty();
    }

    NO_DISCARD static NodeType GetStaticType() noexcept
    {
      return SID("node");
    }

    NO_DISCARD virtual NodeType GetNodeType() const noexcept
    {
      return GetStaticType();
    }

  protected:
    parent_t _parent;
    children_t _children;
  };
}
