#include "Graphics/Renderer2D.h"

#include <gl.h>

namespace Krys
{
  constexpr uint VERTEX_BUFFER_SIZE = sizeof(VertexData) * KRYS_MAX_VERTICES;
  constexpr Vec4 DEFAULT_COLOR = {1.0f, 1.0f, 1.0f, 1.0f};
  constexpr Vec2 QUAD_DEFAULT_TEXTURE_COORDS[] = {{0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}};
  constexpr Vec2 TRIANGLE_DEFAULT_TEXTURE_COORDS[] = {{0.0f, 0.0f}, {0.5f, 1.0f}, {1.0f, 0.0f}};
  constexpr int DEFAULT_TEXTURE_SLOT_INDEX = 0;
  // TODO: temporary
#define QUAD_INDICES(vertexCount)                                                                    \
  {                                                                                                  \
    vertexCount, vertexCount + 1, vertexCount + 2, vertexCount + 2, vertexCount + 3, vertexCount + 0 \
  }

#define TRIANGLE_INDICES(vertexCount)             \
  {                                               \
    vertexCount, vertexCount + 1, vertexCount + 2 \
  }

  Ref<GraphicsContext> Renderer2D::Context;

  Ref<VertexArray> Renderer2D::VertexArray;
  Ref<VertexBuffer> Renderer2D::VertexBuffer;
  Ref<IndexBuffer> Renderer2D::IndexBuffer;

  Unique<std::array<VertexData, KRYS_MAX_VERTICES>> Renderer2D::Vertices;
  uint Renderer2D::VertexCount;

  Unique<std::array<uint32, KRYS_MAX_INDICES>> Renderer2D::Indices;
  uint Renderer2D::IndexCount;

  Ref<Shader> Renderer2D::Shader;

  Unique<std::array<Ref<Texture2D>, KRYS_MAX_TEXTURE_SLOTS>> Renderer2D::TextureSlots;
  int Renderer2D::TextureSlotIndex;
  Ref<Texture2D> Renderer2D::WhiteTexture;

  void Renderer2D::Init(Ref<GraphicsContext> ctx)
  {
    Context = ctx;
    VertexArray = Context->CreateVertexArray();

    VertexBuffer = Context->CreateVertexBuffer(VERTEX_BUFFER_SIZE);
    VertexBuffer->SetLayout(
        BufferLayout(VERTEX_BUFFER_SIZE,
                     {{ShaderDataType::Float3, "position"},
                      {ShaderDataType::Float4, "color"},
                      {ShaderDataType::Float2, "textureCoord"},
                      {ShaderDataType::Int, "textureSlotIndex"}},
                     BufferLayoutType::Interleaved));
    VertexArray->AddVertexBuffer(VertexBuffer);

    IndexBuffer = Context->CreateIndexBuffer(KRYS_MAX_INDICES);
    VertexArray->SetIndexBuffer(IndexBuffer);

    Vertices = CreateUnique<std::array<VertexData, KRYS_MAX_VERTICES>>();
    Indices = CreateUnique<std::array<uint32, KRYS_MAX_INDICES>>();

    Shader = Context->CreateShader();
    Shader->Bind();
    Shader->Load("shaders/renderer-2d.vert", "shaders/renderer-2d.frag");
    Shader->Link();

    int samplers[KRYS_MAX_TEXTURE_SLOTS]{};
    for (uint32_t i = 0; i < KRYS_MAX_TEXTURE_SLOTS; i++)
      samplers[i] = i;
    Shader->SetUniform("u_Textures", samplers, KRYS_MAX_TEXTURE_SLOTS);

    Texture2DSettings whiteTextureSettings{};
    whiteTextureSettings.Width = 1;
    whiteTextureSettings.Height = 1;
    whiteTextureSettings.Format = Texture2DFormat::RGBA8;
    WhiteTexture = Context->CreateTexture2D(whiteTextureSettings);

    uint32_t whiteTextureData = 0xffffffff;
    WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

    TextureSlots = CreateUnique<std::array<Ref<Texture2D>, KRYS_MAX_TEXTURE_SLOTS>>();
    (*TextureSlots.get())[0] = WhiteTexture;

    Reset();
  }

  void Renderer2D::Shutdown()
  {
    // Everything is static and will get cleaned up when the program terminates, nothing needed for now.
  }

#pragma region Triangles
  void Renderer2D::DrawTriangle(Vec3 &posA, Vec3 &posB, Vec3 &posC, Vec4 &color)
  {
    VertexData vertices[] = {
        {posA, color, TRIANGLE_DEFAULT_TEXTURE_COORDS[0], DEFAULT_TEXTURE_SLOT_INDEX},
        {posB, color, TRIANGLE_DEFAULT_TEXTURE_COORDS[1], DEFAULT_TEXTURE_SLOT_INDEX},
        {posC, color, TRIANGLE_DEFAULT_TEXTURE_COORDS[2], DEFAULT_TEXTURE_SLOT_INDEX}};
    uint32 indices[] = TRIANGLE_INDICES(VertexCount);
    AddVertices(&vertices[0], 3, &indices[0], 3);
  }

  void Renderer2D::DrawTriangle(Vec3 &posA, Vec3 &posB, Vec3 &posC, Ref<Texture2D> texture)
  {
    auto slotIndex = GetTextureSlotIndex(texture);
    VertexData vertices[] = {
        {posA, DEFAULT_COLOR, TRIANGLE_DEFAULT_TEXTURE_COORDS[0], slotIndex},
        {posB, DEFAULT_COLOR, TRIANGLE_DEFAULT_TEXTURE_COORDS[1], slotIndex},
        {posC, DEFAULT_COLOR, TRIANGLE_DEFAULT_TEXTURE_COORDS[2], slotIndex}};
    uint32 indices[] = TRIANGLE_INDICES(VertexCount);
    AddVertices(&vertices[0], 3, &indices[0], 3);
  }

  void Renderer2D::DrawTriangle(Vec3 &posA, Vec3 &posB, Vec3 &posC, Ref<Texture2D> texture, Vec4 &tint)
  {
    auto slotIndex = GetTextureSlotIndex(texture);
    VertexData vertices[] = {
        {posA, tint, TRIANGLE_DEFAULT_TEXTURE_COORDS[0], slotIndex},
        {posB, tint, TRIANGLE_DEFAULT_TEXTURE_COORDS[1], slotIndex},
        {posC, tint, TRIANGLE_DEFAULT_TEXTURE_COORDS[2], slotIndex}};
    uint32 indices[] = TRIANGLE_INDICES(VertexCount);
    AddVertices(&vertices[0], 3, &indices[0], 3);
  }

  void Renderer2D::DrawTriangle(Vec3 &posA, Vec3 &posB, Vec3 &posC, Ref<SubTexture2D> subTexture)
  {
    auto texture = subTexture->GetTexture();
    auto textureCoords = subTexture->GetTextureCoords();
    auto slotIndex = GetTextureSlotIndex(texture);

    VertexData vertices[] = {
        {posA, DEFAULT_COLOR, textureCoords[0], slotIndex},
        {posB, DEFAULT_COLOR, textureCoords[1], slotIndex},
        {posC, DEFAULT_COLOR, textureCoords[2], slotIndex}};
    uint32 indices[] = TRIANGLE_INDICES(VertexCount);
    AddVertices(&vertices[0], 3, &indices[0], 3);
  }

  void Renderer2D::DrawTriangle(Vec3 &posA, Vec3 &posB, Vec3 &posC, Ref<SubTexture2D> subTexture, Vec4 &tint)
  {
    auto texture = subTexture->GetTexture();
    auto textureCoords = subTexture->GetTextureCoords();
    auto slotIndex = GetTextureSlotIndex(texture);

    VertexData vertices[] = {
        {posA, tint, textureCoords[0], slotIndex},
        {posB, tint, textureCoords[1], slotIndex},
        {posC, tint, textureCoords[2], slotIndex}};
    uint32 indices[] = TRIANGLE_INDICES(VertexCount);
    AddVertices(&vertices[0], 3, &indices[0], 3);
  }

#pragma endregion Triangles

#pragma region Quads

  void Renderer2D::DrawQuad(Vec3 &pos, Vec2 &size, Vec4 &color)
  {
    VertexData vertices[] = {
        {pos, color, QUAD_DEFAULT_TEXTURE_COORDS[0], DEFAULT_TEXTURE_SLOT_INDEX},
        {Vec3(pos.x + size.x, pos.y, pos.z), color, QUAD_DEFAULT_TEXTURE_COORDS[1], DEFAULT_TEXTURE_SLOT_INDEX},
        {Vec3(pos.x + size.x, pos.y + size.y, pos.z), color, QUAD_DEFAULT_TEXTURE_COORDS[2], DEFAULT_TEXTURE_SLOT_INDEX},
        {Vec3(pos.x, pos.y + size.y, pos.z), color, QUAD_DEFAULT_TEXTURE_COORDS[3], DEFAULT_TEXTURE_SLOT_INDEX},
    };

    uint32 indices[] = QUAD_INDICES(VertexCount);
    AddVertices(&vertices[0], 4, &indices[0], 6);
  }

  void Renderer2D::DrawQuad(Vec3 &pos, Vec2 &size, Ref<Texture2D> texture)
  {
    auto slotIndex = GetTextureSlotIndex(texture);

    VertexData vertices[] = {
        {pos, DEFAULT_COLOR, QUAD_DEFAULT_TEXTURE_COORDS[0], slotIndex},
        {Vec3(pos.x + size.x, pos.y, pos.z), DEFAULT_COLOR, QUAD_DEFAULT_TEXTURE_COORDS[1], slotIndex},
        {Vec3(pos.x + size.x, pos.y + size.y, pos.z), DEFAULT_COLOR, QUAD_DEFAULT_TEXTURE_COORDS[2], slotIndex},
        {Vec3(pos.x, pos.y + size.y, pos.z), DEFAULT_COLOR, QUAD_DEFAULT_TEXTURE_COORDS[3], slotIndex},
    };

    uint32 indices[] = QUAD_INDICES(VertexCount);
    AddVertices(&vertices[0], 4, &indices[0], 6);
  }

  void Renderer2D::DrawQuad(Vec3 &pos, Vec2 &size, Ref<Texture2D> texture, Vec4 &tint)
  {
    auto slotIndex = GetTextureSlotIndex(texture);

    VertexData vertices[] = {
        {pos, tint, QUAD_DEFAULT_TEXTURE_COORDS[0], slotIndex},
        {Vec3(pos.x + size.x, pos.y, pos.z), tint, QUAD_DEFAULT_TEXTURE_COORDS[1], slotIndex},
        {Vec3(pos.x + size.x, pos.y + size.y, pos.z), tint, QUAD_DEFAULT_TEXTURE_COORDS[2], slotIndex},
        {Vec3(pos.x, pos.y + size.y, pos.z), tint, QUAD_DEFAULT_TEXTURE_COORDS[3], slotIndex},
    };

    uint32 indices[] = QUAD_INDICES(VertexCount);
    AddVertices(&vertices[0], 4, &indices[0], 6);
  }

  void Renderer2D::DrawQuad(Vec3 &pos, Vec2 &size, Ref<SubTexture2D> subTexture)
  {
    auto texture = subTexture->GetTexture();
    auto textureCoords = subTexture->GetTextureCoords();
    auto slotIndex = GetTextureSlotIndex(texture);

    VertexData vertices[] = {
        {pos, DEFAULT_COLOR, textureCoords[0], slotIndex},
        {Vec3(pos.x + size.x, pos.y, pos.z), DEFAULT_COLOR, textureCoords[1], slotIndex},
        {Vec3(pos.x + size.x, pos.y + size.y, pos.z), DEFAULT_COLOR, textureCoords[2], slotIndex},
        {Vec3(pos.x, pos.y + size.y, pos.z), DEFAULT_COLOR, textureCoords[3], slotIndex},
    };

    uint32 indices[] = QUAD_INDICES(VertexCount);
    AddVertices(&vertices[0], 4, &indices[0], 6);
  }

  void Renderer2D::DrawQuad(Vec3 &pos, Vec2 &size, Ref<SubTexture2D> subTexture, Vec4 &tint)
  {
    auto texture = subTexture->GetTexture();
    auto textureCoords = subTexture->GetTextureCoords();
    auto slotIndex = GetTextureSlotIndex(texture);

    VertexData vertices[] = {
        {pos, tint, textureCoords[0], slotIndex},
        {Vec3(pos.x + size.x, pos.y, pos.z), tint, textureCoords[1], slotIndex},
        {Vec3(pos.x + size.x, pos.y + size.y, pos.z), tint, textureCoords[2], slotIndex},
        {Vec3(pos.x, pos.y + size.y, pos.z), tint, textureCoords[3], slotIndex},
    };

    uint32 indices[] = QUAD_INDICES(VertexCount);
    AddVertices(&vertices[0], 4, &indices[0], 6);
  }

#pragma endregion Quads

  void Renderer2D::BeginScene()
  {
    Reset();

    Mat4 model = glm::rotate(Mat4(1.0f), glm::radians(-55.0f), Vec3(1.0f, 0.0f, 0.0f));
    Mat4 view = glm::translate(Mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
    Mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    Shader->SetUniform("u_Transform", projection * view * model);
  }

  void Renderer2D::NextBatch()
  {
    // TODO: batch this properly
    EndScene();
    BeginScene();
  }

  void Renderer2D::EndScene()
  {
    if (VertexCount == 0)
      return;

    Shader->Bind();
    VertexBuffer->SetData(static_cast<void *>(Vertices->data()), VertexCount * sizeof(VertexData));
    IndexBuffer->SetData(Indices->data(), IndexCount);

    auto &textureSlots = *TextureSlots;
    for (int i = 0; i < TextureSlotIndex; i++)
      textureSlots[i]->Bind(i);

    glDrawElements(GL_TRIANGLES, IndexCount, GL_UNSIGNED_INT, nullptr);
  }

  void Renderer2D::AddVertices(VertexData *vertices, uint vertexCount, uint32 *indices, uint32 indexCount)
  {
    if (VertexCount + vertexCount >= KRYS_MAX_VERTICES || IndexCount + indexCount >= KRYS_MAX_INDICES)
    {
      NextBatch();
    }

    auto &vertexBuffer = *Vertices;
    for (size_t i = 0; i < vertexCount; i++)
      vertexBuffer[VertexCount++] = vertices[i];

    auto &indexBuffer = *Indices;
    for (size_t i = 0; i < indexCount; i++)
      indexBuffer[IndexCount++] = indices[i];
  }

  void Renderer2D::Reset()
  {
    VertexCount = 0;
    IndexCount = 0;
    TextureSlotIndex = 1; // 0 == WhiteTexture
  }

  int Renderer2D::GetTextureSlotIndex(Ref<Texture2D> texture)
  {
    int textureSlotIndex = -1;
    auto &textureSlots = *TextureSlots;
    for (int i = 0; i < TextureSlotIndex; i++)
    {
      if (textureSlots[i]->GetRendererId() == texture->GetRendererId())
      {
        textureSlotIndex = i;
        break;
      }
    }

    if (textureSlotIndex == -1)
    {
      if (TextureSlotIndex == KRYS_MAX_TEXTURE_SLOTS - 1)
      {
        NextBatch();
      }
      textureSlotIndex = TextureSlotIndex++;
      textureSlots[textureSlotIndex] = texture;
    }

    return textureSlotIndex;
  }
}
