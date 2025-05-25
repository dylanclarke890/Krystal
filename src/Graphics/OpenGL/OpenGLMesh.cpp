#include "Graphics/OpenGL/OpenGLMesh.hpp"
#include "Debug/Macros.hpp"
#include "Graphics/BufferWriter.hpp"
#include "Graphics/OpenGL/OpenGLGraphicsContext.hpp"

namespace Krys::Gfx::OpenGL
{
  OpenGLMesh::OpenGLMesh(MeshHandle handle, const List<vertex_t> &vertices, const List<index_t> &indices,
                         const VertexLayout &layout, Ptr<OpenGLGraphicsContext> ctx) noexcept
      : Mesh(handle, vertices, indices, layout), _ctx(ctx)
  {
    ::glCreateVertexArrays(1, &_vao);
    ::glBindVertexArray(_vao);

    {
      _vbo = _ctx->CreateVertexBuffer(static_cast<uint32>(vertices.size() * sizeof(vertex_t)));
      BufferWriter<VertexBuffer> writer(*_ctx->GetVertexBuffer(_vbo));
      writer.Write(_vertices);
    }

    if (!indices.empty())
    {
      _ebo = _ctx->CreateIndexBuffer(static_cast<uint32>(indices.size() * sizeof(index_t)));
      BufferWriter<IndexBuffer> writer(*_ctx->GetIndexBuffer(_ebo));
      writer.Write(_indices);
    }

    _ctx->SetupVertexArray(_vbo, _ebo, _layout);
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
    BufferWriter<VertexBuffer> writer(*_ctx->GetVertexBuffer(_vbo));
    writer.Write(_vertices);
  }

  void OpenGLMesh::SetIndices(const List<index_t> &indices) noexcept
  {
    _indices = indices;
    BufferWriter<IndexBuffer> writer(*_ctx->GetIndexBuffer(_ebo));
    writer.Write(_indices);
  }
}