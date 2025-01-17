#pragma once

#include "Base/Types.hpp"
#include "Graphics/Colour.hpp"
#include "MTL/Vectors/Vec3.hpp"

namespace Krys::Gfx
{
  struct VertexData
  {
    explicit VertexData(const Vec3 &position, const Colour &colour) noexcept
        : Position(position), Colour(colour)
    {
    }

    Vec3 Position;
    float PositionPadding;
    Colour Colour;
  };

  enum class VertexAttributeType : uint8
  {
    FLOAT_1,
    FLOAT_2,
    FLOAT_3,
    FLOAT_4,
    UINT32_1,
    UINT32_2,
    UINT32_3,
    UINT32_4
  };

  struct VertexAttribute
  {
    VertexAttributeType Type;
    uint8 Components;
    uint32 Offset;
    uint32 Size;
  };

  class VertexLayout
  {
  public:
    static VertexLayout Default() noexcept;

    using attributes_list_t = List<VertexAttribute>;
    using const_iterator = attributes_list_t::const_iterator;

    VertexLayout(const List<VertexAttributeType> &attributeTypes) noexcept;
    ~VertexLayout() noexcept = default;

    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;

    size_t GetStride() const noexcept;

  private:
    attributes_list_t _attributes {};
    size_t _stride;
  };
}