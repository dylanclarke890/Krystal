#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"
#include "Graphics/Buffer.hpp"
#include "Graphics/VertexLayout.hpp"

namespace Krys::Gfx
{
  class Mesh
  {
  public:
    using vertex_t = VertexData;
    using index_t = uint32;

    virtual ~Mesh() noexcept = default;

    virtual void Bind() noexcept = 0;
    virtual void Unbind() noexcept = 0;

    NO_DISCARD MeshHandle GetHandle() const noexcept;
    NO_DISCARD const List<vertex_t> &GetVertices() const noexcept;
    NO_DISCARD const List<index_t> &GetIndices() const noexcept;
    NO_DISCARD const VertexLayout &GetLayout() const noexcept;
    NO_DISCARD VertexBufferHandle GetVertexBuffer() const noexcept;
    NO_DISCARD IndexBufferHandle GetIndexBuffer() const noexcept;
    NO_DISCARD size_t GetCount() const noexcept;
    NO_DISCARD bool IsIndexed() const noexcept;

    virtual void SetVertices(const List<vertex_t> &vertices) noexcept = 0;
    virtual void SetIndices(const List<index_t> &indices) noexcept = 0;

  protected:
    Mesh(MeshHandle handle, const List<vertex_t> &vertices, const List<index_t> &indices, const VertexLayout &layout) noexcept;

    MeshHandle _handle;
    List<vertex_t> _vertices;
    List<index_t> _indices;
    VertexLayout _layout;
    VertexBufferHandle _vbo;
    IndexBufferHandle _ebo;
    size_t _count;
  };
}