#include "krys-pch.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Krys
{
  static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
  {
    switch (type)
    {
      case Krys::ShaderDataType::Float:
      case Krys::ShaderDataType::Float2:
      case Krys::ShaderDataType::Float3:
      case Krys::ShaderDataType::Float4:
      case Krys::ShaderDataType::Mat3:
      case Krys::ShaderDataType::Mat4:
        return GL_FLOAT;
      case Krys::ShaderDataType::Int:
      case Krys::ShaderDataType::Int2:
      case Krys::ShaderDataType::Int3:
      case Krys::ShaderDataType::Int4:
        return GL_INT;
      case Krys::ShaderDataType::Bool:
        return GL_BOOL;
    }

    KRYS_CORE_ASSERT(false, "Unknown ShaderDataType!");
    return 0;
  }

  OpenGLVertexArray::OpenGLVertexArray() : m_RendererId(0), m_VertexBufferIndex(0)
  {
    glCreateVertexArrays(1, &m_RendererId);
  }

  OpenGLVertexArray::~OpenGLVertexArray()
  {
    glDeleteVertexArrays(1, &m_RendererId);
  }

  void OpenGLVertexArray::Bind() const
  {
    glBindVertexArray(m_RendererId);
  }

  void OpenGLVertexArray::Unbind() const
  {
    glBindVertexArray(0);
  }

  void OpenGLVertexArray::AddVertexBuffer(Ref<VertexBuffer> buffer)
  {
    const auto& layout = buffer->GetLayout();
    KRYS_CORE_ASSERT(layout.GetElements().size(), "Vertex Buffer has no layout!");

    glBindVertexArray(m_RendererId);
    buffer->Bind();

    for (const auto& element : layout)
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
    }

    m_VertexBuffers.push_back(buffer);
  }

  void OpenGLVertexArray::SetIndexBuffer(Ref<IndexBuffer> buffer)
  {
    glBindVertexArray(m_RendererId);
    buffer->Bind();

    m_IndexBuffer = buffer;
  }
}