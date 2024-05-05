#include "Renderer2D.h"

#include <gl.h> // TODO: temporary!

namespace Krys
{
  // TODO: use index buffer
  constexpr uint VERTEX_BUFFER_SIZE = sizeof(VertexData) * KRYS_MAX_VERTICES;

  Ref<GraphicsContext> Renderer2D::Context;
  Ref<Shader> Renderer2D::ColorShader;
  Ref<VertexArray> Renderer2D::VertexArray;
  Ref<VertexBuffer> Renderer2D::VertexBuffer;
  std::array<VertexData, KRYS_MAX_VERTICES> Renderer2D::Vertices;
  uint Renderer2D::VertexCount;

  void Renderer2D::Init(Ref<GraphicsContext> ctx)
  {
    Context = ctx;

    VertexArray = Context->CreateVertexArray();

    VertexBuffer = Context->CreateVertexBuffer(VERTEX_BUFFER_SIZE);
    VertexBuffer->SetLayout(
        BufferLayout(VERTEX_BUFFER_SIZE,
                     {{ShaderDataType::Float3, "position"}, {ShaderDataType::Float4, "color"}},
                     BufferLayoutType::Interleaved));

    VertexArray->AddVertexBuffer(VertexBuffer);

    ColorShader = Context->CreateShader();
    ColorShader->Bind();
    ColorShader->Load("Renderer/color-shader.vert", "Renderer/color-shader.frag");
    ColorShader->Link();

    Vertices = std::array<VertexData, KRYS_MAX_VERTICES>();
    VertexCount = 0;
  }

  void Renderer2D::Shutdown()
  {
  }

  void Renderer2D::DrawTriangle(Vec3 &posA, Vec3 &posB, Vec3 &posC, Vec4 &color)
  {
    VertexData vertices[] = {{posA, color}, {posB, color}, {posC, color}};
    AddVertices(&vertices[0], 3);
  }

  void Renderer2D::DrawQuad(Vec3 &pos, Vec2 &size, Vec4 &color)
  {
    VertexData vertices[] = {
        // Triangle 1
        {pos, color},
        {Vec3(pos.x + size.x, pos.y, pos.z), color},
        {Vec3(pos.x, pos.y + size.y, pos.z), color},
        // Triangle 2
        {Vec3(pos.x + size.x, pos.y, pos.z), color},
        {Vec3(pos.x + size.x, pos.y + size.y, pos.z), color},
        {Vec3(pos.x, pos.y + size.y, pos.z), color},
    };
    AddVertices(&vertices[0], 6);
  }

  void Renderer2D::Begin()
  {
    VertexCount = 0;
  }

  void Renderer2D::End()
  {
    if (VertexCount == 0)
      return;

    ColorShader->Bind();
    VertexBuffer->SetData((const void *)Vertices.data(), VertexCount * sizeof(VertexData));
    glDrawArrays(GL_TRIANGLES, 0, VertexCount);
  }

  void Renderer2D::AddVertices(VertexData *vertices, uint count)
  {
    if (VertexCount + count > KRYS_MAX_VERTICES)
    {
      // TODO: batch this properly
      End();
      Begin();
    }

    for (size_t i = 0; i < count; i++)
      Vertices[VertexCount++] = vertices[i];
  }
}