#include "GLVertexArray.h"
#include "Graphics/Buffer.h"

namespace Krys
{
  static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
  {
    switch (type)
    {
    case ShaderDataType::Float:
      return GL_FLOAT;
    case ShaderDataType::Float2:
      return GL_FLOAT;
    case ShaderDataType::Float3:
      return GL_FLOAT;
    case ShaderDataType::Float4:
      return GL_FLOAT;
    case ShaderDataType::Mat3:
      return GL_FLOAT;
    case ShaderDataType::Mat4:
      return GL_FLOAT;
    case ShaderDataType::Int:
      return GL_INT;
    case ShaderDataType::Int2:
      return GL_INT;
    case ShaderDataType::Int3:
      return GL_INT;
    case ShaderDataType::Int4:
      return GL_INT;
    case ShaderDataType::Bool:
      return GL_BOOL;
    }

    KRYS_ASSERT(false, "Unknown ShaderDataType!");
    return 0;
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
    KRYS_ASSERT(buffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

    glBindVertexArray(Id);
    buffer->Bind();

    const auto &layout = buffer->GetLayout();
    for (const auto &element : layout)
    {
      // TODO: we should make sure we don't add too many attributes.
      // int nrAttributes;
      // glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
      switch (element.Type)
      {
      case ShaderDataType::Float:
      case ShaderDataType::Float2:
      case ShaderDataType::Float3:
      case ShaderDataType::Float4:
      {
        glEnableVertexAttribArray(VertexBufferIndex);
        glVertexAttribPointer(VertexBufferIndex,
                              element.GetComponentCount(),
                              ShaderDataTypeToOpenGLBaseType(element.Type),
                              element.Normalized ? GL_TRUE : GL_FALSE,
                              element.Stride,
                              (const void *)element.Offset);
        VertexBufferIndex++;
        break;
      }
      case ShaderDataType::Int:
      case ShaderDataType::Int2:
      case ShaderDataType::Int3:
      case ShaderDataType::Int4:
      case ShaderDataType::Bool:
      {
        glEnableVertexAttribArray(VertexBufferIndex);
        glVertexAttribIPointer(VertexBufferIndex,
                               element.GetComponentCount(),
                               ShaderDataTypeToOpenGLBaseType(element.Type),
                               element.Stride,
                               (const void *)element.Offset);
        VertexBufferIndex++;
        break;
      }
      case ShaderDataType::Mat3:
      case ShaderDataType::Mat4:
      {
        uint8 count = element.GetComponentCount();
        for (uint8 i = 0; i < count; i++)
        {
          glEnableVertexAttribArray(VertexBufferIndex);
          glVertexAttribPointer(VertexBufferIndex,
                                count,
                                ShaderDataTypeToOpenGLBaseType(element.Type),
                                element.Normalized ? GL_TRUE : GL_FALSE,
                                element.Stride,
                                (const void *)(element.Offset + sizeof(float) * count * i));
          glVertexAttribDivisor(VertexBufferIndex, 1);
          VertexBufferIndex++;
        }
        break;
      }
      default:
        KRYS_ASSERT(false, "Unknown ShaderDataType!");
      }
    }

    VertexBuffers.push_back(buffer);
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

  const Ref<IndexBuffer> GLVertexArray::GetIndexBuffer()
  {
    return ZBuffer;
  }
}