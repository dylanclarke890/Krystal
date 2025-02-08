#pragma once

#include "Graphics/Handles.hpp"
#include "Graphics/Scene/Node.hpp"

namespace Krys::Gfx
{
  class MaterialNode : public Node
  {
  public:
    MaterialNode(MaterialHandle material) noexcept : _material(material)
    {
    }

    KRYS_NODE_CLASS_TYPE("material")

    virtual ~MaterialNode() noexcept = default;

    MaterialHandle GetMaterial() const noexcept
    {
      return _material;
    }

    void SetMaterial(MaterialHandle material) noexcept
    {
      _material = material;
    }

    virtual bool IsLeafOnly() const noexcept override
    {
      return true;
    }

  protected:
    MaterialHandle _material;
  };
}