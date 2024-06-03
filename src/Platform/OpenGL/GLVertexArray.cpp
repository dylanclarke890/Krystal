#include "GLVertexArray.h"
#include "Graphics/Buffer.h"

namespace Krys
{
  // TODO: we should make sure we don't add too many attributes to vertex/instance array buffers
  // int nrAttributes;
  // glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);

  static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
  {
    switch (type)
    {
    case ShaderDataType::Float:
    case ShaderDataType::Float2:
    case ShaderDataType::Float3:
    case ShaderDataType::Float4:
    case ShaderDataType::Mat3:
    case ShaderDataType::Mat4:
      return GL_FLOAT;
    case ShaderDataType::Int:
    case ShaderDataType::Int2:
    case ShaderDataType::Int3:
    case ShaderDataType::Int4:
      return GL_INT;
    case ShaderDataType::Bool:
      return GL_BOOL;
    default:
    {
      KRYS_ASSERT(false, "Unknown ShaderDataType!", 0);
      return 0;
    }
    }
  }

  GLVertexArray::GLVertexArray()
  {
    glCreateVertexArrays(1, &Id);
  }

  GLVertexArray::~GLVertexArray()
  {
    glDeleteVertexArrays(1, &Id);
  }

  void GLVertexArray::Bind() const
  {
    glBindVertexArray(Id);
  }

  void GLVertexArray::Unbind() const
  {
    glBindVertexArray(0);
  }

  void GLVertexArray::AddVertexBuffer(Ref<VertexBuffer> buffer)
  {
    KRYS_ASSERT(buffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!", 0);

    glBindVertexArray(Id);
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
        glEnableVertexAttribArray(AttributeIndex);
        glVertexAttribPointer(AttributeIndex,
                              element.GetComponentCount(),
                              ShaderDataTypeToOpenGLBaseType(element.Type),
                              element.Normalized ? GL_TRUE : GL_FALSE,
                              element.Stride,
                              (const void *)element.Offset);
        AttributeIndex++;
        break;
      }
      case ShaderDataType::Int:
      case ShaderDataType::Int2:
      case ShaderDataType::Int3:
      case ShaderDataType::Int4:
      case ShaderDataType::Bool:
      {
        glEnableVertexAttribArray(AttributeIndex);
        glVertexAttribIPointer(AttributeIndex,
                               element.GetComponentCount(),
                               ShaderDataTypeToOpenGLBaseType(element.Type),
                               element.Stride,
                               (const void *)element.Offset);
        AttributeIndex++;
        break;
      }
      case ShaderDataType::Mat3:
      case ShaderDataType::Mat4:
      {
        uint8 count = element.GetComponentCount();
        for (uint8 i = 0; i < count; i++)
        {
          glEnableVertexAttribArray(AttributeIndex);
          glVertexAttribPointer(AttributeIndex,
                                count,
                                ShaderDataTypeToOpenGLBaseType(element.Type),
                                element.Normalized ? GL_TRUE : GL_FALSE,
                                element.Stride,
                                (const void *)(element.Offset + sizeof(float) * count * i));
          glVertexAttribDivisor(AttributeIndex, 1);
          AttributeIndex++;
        }
        break;
      }
      default:
        KRYS_ASSERT(false, "Unknown ShaderDataType!", 0);
      }
    }

    VertexBuffers.push_back(buffer);
  }

  void GLVertexArray::AddInstanceArrayBuffer(Ref<InstanceArrayBuffer> buffer)
  {
    KRYS_ASSERT(buffer->GetLayout().GetElements().size(), "Instance Array Buffer has no layout!", 0);

    glBindVertexArray(Id);
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
        glEnableVertexAttribArray(AttributeIndex);
        glVertexAttribPointer(AttributeIndex,
                              element.GetComponentCount(),
                              ShaderDataTypeToOpenGLBaseType(element.Type),
                              element.Normalized ? GL_TRUE : GL_FALSE,
                              element.Stride,
                              (const void *)element.Offset);
        glVertexAttribDivisor(AttributeIndex, element.AttributeUsageFrequency);
        AttributeIndex++;
        break;
      }
      case ShaderDataType::Int:
      case ShaderDataType::Int2:
      case ShaderDataType::Int3:
      case ShaderDataType::Int4:
      case ShaderDataType::Bool:
      {
        glEnableVertexAttribArray(AttributeIndex);
        glVertexAttribIPointer(AttributeIndex,
                               element.GetComponentCount(),
                               ShaderDataTypeToOpenGLBaseType(element.Type),
                               element.Stride,
                               (const void *)element.Offset);
        glVertexAttribDivisor(AttributeIndex, element.AttributeUsageFrequency);
        AttributeIndex++;
        break;
      }
      case ShaderDataType::Mat3:
      case ShaderDataType::Mat4:
      {
        uint8 count = element.GetComponentCount();
        for (uint8 i = 0; i < count; i++)
        {
          glEnableVertexAttribArray(AttributeIndex);
          glVertexAttribPointer(AttributeIndex,
                                count,
                                ShaderDataTypeToOpenGLBaseType(element.Type),
                                element.Normalized ? GL_TRUE : GL_FALSE,
                                element.Stride,
                                (const void *)(element.Offset + sizeof(float) * count * i));
          glVertexAttribDivisor(AttributeIndex, 1);
          AttributeIndex++;
        }
        break;
      }
      default:
        KRYS_ASSERT(false, "Unknown ShaderDataType!", 0);
      }
    }

    InstanceArrayBuffers.push_back(buffer);
  }

  void GLVertexArray::SetIndexBuffer(Ref<IndexBuffer> buffer)
  {
    glBindVertexArray(Id);
    ZBuffer = buffer;
    ZBuffer->Bind();
  }

  const std::vector<Ref<VertexBuffer>> &GLVertexArray::GetVertexBuffers() const
  {
    return VertexBuffers;
  }

  const std::vector<Ref<InstanceArrayBuffer>> &GLVertexArray::GetInstanceArrayBuffers() const
  {
    return InstanceArrayBuffers;
  }

  const Ref<IndexBuffer> GLVertexArray::GetIndexBuffer()
  {
    return ZBuffer;
  }
}