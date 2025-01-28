#include "Graphics/OpenGL/OpenGLMesh.hpp"
#include "Core/Debug/Macros.hpp"
#include "Graphics/BufferWriter.hpp"
#include "Graphics/OpenGL/OpenGLGraphicsContext.hpp"

namespace Krys::Gfx::OpenGL
{
  struct OpenGLAttributeInfo
  {
    GLenum Type;
    bool IsFloat;
  };

  static OpenGLAttributeInfo GetOpenGLAttributeInfo(VertexAttributeType attrType) noexcept
  {
    switch (attrType)
    {
      case VertexAttributeType::FLOAT_1:  return {GL_FLOAT, true};
      case VertexAttributeType::FLOAT_2:  return {GL_FLOAT, true};
      case VertexAttributeType::FLOAT_3:  return {GL_FLOAT, true};
      case VertexAttributeType::FLOAT_4:  return {GL_FLOAT, true};
      case VertexAttributeType::UINT32_1: return {GL_UNSIGNED_INT, false};
      case VertexAttributeType::UINT32_2: return {GL_UNSIGNED_INT, false};
      case VertexAttributeType::UINT32_3: return {GL_UNSIGNED_INT, false};
      case VertexAttributeType::UINT32_4: return {GL_UNSIGNED_INT, false};
      default:
        KRYS_ASSERT(false, "Unrecognised VertexAttributeType: {0}", static_cast<uint8>(attrType));
        return {0, false};
    }
  }

  OpenGLMesh::OpenGLMesh(MeshHandle handle, const List<vertex_t> &vertices, const List<index_t> &indices,
                         const VertexLayout &layout, Ptr<OpenGLGraphicsContext> ctx) noexcept
      : Mesh(handle, vertices, indices, layout), _ctx(ctx)
  {
    ::glCreateVertexArrays(1, &_vao);
    ::glBindVertexArray(_vao);

    {
      _vbo = _ctx->CreateVertexBuffer(static_cast<uint32>(vertices.size() * sizeof(vertex_t)));
      BufferWriter<VertexBuffer> writer(_ctx->GetVertexBuffer(_vbo));
      writer.Write(_vertices);
    }

    if (!indices.empty())
    {
      _ebo = _ctx->CreateIndexBuffer(static_cast<uint32>(indices.size() * sizeof(index_t)));
      BufferWriter<IndexBuffer> writer(_ctx->GetIndexBuffer(_ebo));
      writer.Write(_indices);
    }

    SetupVAO();
  }

  OpenGLMesh::~OpenGLMesh() noexcept
  {
    _ctx->DestroyVertexBuffer(_vbo);
    _ctx->DestroyIndexBuffer(_ebo);

    ::glDeleteVertexArrays(1, &_vao);
  }

  void OpenGLMesh::Bind() noexcept
  {
    ::glBindVertexArray(_vao);
  }

  void OpenGLMesh::Unbind() noexcept
  {
    ::glBindVertexArray(0);
  }

  void OpenGLMesh::SetVertices(const List<vertex_t> &vertices) noexcept
  {
    _vertices = vertices;
    BufferWriter<VertexBuffer> writer(_ctx->GetVertexBuffer(_vbo));
    writer.Write(_vertices);
  }

  void OpenGLMesh::SetIndices(const List<index_t> &indices) noexcept
  {
    _indices = indices;
    BufferWriter<IndexBuffer> writer(_ctx->GetIndexBuffer(_ebo));
    writer.Write(_indices);
  }

  void OpenGLMesh::SetupVAO() noexcept
  {
    KRYS_ASSERT(_vbo.IsValid(), "Invalid vertex buffer handle");
    _ctx->GetVertexBuffer(_vbo).Bind();

    if (_ebo.IsValid())
      _ctx->GetIndexBuffer(_ebo).Bind();

    auto index = 0u;
    for (auto &attr : _layout)
    {
      ::glEnableVertexAttribArray(index);

      auto [type, components, offset, size] = attr;
      auto [openGLType, isFloat] = GetOpenGLAttributeInfo(type);

      if (isFloat)
      {
        ::glVertexAttribPointer(index, components, openGLType, GL_FALSE,
                                static_cast<GLsizei>(_layout.GetStride()),
                                reinterpret_cast<void *>(static_cast<uintptr_t>(offset)));
      }
      else
      {
        ::glVertexAttribIPointer(index, components, openGLType, static_cast<GLsizei>(_layout.GetStride()),
                                 reinterpret_cast<void *>(static_cast<uintptr_t>(offset)));
      }

      index++;
    }
  }
}