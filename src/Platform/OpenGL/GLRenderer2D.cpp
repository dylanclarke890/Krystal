#include <gl.h>

#include "Graphics/Renderer2D.h"
#include "Misc/Time.h"

namespace Krys
{
#pragma region Constants

  constexpr uint VERTEX_BUFFER_SIZE = sizeof(VertexData) * KRYS_MAX_VERTICES;
  constexpr Vec2 QUAD_DEFAULT_TEXTURE_COORDS[] = {{0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}};
  constexpr Vec4 QUAD_LOCAL_SPACE_VERTICES[] = {{-0.5f, -0.5f, 0.0f, 1.0f}, {0.5f, -0.5f, 0.0f, 1.0f}, {0.5f, 0.5f, 0.0f, 1.0f}, {-0.5f, 0.5f, 0.0f, 1.0f}};

  constexpr Vec2 TRIANGLE_DEFAULT_TEXTURE_COORDS[] = {{0.0f, 0.0f}, {0.5f, 1.0f}, {1.0f, 0.0f}};
  constexpr Vec4 TRIANGLE_LOCAL_SPACE_VERTICES[] = {{0.5f, -0.5f, 0.0f, 1.0f}, {-0.5f, -0.5f, 0.0f, 1.0f}, {0.0f, 0.5f, 0.0f, 1.0f}};
  constexpr int DEFAULT_TEXTURE_SLOT_INDEX = 0;
  constexpr Vec3 ROTATE_AXIS_X = Vec3(1.0f, 0.0f, 0.0f);
  constexpr Vec3 ROTATE_AXIS_Y = Vec3(0.0f, 1.0f, 0.0f);
  constexpr Vec3 ROTATE_AXIS_Z = Vec3(0.0f, 0.0f, 1.0f);
  constexpr Mat4 MAT4_I = Mat4(1.0f);

#pragma endregion Constants

#pragma region Static Member Initialisation

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

#pragma endregion Static Member Initialisation

#pragma region Lifecycle Methods

  void Renderer2D::Init(Ref<GraphicsContext> ctx)
  {
    Context = ctx;
    VertexArray = Context->CreateVertexArray();

    VertexBuffer = Context->CreateVertexBuffer(VERTEX_BUFFER_SIZE);
    VertexBuffer->SetLayout(
        BufferLayout(VERTEX_BUFFER_SIZE,
                     {{ShaderDataType::Float4, "position"},
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

#pragma endregion Lifecycle Methods

#pragma region Drawing Triangles

  void Renderer2D::DrawTriangle(Vec3 &pos, Vec2 &size, Vec4 &color, float rotation)
  {
    DrawTriangle(pos, size, rotation, color, DEFAULT_TEXTURE_SLOT_INDEX, TRIANGLE_DEFAULT_TEXTURE_COORDS);
  }

  void Renderer2D::DrawTriangle(Vec3 &pos, Vec2 &size, Ref<Texture2D> texture, float rotation, Vec4 &tint)
  {
    DrawTriangle(pos, size, rotation, tint, GetTextureSlotIndex(texture), TRIANGLE_DEFAULT_TEXTURE_COORDS);
  }

  void Renderer2D::DrawTriangle(Vec3 &pos, Vec2 &size, Ref<SubTexture2D> subTexture, float rotation, Vec4 &tint)
  {
    auto texture = subTexture->GetTexture();
    DrawTriangle(pos, size, rotation, tint, GetTextureSlotIndex(texture), subTexture->GetTextureCoords());
  }

  void Renderer2D::DrawTriangle(Vec3 &pos, Vec2 &size, float rotation, Vec4 &color, int textureSlotIndex, const Vec2 *textureCoords)
  {
    Mat4 model = glm::translate(MAT4_I, pos) * glm::rotate(MAT4_I, glm::radians(rotation), ROTATE_AXIS_Z) * glm::scale(MAT4_I, {size.x, size.y, 1.0f});

    VertexData vertices[] = {
        {model * TRIANGLE_LOCAL_SPACE_VERTICES[0], color, textureCoords[0], textureSlotIndex},
        {model * TRIANGLE_LOCAL_SPACE_VERTICES[1], color, textureCoords[1], textureSlotIndex},
        {model * TRIANGLE_LOCAL_SPACE_VERTICES[2], color, textureCoords[2], textureSlotIndex},
    };

    uint32 indices[] = {VertexCount, VertexCount + 1, VertexCount + 2};
    AddVertices(&vertices[0], 4, &indices[0], 6);
  }

#pragma endregion Drawing Triangles

#pragma region Drawing Quads

  void Renderer2D::DrawQuad(Vec3 &pos, Vec2 &size, Vec4 &color, float rotation)
  {
    DrawQuad(pos, size, rotation, color, DEFAULT_TEXTURE_SLOT_INDEX, QUAD_DEFAULT_TEXTURE_COORDS);
  }

  void Renderer2D::DrawQuad(Vec3 &pos, Vec2 &size, Ref<Texture2D> texture, float rotation, Vec4 &tint)
  {
    DrawQuad(pos, size, rotation, tint, GetTextureSlotIndex(texture), QUAD_DEFAULT_TEXTURE_COORDS);
  }

  void Renderer2D::DrawQuad(Vec3 &pos, Vec2 &size, Ref<SubTexture2D> subTexture, float rotation, Vec4 &tint)
  {
    auto texture = subTexture->GetTexture();
    DrawQuad(pos, size, rotation, tint, GetTextureSlotIndex(texture), subTexture->GetTextureCoords());
  }

  void Renderer2D::DrawQuad(Vec3 &pos, Vec2 &size, float rotation, Vec4 &color, int textureSlotIndex, const Vec2 *textureCoords)
  {
    Mat4 model = glm::translate(MAT4_I, pos) * glm::rotate(MAT4_I, glm::radians(rotation), ROTATE_AXIS_Z) * glm::scale(MAT4_I, {size.x, size.y, 1.0f});

    VertexData vertices[] = {
        {model * QUAD_LOCAL_SPACE_VERTICES[0], color, textureCoords[0], textureSlotIndex},
        {model * QUAD_LOCAL_SPACE_VERTICES[1], color, textureCoords[1], textureSlotIndex},
        {model * QUAD_LOCAL_SPACE_VERTICES[2], color, textureCoords[2], textureSlotIndex},
        {model * QUAD_LOCAL_SPACE_VERTICES[3], color, textureCoords[3], textureSlotIndex},
    };

    uint32 indices[] = {VertexCount, VertexCount + 1, VertexCount + 2, VertexCount + 2, VertexCount + 3, VertexCount + 0};
    AddVertices(&vertices[0], 4, &indices[0], 6);
  }

#pragma endregion Drawing Quads

  void Renderer2D::Reset()
  {
    VertexCount = 0;
    IndexCount = 0;
    TextureSlotIndex = 1; // 0 == WhiteTexture
  }

  void Renderer2D::BeginScene(Ref<Camera> camera)
  {
    Reset();

    auto &viewProjection = camera->GetViewProjection();
    Shader->SetUniform("u_Transform", viewProjection);
  }

  void Renderer2D::NextBatch()
  {
    Flush();
    Reset();
  }

  void Renderer2D::Flush()
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

  void Renderer2D::EndScene()
  {
    Flush();
  }

  void Renderer2D::AddVertices(VertexData *vertices, uint vertexCount, uint32 *indices, uint32 indexCount)
  {
    if (VertexCount + vertexCount >= KRYS_MAX_VERTICES || IndexCount + indexCount >= KRYS_MAX_INDICES)
    {
      NextBatch();
    }

    // Translate * Rotate * Scale * vector_to_transform.

    auto &vertexBuffer = *Vertices;
    for (size_t i = 0; i < vertexCount; i++)
      vertexBuffer[VertexCount++] = vertices[i];

    auto &indexBuffer = *Indices;
    for (size_t i = 0; i < indexCount; i++)
      indexBuffer[IndexCount++] = indices[i];
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
