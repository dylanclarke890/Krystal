#pragma once

#include "Core.h"

#include <initializer_list>
#include <vector>

namespace Krys
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

  struct BufferElement
  {
    const char *Name;
    ShaderDataType Type;
    uint32 Size;
    uint32 Stride;
    size_t Offset;
    bool Normalized;

    BufferElement() = default;

    BufferElement(ShaderDataType type, const char *name, bool normalized = false)
        : Name(name), Type(type), Size(GetSizeOfShaderDataType(type)), Normalized(normalized), Stride(0), Offset(0)
    {
    }

    uint8 GetComponentCount() const
    {
      switch (Type)
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

  private:
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
  };

  enum class BufferLayoutType
  {
    // Attributes are interleaved in memory (i.e. [pos, color], [pos, color]).
    Interleaved = 0,
    // Attributes are contiguous in memory (i.e. [pos, pos], [color, color]).
    Contiguous = 1
  };

  class BufferLayout
  {
  private:
    std::vector<BufferElement> m_Elements;
    uint32 m_BufferSize;
    BufferLayoutType m_LayoutType;

  public:
    BufferLayout() = default;

    BufferLayout(
        uint32 bufferSize,
        std::initializer_list<BufferElement> elements,
        BufferLayoutType layoutType = BufferLayoutType::Interleaved)
        : m_Elements(elements), m_BufferSize(bufferSize), m_LayoutType(layoutType)
    {
      CalculateOffsetsAndStride();
    }

    const std::vector<BufferElement> &GetElements() const { return m_Elements; }
    std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
    std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
    std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
    std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

  private:
    void CalculateOffsetsAndStride()
    {
      uint32 vertexSize = 0;
      for (auto &element : m_Elements)
        vertexSize += element.Size;
      KRYS_ASSERT(vertexSize != 0, "Invalid element size!", 0);

      switch (m_LayoutType)
      {
      case BufferLayoutType::Interleaved:
      {
        uint32 offset = 0;
        for (auto &element : m_Elements)
        {
          element.Offset = offset;
          offset += element.Size;
          element.Stride = vertexSize;
        }
        break;
      }
      // TODO: this doesn't work when we don't fill up all of the buffer.
      case BufferLayoutType::Contiguous:
      {
        uint32 offset = 0;
        uint32 numElements = m_BufferSize / vertexSize;
        for (auto &element : m_Elements)
        {
          element.Offset = offset;
          offset += element.Size * numElements;
          element.Stride = element.Size;
        }
        break;
      }
      default:
        KRYS_ASSERT(false, "Unrecognised BufferLayoutType!", 0);
        break;
      }
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
  };

  struct UniformBufferElement
  {
    std::string Name;
    UniformDataType Type;
    // Only used by array types
    uint32 Count;
    uint32 BaseAlignment;
    uint32 AlignedOffset;
    uint32 LayoutSize;

    UniformBufferElement(UniformDataType type, const std::string &name, uint32 count = 1)
        : Name(name), Type(type), Count(count), BaseAlignment(0), AlignedOffset(0), LayoutSize(0) {}
  };

  struct UniformBufferLayout
  {
  private:
    std::vector<UniformBufferElement> Elements;

  public:
    UniformBufferLayout() = default;

    UniformBufferLayout(std::initializer_list<UniformBufferElement> elements)
        : Elements(elements)
    {
      CalculateOffsetsAndSize();
    }

    const std::vector<UniformBufferElement> &GetElements() const { return Elements; }
    std::vector<UniformBufferElement>::iterator begin() { return Elements.begin(); }
    std::vector<UniformBufferElement>::iterator end() { return Elements.end(); }
    std::vector<UniformBufferElement>::const_iterator begin() const { return Elements.begin(); }
    std::vector<UniformBufferElement>::const_iterator end() const { return Elements.end(); }

  private:
    void CalculateOffsetsAndSize()
    {
      KRYS_ASSERT(Elements.size(), "UniformBufferLayout has no elements", 0);

      uint32 alignedOffset = 0;
      for (auto &element : Elements)
      {
        element.BaseAlignment = BaseAlignmentOf(element.Type, element.Count);
        alignedOffset = AlignOffset(alignedOffset, element.BaseAlignment);
        element.AlignedOffset = alignedOffset;
        element.LayoutSize += Std140LayoutSizeOf(element.Type, element.Count);
        alignedOffset += element.LayoutSize;
      }
    }

    static uint32 BaseAlignmentOf(UniformDataType type, uint32 count)
    {
      const uint32 N = 4;
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
      }
    }

    static uint32 Std140LayoutSizeOf(UniformDataType type, uint32 count)
    {
      const uint32 N = 4;
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
        return 4 * N * 3; // 3 columns, each column is a vec4
      case UniformDataType::Mat4:
        return 4 * N * 4; // 4 columns, each column is a vec4
      case UniformDataType::Array:
        return 4 * N * count; // Each element in an array has the size of a vec4
      default:
        KRYS_ASSERT(false, "Unknown UniformDataType!", 0);
        return uint32(0);
      }
    }

    static uint32 AlignOffset(uint32 offset, uint32 alignment)
    {
      return (offset + alignment - 1) & ~(alignment - 1);
    }
  };
}