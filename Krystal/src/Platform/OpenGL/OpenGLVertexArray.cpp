#include "krys-pch.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Krys
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
      case ShaderDataType::Mat4:
        return GL_FLOAT;
      case ShaderDataType::Int:
      case ShaderDataType::Int2:
      case ShaderDataType::Int3:
      case ShaderDataType::Int4:
        return GL_INT;
      case ShaderDataType::Bool:
        return GL_BOOL;
    }

    KRYS_CORE_ASSERT(false, "Unknown ShaderDataType!");
    return 0;
  }

  OpenGLVertexArray::OpenGLVertexArray() : m_RendererId(0), m_VertexBufferIndex(0)
  {
    KRYS_PROFILE_FUNCTION();

    glCreateVertexArrays(1, &m_RendererId);
  }

  OpenGLVertexArray::~OpenGLVertexArray()
  {
    KRYS_PROFILE_FUNCTION();
    
    glDeleteVertexArrays(1, &m_RendererId);
  }

  void OpenGLVertexArray::Bind() const
  {
    KRYS_PROFILE_FUNCTION();
    
    glBindVertexArray(m_RendererId);
  }

  void OpenGLVertexArray::Unbind() const
  {
    KRYS_PROFILE_FUNCTION();
    
    glBindVertexArray(0);
  }

  void OpenGLVertexArray::AddVertexBuffer(Ref<VertexBuffer> buffer)
  {
    KRYS_PROFILE_FUNCTION();
    
    const auto& layout = buffer->GetLayout();
    KRYS_CORE_ASSERT(layout.GetElements().size(), "Vertex Buffer has no layout!");

    glBindVertexArray(m_RendererId);
    buffer->Bind();

    for (const auto& element : layout)
    {
      switch (element.Type)
      {
        case ShaderDataType::Bool:
        case ShaderDataType::Int:
        case ShaderDataType::Int2:
        case ShaderDataType::Int3:
        case ShaderDataType::Int4:
        case ShaderDataType::Float:
        case ShaderDataType::Float2:
        case ShaderDataType::Float3:
        case ShaderDataType::Float4:
        {
          glEnableVertexAttribArray(m_VertexBufferIndex);
          glVertexAttribPointer(
            m_VertexBufferIndex, 
            element.GetComponentCount(),
            ShaderDataTypeToOpenGLBaseType(element.Type), 
            element.Normalized ? GL_TRUE : GL_FALSE,
            layout.GetStride(), 
            (const void*)(intptr_t)element.Offset
          );
          m_VertexBufferIndex++;
          break;
        }
        case ShaderDataType::Mat3:
        case ShaderDataType::Mat4:
        {
          uint8_t count = element.GetComponentCount();
          for (uint8_t i = 0; i < count; i++)
          {
            glEnableVertexAttribArray(m_VertexBufferIndex);
            glVertexAttribPointer(
              m_VertexBufferIndex,
              count,
              ShaderDataTypeToOpenGLBaseType(element.Type),
              element.Normalized ? GL_TRUE : GL_FALSE,
              layout.GetStride(),
              (const void*)(sizeof(float) * count * i)
            );
            glVertexAttribDivisor(m_VertexBufferIndex, 1);
            m_VertexBufferIndex++;
          }
          break;
        }
        default:
          KRYS_CORE_ASSERT(false, "Unknown ShaderDataType!");
      }
    }

    m_VertexBuffers.push_back(buffer);
  }

  void OpenGLVertexArray::SetIndexBuffer(Ref<IndexBuffer> buffer)
  {
    KRYS_PROFILE_FUNCTION();
    
    glBindVertexArray(m_RendererId);
    buffer->Bind();

    m_IndexBuffer = buffer;
  }
}