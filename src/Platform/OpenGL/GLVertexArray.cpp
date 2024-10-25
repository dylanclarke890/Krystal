#include "OpenGL/GLVertexArray.h"
#include "Graphics/Buffer.h"

namespace Krys::OpenGL
{
  static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
  {
    switch (type)
    {
      case ShaderDataType::Float:
      case ShaderDataType::Float2:
      case ShaderDataType::Float3:
      case ShaderDataType::Float4:
      case ShaderDataType::Mat3:
      case ShaderDataType::Mat4:   return GL_FLOAT;
      case ShaderDataType::Int:
      case ShaderDataType::Int2:
      case ShaderDataType::Int3:
      case ShaderDataType::Int4:   return GL_INT;
      case ShaderDataType::Bool:   return GL_BOOL;
      default:
      {
        KRYS_ASSERT(false, "Unknown ShaderDataType!", 0);
        return 0;
      }
    }
  }

  GLVertexArray::GLVertexArray()
  {
    glCreateVertexArrays(1, &_id);
  }

  GLVertexArray::~GLVertexArray()
  {
    glDeleteVertexArrays(1, &_id);
  }

  void GLVertexArray::Bind() const
  {
    glBindVertexArray(_id);
  }

  void GLVertexArray::Unbind() const
  {
    glBindVertexArray(0);
  }

  void GLVertexArray::AddVertexBuffer(Ref<VertexBuffer> buffer)
  {
    KRYS_ASSERT(buffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!", 0);

    glBindVertexArray(_id);
    buffer->Bind();

    const auto &layout = buffer->GetLayout();
    for (const auto &element : layout)
    {
      switch (element.Type)
      {
        case ShaderDataType::Float:
        case ShaderDataType::Float2:
        case ShaderDataType::Float3:
        case ShaderDataType::Float4:
        {
          glEnableVertexAttribArray(_attributeIndex);
          glVertexAttribPointer(_attributeIndex, element.GetComponentCount(),
                                ShaderDataTypeToOpenGLBaseType(element.Type), element.Normalized ? GL_TRUE : GL_FALSE,
                                element.Stride, (const void *)element.Offset);
          _attributeIndex++;
          break;
        }
        case ShaderDataType::Int:
        case ShaderDataType::Int2:
        case ShaderDataType::Int3:
        case ShaderDataType::Int4:
        case ShaderDataType::Bool:
        {
          glEnableVertexAttribArray(_attributeIndex);
          glVertexAttribIPointer(_attributeIndex, element.GetComponentCount(),
                                 ShaderDataTypeToOpenGLBaseType(element.Type), element.Stride,
                                 (const void *)element.Offset);
          _attributeIndex++;
          break;
        }
        case ShaderDataType::Mat3:
        case ShaderDataType::Mat4:
        {
          uint8 count = element.GetComponentCount();
          for (uint8 i = 0; i < count; i++)
          {
            glEnableVertexAttribArray(_attributeIndex);
            glVertexAttribPointer(_attributeIndex, count, ShaderDataTypeToOpenGLBaseType(element.Type),
                                  element.Normalized ? GL_TRUE : GL_FALSE, element.Stride,
                                  (const void *)(element.Offset + sizeof(float) * count * i));
            glVertexAttribDivisor(_attributeIndex, 1);
            _attributeIndex++;
          }
          break;
        }
        default: KRYS_ASSERT(false, "Unknown ShaderDataType!", 0);
      }
    }

    _vertexBuffers.push_back(buffer);
  }

  void GLVertexArray::AddInstanceArrayBuffer(Ref<InstanceArrayBuffer> buffer)
  {
    KRYS_ASSERT(buffer->GetLayout().GetElements().size(), "Instance Array Buffer has no layout!", 0);

    glBindVertexArray(_id);
    buffer->Bind();

    const auto &layout = buffer->GetLayout();
    for (const auto &element : layout)
    {
      switch (element.Type)
      {
        case ShaderDataType::Float:
        case ShaderDataType::Float2:
        case ShaderDataType::Float3:
        case ShaderDataType::Float4:
        {
          glEnableVertexAttribArray(_attributeIndex);
          glVertexAttribPointer(_attributeIndex, element.GetComponentCount(),
                                ShaderDataTypeToOpenGLBaseType(element.Type), element.Normalized ? GL_TRUE : GL_FALSE,
                                element.Stride, (const void *)element.Offset);
          glVertexAttribDivisor(_attributeIndex, element.AttributeUsageFrequency);
          _attributeIndex++;
          break;
        }
        case ShaderDataType::Int:
        case ShaderDataType::Int2:
        case ShaderDataType::Int3:
        case ShaderDataType::Int4:
        case ShaderDataType::Bool:
        {
          glEnableVertexAttribArray(_attributeIndex);
          glVertexAttribIPointer(_attributeIndex, element.GetComponentCount(),
                                 ShaderDataTypeToOpenGLBaseType(element.Type), element.Stride,
                                 (const void *)element.Offset);
          glVertexAttribDivisor(_attributeIndex, element.AttributeUsageFrequency);
          _attributeIndex++;
          break;
        }
        case ShaderDataType::Mat3:
        case ShaderDataType::Mat4:
        {
          uint8 count = element.GetComponentCount();
          for (uint8 i = 0; i < count; i++)
          {
            glEnableVertexAttribArray(_attributeIndex);
            glVertexAttribPointer(_attributeIndex, count, ShaderDataTypeToOpenGLBaseType(element.Type),
                                  element.Normalized ? GL_TRUE : GL_FALSE, element.Stride,
                                  (const void *)(element.Offset + sizeof(float) * count * i));
            glVertexAttribDivisor(_attributeIndex, 1);
            _attributeIndex++;
          }
          break;
        }
        default: KRYS_ASSERT(false, "Unknown ShaderDataType!", 0);
      }
    }

    _instanceArrayBuffers.push_back(buffer);
  }

  void GLVertexArray::SetIndexBuffer(Ref<IndexBuffer> buffer)
  {
    glBindVertexArray(_id);
    _indexBuffer = buffer;
    _indexBuffer->Bind();
  }

  const List<Ref<VertexBuffer>> &GLVertexArray::GetVertexBuffers() const
  {
    return _vertexBuffers;
  }

  const List<Ref<InstanceArrayBuffer>> &GLVertexArray::GetInstanceArrayBuffers() const
  {
    return _instanceArrayBuffers;
  }

  const Ref<IndexBuffer> GLVertexArray::GetIndexBuffer()
  {
    return _indexBuffer;
  }
}