#pragma once

#include "Krystal.h"

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

  static uint32 ShaderDataTypeSize(ShaderDataType type)
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
    }

    KRYS_ASSERT(false, "Unknown ShaderDataType!");
    return 0;
  }

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
        : Name(name), Type(type), Size(ShaderDataTypeSize(type)), Normalized(normalized)
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
      }

      KRYS_ASSERT(false, "Unknown ShaderDataType!");
      return 0;
    }
  };

  // TODO: extend layout class to support contiguous memory layouts.
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
      KRYS_ASSERT(vertexSize != 0, "Invalid element size!");

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
        KRYS_ASSERT(false, "Unrecognised BufferLayoutType!");
        break;
      }
    }
  };
}