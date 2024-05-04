#include "Renderer2D.h"

#include <glad.h> // TODO: temporary!

namespace Krys
{
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
                     {{ShaderDataType::Float3, "position"},
                      {ShaderDataType::Float4, "color"}},
                     BufferLayoutType::Contiguous));

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
    // TODO: make sure we have enough room in the batch
    Vertices[VertexCount++] = {posA, color};
    Vertices[VertexCount++] = {posB, color};
    Vertices[VertexCount++] = {posC, color};
  }

  void Renderer2D::Begin()
  {
    VertexCount = 0;
  }

  void Renderer2D::End()
  {
    if (VertexCount == 0)
      return;

    VertexArray->Bind();
    VertexBuffer->Bind();
    ColorShader->Bind();

    Vec3 PositionA(-1.0f, -1.0f, 0.0f);
    Vec3 PositionB(1.0f, -1.0f, 0.0f);
    Vec3 PositionC(0.0f, 1.0f, 0.0f);
    Vec4 TriangleColor(1.0f);
    VertexData vertices[] = {{PositionA, TriangleColor},
                             {PositionB, TriangleColor},
                             {PositionC, TriangleColor}};

    VertexBuffer->SetData((const void *)vertices, VertexCount * sizeof(VertexData));
    glDrawArrays(GL_TRIANGLES, 0, VertexCount);
  }
}