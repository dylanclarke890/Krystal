#include "Graphics/Renderer2D.h"

#include <gl.h>

namespace Krys
{
  constexpr uint VERTEX_BUFFER_SIZE = sizeof(VertexData) * KRYS_MAX_VERTICES;
  constexpr Vec4 DEFAULT_COLOR = {1.0f, 1.0f, 1.0f, 1.0f};
  constexpr Vec2 QUAD_DEFAULT_TEXTURE_COORDS[] = {{0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}};
  constexpr Vec2 TRIANGLE_DEFAULT_TEXTURE_COORDS[] = {{0.0f, 0.0f}, {0.5f, 1.0f}, {1.0f, 0.0f}};
#define QUAD_INDICES(vertexCount)                                                                    \
  {                                                                                                  \
    vertexCount, vertexCount + 1, vertexCount + 2, vertexCount + 1, vertexCount + 3, vertexCount + 2 \
  }

#define TRIANGLE_INDICES(vertexCount)             \
  {                                               \
    vertexCount, vertexCount + 1, vertexCount + 2 \
  }

  Ref<GraphicsContext>
      Renderer2D::Context;
  Ref<Shader> Renderer2D::Shader;

  Ref<VertexArray> Renderer2D::VertexArray;
  Ref<VertexBuffer> Renderer2D::VertexBuffer;
  Ref<IndexBuffer> Renderer2D::IndexBuffer;

  Unique<std::array<VertexData, KRYS_MAX_VERTICES>> Renderer2D::Vertices;
  uint Renderer2D::VertexCount;
  Unique<std::array<uint32, KRYS_MAX_INDICES>> Renderer2D::Indices;
  uint Renderer2D::IndexCount;

  void Renderer2D::Init(Ref<GraphicsContext> ctx)
  {
    Context = ctx;

    IndexBuffer = Context->CreateIndexBuffer(KRYS_MAX_INDICES);

    VertexBuffer = Context->CreateVertexBuffer(VERTEX_BUFFER_SIZE);
    VertexBuffer->SetLayout(
        BufferLayout(VERTEX_BUFFER_SIZE,
                     {{ShaderDataType::Float3, "position"},
                      {ShaderDataType::Float4, "color"},
                      {ShaderDataType::Float2, "textureCoord"}},
                     BufferLayoutType::Interleaved));

    VertexArray = Context->CreateVertexArray();
    VertexArray->AddVertexBuffer(VertexBuffer);
    VertexArray->SetIndexBuffer(IndexBuffer);

    Shader = Context->CreateShader();
    Shader->Bind();
    Shader->Load("shaders/renderer-2d.vert", "shaders/renderer-2d.frag");
    Shader->Link();

    Vertices = CreateUnique<std::array<VertexData, KRYS_MAX_VERTICES>>();
    VertexCount = 0;

    Indices = CreateUnique<std::array<uint32, KRYS_MAX_INDICES>>();
    IndexCount = 0;
  }

  void Renderer2D::Shutdown()
  {
    // Everything is static and will get cleaned up when the program terminates, nothing needed for now.
  }

  void Renderer2D::DrawTriangle(Vec3 &posA, Vec3 &posB, Vec3 &posC, Vec4 &color)
  {
    VertexData vertices[] = {
        {posA, color, TRIANGLE_DEFAULT_TEXTURE_COORDS[0]},
        {posB, color, TRIANGLE_DEFAULT_TEXTURE_COORDS[1]},
        {posC, color, TRIANGLE_DEFAULT_TEXTURE_COORDS[2]}};
    uint32 indices[] = TRIANGLE_INDICES(VertexCount);
    AddVertices(&vertices[0], 3, &indices[0], 3);
  }

  void Renderer2D::DrawTriangle(Vec3 &posA, Vec3 &posB, Vec3 &posC, Ref<Texture2D> texture)
  {
    VertexData vertices[] = {
        {posA, DEFAULT_COLOR, TRIANGLE_DEFAULT_TEXTURE_COORDS[0]},
        {posB, DEFAULT_COLOR, TRIANGLE_DEFAULT_TEXTURE_COORDS[1]},
        {posC, DEFAULT_COLOR, TRIANGLE_DEFAULT_TEXTURE_COORDS[2]}};
    uint32 indices[] = TRIANGLE_INDICES(VertexCount);
    AddVertices(&vertices[0], 3, &indices[0], 3);
  }

  void Renderer2D::DrawQuad(Vec3 &pos, Vec2 &size, Vec4 &color)
  {
    VertexData vertices[] = {
        {pos, color, QUAD_DEFAULT_TEXTURE_COORDS[0]},
        {Vec3(pos.x + size.x, pos.y, pos.z), color, QUAD_DEFAULT_TEXTURE_COORDS[1]},
        {Vec3(pos.x, pos.y + size.y, pos.z), color, QUAD_DEFAULT_TEXTURE_COORDS[2]},
        {Vec3(pos.x + size.x, pos.y + size.y, pos.z), color, QUAD_DEFAULT_TEXTURE_COORDS[3]},
    };

    uint32 indices[] = QUAD_INDICES(VertexCount);
    AddVertices(&vertices[0], 4, &indices[0], 6);
  }

  void Renderer2D::DrawQuad(Vec3 &pos, Vec2 &size, Ref<Texture2D> texture)
  {
    VertexData vertices[] = {
        {pos, DEFAULT_COLOR, QUAD_DEFAULT_TEXTURE_COORDS[0]},
        {Vec3(pos.x + size.x, pos.y, pos.z), DEFAULT_COLOR, QUAD_DEFAULT_TEXTURE_COORDS[1]},
        {Vec3(pos.x, pos.y + size.y, pos.z), DEFAULT_COLOR, QUAD_DEFAULT_TEXTURE_COORDS[2]},
        {Vec3(pos.x + size.x, pos.y + size.y, pos.z), DEFAULT_COLOR, QUAD_DEFAULT_TEXTURE_COORDS[3]},
    };

    uint32 indices[] = QUAD_INDICES(VertexCount);
    AddVertices(&vertices[0], 4, &indices[0], 6);
  }

  void Renderer2D::Begin()
  {
    VertexCount = 0;
    IndexCount = 0;
  }

  void Renderer2D::NextBatch()
  {
    // TODO: batch this properly
    End();
    Begin();
  }

  void Renderer2D::End()
  {
    if (VertexCount == 0)
      return;

    Shader->Bind();
    VertexBuffer->SetData(static_cast<void *>(Vertices->data()), VertexCount * sizeof(VertexData));
    IndexBuffer->SetData(Indices->data(), IndexCount);
    glDrawElements(GL_TRIANGLES, IndexCount, GL_UNSIGNED_INT, nullptr);
  }

  void Renderer2D::AddVertices(VertexData *vertices, uint vertexCount, uint32 *indices, uint32 indexCount)
  {
    if (VertexCount + vertexCount >= KRYS_MAX_VERTICES || IndexCount + indexCount >= KRYS_MAX_INDICES)
      NextBatch();

    auto &vertexBuffer = *Vertices;
    for (size_t i = 0; i < vertexCount; i++)
      vertexBuffer[VertexCount++] = vertices[i];

    auto &indexBuffer = *Indices;
    for (size_t i = 0; i < indexCount; i++)
      indexBuffer[IndexCount++] = indices[i];
  }
}