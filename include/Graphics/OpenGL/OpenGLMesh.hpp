#pragma once

#include "Base/Pointers.hpp"
#include "Base/Types.hpp"
#include "Graphics/Handles.hpp"
#include "Graphics/Mesh.hpp"
#include "Graphics/VertexLayout.hpp"

#include <glad/gl.h>

namespace Krys::Gfx::OpenGL
{
  class OpenGLGraphicsContext;

  class OpenGLMesh : public Mesh
  {
  public:
    using vertex_t = Mesh::vertex_t;
    using index_t = Mesh::index_t;

    OpenGLMesh(const List<vertex_t> &vertices, const List<index_t> &indices, const VertexLayout &layout,
               Ptr<OpenGLGraphicsContext> ctx) noexcept;

    ~OpenGLMesh() noexcept override;

    void Bind() noexcept override;
    void Unbind() noexcept override;

    void SetVertices(const List<vertex_t> &vertices) noexcept override;
    void SetIndices(const List<index_t> &indices) noexcept override;

  private:
    void SetupVAO() noexcept;

    GLuint _vao;
    Ptr<OpenGLGraphicsContext> _ctx;
  };
}