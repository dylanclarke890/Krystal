#include "Graphics/Mesh.hpp"

namespace Krys::Gfx
{
  Mesh::Mesh(MeshHandle handle, const List<vertex_t> &vertices, const List<index_t> &indices,
             const VertexLayout &layout) noexcept
      : _handle(handle), _vertices(vertices), _indices(indices), _layout(layout),
        _count(indices.empty() ? vertices.size() : indices.size())
  {
  }

  MeshHandle Mesh::GetHandle() const noexcept
  {
    return _handle;
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

  PrimitiveType Mesh::GetPrimitiveType() const noexcept
  {
    return _primitiveType;
  }

  void Mesh::SetPrimitiveType(PrimitiveType type) noexcept
  {
    _primitiveType = type;
  }
}