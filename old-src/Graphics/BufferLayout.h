#pragma once

#include "Core.h"
#include <initializer_list>

namespace Krys::Gfx
{
  enum class ShaderDataType
  {
    None = 0,
    Float,
    Float2,
    Float3,
    Float4,
    Mat3,
    Mat4,
    Int,
    Int2,
    Int3,
    Int4,
    Bool
  };

  static uint32 GetSizeOfShaderDataType(ShaderDataType type)
  {
    switch (type)
    {
    case ShaderDataType::Float:
      return 4;
    case ShaderDataType::Float2:
      return 4 * 2;
    case ShaderDataType::Float3:
      return 4 * 3;
    case ShaderDataType::Float4:
      return 4 * 4;
    case ShaderDataType::Mat3:
      return 4 * 3 * 3;
    case ShaderDataType::Mat4:
      return 4 * 4 * 4;
    case ShaderDataType::Int:
      return 4;
    case ShaderDataType::Int2:
      return 4 * 2;
    case ShaderDataType::Int3:
      return 4 * 3;
    case ShaderDataType::Int4:
      return 4 * 4;
    case ShaderDataType::Bool:
      return 1;
    default:
    {
      KRYS_ASSERT(false, "Unknown ShaderDataType!", 0);
      return 0;
    }
    }
  }

  static uint8 GetComponentCountOfShaderDataType(ShaderDataType type)
  {
    switch (type)
    {
    case ShaderDataType::Float:
      return 1;
    case ShaderDataType::Float2:
      return 2;
    case ShaderDataType::Float3:
      return 3;
    case ShaderDataType::Float4:
      return 4;
    case ShaderDataType::Mat3:
      return 3; // 3* float3
    case ShaderDataType::Mat4:
      return 4; // 4* float4
    case ShaderDataType::Int:
      return 1;
    case ShaderDataType::Int2:
      return 2;
    case ShaderDataType::Int3:
      return 3;
    case ShaderDataType::Int4:
      return 4;
    case ShaderDataType::Bool:
      return 1;
    default:
    {
      KRYS_ASSERT(false, "Unknown ShaderDataType!", 0);
      return 0;
    }
    }
  }

  struct VertexBufferElement
  {
    string Name;
    ShaderDataType Type;
    bool Normalized;
    uint32 Size;
    uint32 Stride;
    size_t Offset;

    VertexBufferElement() = default;
    VertexBufferElement(ShaderDataType type, const string &name, bool normalized = false)
        : Name(name), Type(type), Normalized(normalized),
          Size(GetSizeOfShaderDataType(type)), Stride(0), Offset(0)
    {
    }

    uint8 GetComponentCount() const
    {
      return GetComponentCountOfShaderDataType(Type);
    }
  };

  class VertexBufferLayout
  {
  private:
    List<VertexBufferElement> _elements;
    int _attributeCount;

  public:
    VertexBufferLayout() = default;

    VertexBufferLayout(std::initializer_list<VertexBufferElement> elements)
        : _elements(elements), _attributeCount(0)
    {
      CalculateOffsetsAndStride();
      CalculateAttributeCount();
    }

    const List<VertexBufferElement> &GetElements() const { return _elements; }
    List<VertexBufferElement>::iterator begin() { return _elements.begin(); }
    List<VertexBufferElement>::iterator end() { return _elements.end(); }
    List<VertexBufferElement>::const_iterator begin() const { return _elements.begin(); }
    List<VertexBufferElement>::const_iterator end() const { return _elements.end(); }

    NO_DISCARD int GetAttributeCount() const noexcept
    {
      return _attributeCount;
    }

  private:
    void CalculateOffsetsAndStride()
    {
      KRYS_ASSERT(_elements.size(), "VertexBufferLayout has no elements", 0);

      uint32 vertexSize = 0;
      for (auto &element : _elements)
        vertexSize += element.Size;
      KRYS_ASSERT(vertexSize, "vertexSize was 0", 0);

      uint32 offset = 0;
      for (auto &element : _elements)
      {
        element.Offset = offset;
        offset += element.Size;
        element.Stride = vertexSize;
      }
    }

    void CalculateAttributeCount()
    {
      int count = 0;

      for (auto element : _elements)
      {
        switch (element.Type)
        {
        case ShaderDataType::Float:
        case ShaderDataType::Float2:
        case ShaderDataType::Float3:
        case ShaderDataType::Float4:
        case ShaderDataType::Int:
        case ShaderDataType::Int2:
        case ShaderDataType::Int3:
        case ShaderDataType::Int4:
        case ShaderDataType::Bool:
        {
          count++;
          break;
        }
        case ShaderDataType::Mat3:
        {
          count += 3;
          break;
        }
        case ShaderDataType::Mat4:
        {
          count += 4;
          break;
        }
        default:
        {
          KRYS_ASSERT(false, "Unknown ShaderDataType", 0);
          break;
        }
        }
      }

      _attributeCount = count;
    }
  };

  enum class UniformDataType
  {
    None = 0,
    Scalar,
    Vec2,
    Vec3,
    Vec4,
    Array,
    Mat3,
    Mat4,
    Struct
  };

  static uint32 CalculateBaseAlignment(UniformDataType type)
  {
    const uint32 N = 4;
    return ([&]()
            {
        switch (type)
        {
            case UniformDataType::Scalar:
                return N;
            case UniformDataType::Vec2:
                return 2 * N;
            case UniformDataType::Vec3:
            case UniformDataType::Vec4:
                return 4 * N;
            case UniformDataType::Mat3:
                return 4 * N; // Each column is a vec4
            case UniformDataType::Mat4:
                return 4 * N; // Each column is a vec4
            case UniformDataType::Array:
                return 4 * N; // Each element in an array of scalars/vectors has the alignment of a vec4
            default:
              KRYS_ASSERT(false, "Unknown UniformDataType!", 0);
              return uint32(0);
        } })();
  }

  static uint32 CalculateStd140LayoutSize(UniformDataType type, uint32 count)
  {
    const uint32 N = 4;
    return ([&]()
            {
        switch (type)
        {
            case UniformDataType::Scalar:
                return N;
            case UniformDataType::Vec2:
                return 2 * N;
            case UniformDataType::Vec3:
            case UniformDataType::Vec4:
                return 4 * N;
            case UniformDataType::Mat3:
              return (4 * N * 3) * count; // Each column is a vec4
            case UniformDataType::Mat4:
              return (4 * N * 4) * count; // Each column is a vec4
            case UniformDataType::Array:
              return 4 * N * count; // Each element in an array of scalars/vectors has the alignment of a vec4
            default:
              KRYS_ASSERT(false, "Unknown UniformDataType!", 0);
              return uint32(0);
        } })();
  }

  struct UniformStructElement
  {
    UniformDataType Type;
    string Name;
    uint32 Count, BaseAlignment, LayoutSize, AlignedOffset;

    UniformStructElement(UniformDataType type, const string &name, uint32 count = 1)
        : Type(type), Name(name), Count(count)
    {
      BaseAlignment = CalculateBaseAlignment(type);
      LayoutSize = CalculateStd140LayoutSize(type, count);
    }
  };

  struct UniformStructLayout
  {
  private:
    List<UniformStructElement> _layout;

  public:
    UniformStructLayout() = default;

    UniformStructLayout(std::initializer_list<UniformStructElement> layout)
        : _layout(layout)
    {
      CalculateOffsetsAndSize();
    }

    uint32 GetSize() const noexcept { return CalculateTotalSize(); }
    const List<UniformStructElement> &GetElements() const noexcept { return _layout; }
    List<UniformStructElement>::iterator begin() { return _layout.begin(); }
    List<UniformStructElement>::iterator end() { return _layout.end(); }
    List<UniformStructElement>::const_iterator begin() const { return _layout.begin(); }
    List<UniformStructElement>::const_iterator end() const { return _layout.end(); }

    uint32 CalculateBaseAlignment() const
    {
      uint32 maxAlignment = 0;
      for (const auto &element : _layout)
      {
        if (element.BaseAlignment > maxAlignment)
          maxAlignment = element.BaseAlignment;
      }
      return maxAlignment;
    }

    uint32 CalculateTotalSize() const
    {
      uint32 totalSize = 0;
      for (const auto &element : _layout)
      {
        totalSize = AlignOffset(totalSize, element.BaseAlignment);
        totalSize += element.LayoutSize;
      }
      return AlignOffset(totalSize, 16); // Ensure the structure itself is aligned to a 16-byte boundary
    }

  private:
    void CalculateOffsetsAndSize()
    {
      uint32 alignedOffset = 0;
      for (auto &element : _layout)
      {
        element.AlignedOffset = alignedOffset = AlignOffset(alignedOffset, element.BaseAlignment);
        alignedOffset += element.LayoutSize;
      }
    }

    static uint32 AlignOffset(uint32 offset, uint32 alignment)
    {
      return (offset + alignment - 1) & ~(alignment - 1);
    }
  };

  struct UniformBufferElement
  {
    UniformDataType Type;
    string Name;
    uint32 Count;
    UniformStructLayout Layout;

    uint32 BaseAlignment, LayoutSize, AlignedOffset;

    UniformBufferElement(UniformDataType type, const string &name, uint32 count = 1)
        : Type(type), Name(name), Count(count), Layout()
    {
      BaseAlignment = CalculateBaseAlignment(Type);
      LayoutSize = CalculateStd140LayoutSize(Type, Count);
    }

    UniformBufferElement(UniformDataType type, const string &name, UniformStructLayout layout, uint32 count = 1)
        : Type(type), Name(name), Count(count), Layout(layout)
    {
      BaseAlignment = layout.CalculateBaseAlignment();
      LayoutSize = layout.CalculateTotalSize();
    }
  };

  struct UniformBufferLayout
  {
  private:
    List<UniformBufferElement> _layout;
    uint32 _size;

  public:
    UniformBufferLayout() = default;

    UniformBufferLayout(std::initializer_list<UniformBufferElement> layout)
        : _layout(layout), _size(0)
    {
      CalculateOffsetsAndSize();
    }

    uint32 GetSize() const noexcept { return _size; }
    const List<UniformBufferElement> &GetElements() const noexcept { return _layout; }
    List<UniformBufferElement>::iterator begin() { return _layout.begin(); }
    List<UniformBufferElement>::iterator end() { return _layout.end(); }
    List<UniformBufferElement>::const_iterator begin() const { return _layout.begin(); }
    List<UniformBufferElement>::const_iterator end() const { return _layout.end(); }

  private:
    void CalculateOffsetsAndSize()
    {
      KRYS_ASSERT(_layout.size(), "UniformBufferLayout has no elements", 0);

      uint32 alignedOffset = 0;
      for (auto &element : _layout)
      {
        element.AlignedOffset = alignedOffset = AlignOffset(alignedOffset, element.BaseAlignment);
        alignedOffset += element.LayoutSize * element.Count;
      }

      _size = alignedOffset;
    }

    static uint32 AlignOffset(uint32 offset, uint32 alignment)
    {
      return (offset + alignment - 1) & ~(alignment - 1);
    }
  };

  constexpr uint32 UPDATE_ATTRIBUTE_PER_VERTEX = 0;
  constexpr uint32 UPDATE_ATTRIBUTE_PER_INSTANCE = 1;

  struct InstanceArrayElement
  {
    string Name;
    ShaderDataType Type;
    uint32 AttributeUsageFrequency;
    bool Normalized;
    uint32 Size;
    uint32 Stride;
    size_t Offset;

    InstanceArrayElement() = default;
    InstanceArrayElement(ShaderDataType type, const string &name, uint32 attributeUsageFrequency = UPDATE_ATTRIBUTE_PER_VERTEX, bool normalized = false)
        : Name(name), Type(type), AttributeUsageFrequency(attributeUsageFrequency), Normalized(normalized),
          Size(GetSizeOfShaderDataType(type)), Stride(0), Offset(0)
    {
    }

    uint8 GetComponentCount() const
    {
      return GetComponentCountOfShaderDataType(Type);
    }
  };

  struct InstanceArrayBufferLayout
  {
  private:
    List<InstanceArrayElement> _elements;

  public:
    InstanceArrayBufferLayout() = default;

    InstanceArrayBufferLayout(std::initializer_list<InstanceArrayElement> elements)
        : _elements(elements)
    {
      CalculateOffsetsAndSize();
    }

    const List<InstanceArrayElement> &GetElements() const { return _elements; }
    List<InstanceArrayElement>::iterator begin() { return _elements.begin(); }
    List<InstanceArrayElement>::iterator end() { return _elements.end(); }
    List<InstanceArrayElement>::const_iterator begin() const { return _elements.begin(); }
    List<InstanceArrayElement>::const_iterator end() const { return _elements.end(); }

  private:
    void CalculateOffsetsAndSize()
    {
      KRYS_ASSERT(_elements.size(), "InstanceArrayBufferLayout has no elements", 0);

      uint32 vertexSize = 0;
      for (auto &element : _elements)
        vertexSize += element.Size;
      KRYS_ASSERT(vertexSize, "vertexSize was 0", 0);

      uint32 offset = 0;
      for (auto &element : _elements)
      {
        element.Offset = offset;
        offset += element.Size;
        element.Stride = vertexSize;
      }
    }
  };
}