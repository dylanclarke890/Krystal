#include "Graphics/Mesh.hpp"

namespace Krys::Gfx
{
  Mesh::Mesh(const List<vertex_t> &vertices, const List<index_t> &indices,
             const VertexLayout &layout) noexcept
      : _vertices(vertices), _indices(indices), _layout(layout),
        _count(indices.empty() ? vertices.size() : indices.size())
  {
  }

  const List<Mesh::vertex_t> &Mesh::GetVertices() const noexcept
  {
    return _vertices;
  }

  const List<Mesh::index_t> &Mesh::GetIndices() const noexcept
  {
    return _indices;
  }

  const VertexLayout &Mesh::GetLayout() const noexcept
  {
    return _layout;
  }

  VertexBufferHandle Mesh::GetVertexBuffer() const noexcept
  {
    return _vbo;
  }

  IndexBufferHandle Mesh::GetIndexBuffer() const noexcept
  {
    return _ebo;
  }

  size_t Mesh::GetCount() const noexcept
  {
    return _count;
  }

  bool Mesh::IsIndexed() const noexcept
  {
    return !_indices.empty() && _ebo.IsValid();
  }
}