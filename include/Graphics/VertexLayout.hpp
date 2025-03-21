#pragma once

#include "Base/Types.hpp"
#include "Graphics/Colour.hpp"
#include "MTL/Vectors/Ext/Hash.hpp"
#include "MTL/Vectors/Vec2.hpp"
#include "MTL/Vectors/Vec3.hpp"

namespace Krys::Gfx
{
  struct VertexData
  {
    VertexData(const Vec3 &position, const Vec3 &normal, const Colour &colour,
               const Vec3 &textureCoords) noexcept
        : Position(position), Normal(normal), Colour(colour), TextureCoords(textureCoords)
    {
    }

    Vec3 Position;
    float PositionPadding{0.f};
    Vec3 Normal;
    float NormalPadding{0.f};
    Colour Colour;
    Vec3 TextureCoords;
    float TextureCoordsPadding{0.f};

    bool operator==(const VertexData &other) const noexcept
    {
      // TODO: add epsilon comparison
      return Position == other.Position && Normal == other.Normal && Colour == other.Colour
             && TextureCoords == other.TextureCoords;
    }
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

namespace std
{
  template <>
  struct hash<Krys::Gfx::VertexData>
  {
    size_t operator()(const Krys::Gfx::VertexData &vertex) const noexcept
    {
      return std::hash<Krys::Vec3>()(vertex.Position) ^ std::hash<Krys::Vec3>()(vertex.Normal)
             ^ std::hash<Krys::Gfx::Colour>()(vertex.Colour) ^ std::hash<Krys::Vec3>()(vertex.TextureCoords);
    }
  };
}