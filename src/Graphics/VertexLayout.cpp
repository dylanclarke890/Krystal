#include "Graphics/VertexLayout.hpp"
#include "Core/Debug/Macros.hpp"

namespace Krys::Gfx
{
  struct VertexTypeInfo
  {
    /// @brief Number of components in the attribute.
    uint8 Components;

    /// @brief Size of a single component.
    size_t Size;
  };

  constexpr VertexTypeInfo GetTypeInfo(VertexAttributeType type) noexcept
  {
    switch (type)
    {
      case VertexAttributeType::FLOAT_1:  return {1, sizeof(float)};
      case VertexAttributeType::FLOAT_2:  return {2, sizeof(float)};
      case VertexAttributeType::FLOAT_3:  return {3, sizeof(float)};
      case VertexAttributeType::FLOAT_4:  return {4, sizeof(float)};
      case VertexAttributeType::UINT32_1: return {1, sizeof(uint32)};
      case VertexAttributeType::UINT32_2: return {2, sizeof(uint32)};
      case VertexAttributeType::UINT32_3: return {3, sizeof(uint32)};
      case VertexAttributeType::UINT32_4: return {4, sizeof(uint32)};
      default:                            KRYS_ASSERT(false, "Invalid vertex attribute type"); return {0, 0};
    }
  }

  VertexLayout::VertexLayout(const List<VertexAttributeType> &attributeTypes) noexcept
  {
    uint32 offset = 0u;
    for (auto &attributeType : attributeTypes)
    {
      auto [components, size] = GetTypeInfo(attributeType);
      VertexAttribute attribute;
      attribute.Type = attributeType;
      attribute.Offset = offset;
      attribute.Size = static_cast<uint32>(size);
      attribute.Components = components;
      _attributes.push_back(attribute);

      offset += static_cast<uint32>(size * components);
    }

    _stride = offset;
  }

  VertexLayout VertexLayout::Default() noexcept
  {
    return VertexLayout({VertexAttributeType::FLOAT_4, VertexAttributeType::FLOAT_4,
                         VertexAttributeType::FLOAT_4, VertexAttributeType::FLOAT_4});
  }

  VertexLayout::const_iterator VertexLayout::begin() const noexcept
  {
    return _attributes.cbegin();
  }

  VertexLayout::const_iterator VertexLayout::end() const noexcept
  {
    return _attributes.cend();
  }

  size_t VertexLayout::GetStride() const noexcept
  {
    return _stride;
  }
}