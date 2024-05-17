#include <gl.h>

#include "Graphics/Renderer2D.h"
#include "Misc/Time.h"

namespace Krys
{
#pragma region Constants

  constexpr uint VERTEX_BUFFER_SIZE = sizeof(VertexData) * REN2D_MAX_VERTICES;

  constexpr Vec2 QUAD_DEFAULT_TEXTURE_COORDS[] = {{0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}};
  constexpr Vec3 QUAD_NORMALS[] = {{-0.5f, -0.5f, 0.0f}, {0.5f, -0.5f, 0.0f}, {0.5f, 0.5f, 0.0f}, {-0.5f, 0.5f, 0.0f}};
  constexpr Vec4 QUAD_LOCAL_SPACE_VERTICES[] = {{-0.5f, -0.5f, 0.0f, 1.0f}, {0.5f, -0.5f, 0.0f, 1.0f}, {0.5f, 0.5f, 0.0f, 1.0f}, {-0.5f, 0.5f, 0.0f, 1.0f}};

  constexpr Vec2 TRIANGLE_DEFAULT_TEXTURE_COORDS[] = {{0.0f, 0.0f}, {0.5f, 1.0f}, {1.0f, 0.0f}};
  constexpr Vec3 TRIANGLE_NORMALS[] = {{0.0f, 0.0f, 0.0f}, {0.5f, 1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}};
  constexpr Vec4 TRIANGLE_LOCAL_SPACE_VERTICES[] = {{0.5f, -0.5f, 0.0f, 1.0f}, {-0.5f, -0.5f, 0.0f, 1.0f}, {0.0f, 0.5f, 0.0f, 1.0f}};
  constexpr int DEFAULT_TEXTURE_SLOT_INDEX = 0;

  constexpr Vec4 CUBE_LOCAL_SPACE_VERTICES[] = {
      // Front face
      {-0.5f, -0.5f, 0.5f, 1.0f}, // 0
      {0.5f, -0.5f, 0.5f, 1.0f},  // 1
      {0.5f, 0.5f, 0.5f, 1.0f},   // 2
      {-0.5f, 0.5f, 0.5f, 1.0f},  // 3

      // Back face
      {-0.5f, -0.5f, -0.5f, 1.0f}, // 4
      {0.5f, -0.5f, -0.5f, 1.0f},  // 5
      {0.5f, 0.5f, -0.5f, 1.0f},   // 6
      {-0.5f, 0.5f, -0.5f, 1.0f},  // 7

      // Left face
      {-0.5f, -0.5f, -0.5f, 1.0f}, // 8
      {-0.5f, -0.5f, 0.5f, 1.0f},  // 9
      {-0.5f, 0.5f, 0.5f, 1.0f},   // 10
      {-0.5f, 0.5f, -0.5f, 1.0f},  // 11

      // Right face
      {0.5f, -0.5f, -0.5f, 1.0f}, // 12
      {0.5f, -0.5f, 0.5f, 1.0f},  // 13
      {0.5f, 0.5f, 0.5f, 1.0f},   // 14
      {0.5f, 0.5f, -0.5f, 1.0f},  // 15

      // Top face
      {-0.5f, 0.5f, 0.5f, 1.0f},  // 16
      {0.5f, 0.5f, 0.5f, 1.0f},   // 17
      {0.5f, 0.5f, -0.5f, 1.0f},  // 18
      {-0.5f, 0.5f, -0.5f, 1.0f}, // 19

      // Bottom face
      {-0.5f, -0.5f, 0.5f, 1.0f}, // 20
      {0.5f, -0.5f, 0.5f, 1.0f},  // 21
      {0.5f, -0.5f, -0.5f, 1.0f}, // 22
      {-0.5f, -0.5f, -0.5f, 1.0f} // 23
  };
  constexpr Vec3 CUBE_NORMALS[] = {
      {0.0f, 0.0f, 1.0f}, // Front face
      {0.0f, 0.0f, 1.0f},
      {0.0f, 0.0f, 1.0f},
      {0.0f, 0.0f, 1.0f},

      {0.0f, 0.0f, -1.0f}, // Back face
      {0.0f, 0.0f, -1.0f},
      {0.0f, 0.0f, -1.0f},
      {0.0f, 0.0f, -1.0f},

      {-1.0f, 0.0f, 0.0f}, // Left face
      {-1.0f, 0.0f, 0.0f},
      {-1.0f, 0.0f, 0.0f},
      {-1.0f, 0.0f, 0.0f},

      {1.0f, 0.0f, 0.0f}, // Right face
      {1.0f, 0.0f, 0.0f},
      {1.0f, 0.0f, 0.0f},
      {1.0f, 0.0f, 0.0f},

      {0.0f, 1.0f, 0.0f}, // Top face
      {0.0f, 1.0f, 0.0f},
      {0.0f, 1.0f, 0.0f},
      {0.0f, 1.0f, 0.0f},

      {0.0f, -1.0f, 0.0f}, // Bottom face
      {0.0f, -1.0f, 0.0f},
      {0.0f, -1.0f, 0.0f},
      {0.0f, -1.0f, 0.0f}};

#pragma endregion Constants

#pragma region Static Member Initialisation

  Ref<GraphicsContext> Renderer2D::Context;

  Ref<Shader> Renderer2D::ObjectShader;
  Ref<VertexArray> Renderer2D::ObjectVertexArray;
  Ref<VertexBuffer> Renderer2D::ObjectVertexBuffer;
  Ref<IndexBuffer> Renderer2D::ObjectIndexBuffer;

  Ref<Shader> Renderer2D::LightSourceShader;
  Ref<VertexArray> Renderer2D::LightSourceVertexArray;
  Ref<VertexBuffer> Renderer2D::LightSourceVertexBuffer;
  Ref<IndexBuffer> Renderer2D::LightSourceIndexBuffer;

  Unique<std::array<VertexData, REN2D_MAX_VERTICES>> Renderer2D::Vertices;
  uint Renderer2D::VertexCount;

  Unique<std::array<uint32, REN2D_MAX_INDICES>> Renderer2D::Indices;
  uint Renderer2D::IndexCount;

  Unique<std::array<Ref<Texture2D>, REN2D_MAX_TEXTURE_SLOTS>> Renderer2D::TextureSlots;
  int Renderer2D::TextureSlotIndex;
  Ref<Texture2D> Renderer2D::WhiteTexture;

#pragma endregion Static Member Initialisation

#pragma region Lifecycle Methods

  void Renderer2D::Init(Ref<GraphicsContext> ctx)
  {
    Context = ctx;

    // Object shader
    ObjectVertexBuffer = Context->CreateVertexBuffer(VERTEX_BUFFER_SIZE);
    ObjectVertexBuffer->SetLayout(
        BufferLayout(VERTEX_BUFFER_SIZE,
                     {{ShaderDataType::Float4, "position"},
                      {ShaderDataType::Float3, "normal"},
                      {ShaderDataType::Float4, "color"},
                      {ShaderDataType::Float2, "textureCoord"},
                      {ShaderDataType::Int, "textureSlotIndex"}}));
    ObjectIndexBuffer = Context->CreateIndexBuffer(REN2D_MAX_INDICES);

    ObjectVertexArray = Context->CreateVertexArray();
    ObjectVertexArray->AddVertexBuffer(ObjectVertexBuffer);
    ObjectVertexArray->SetIndexBuffer(ObjectIndexBuffer);

    ObjectShader = Context->CreateShader();
    ObjectShader->Bind();
    ObjectShader->Load("shaders/renderer-2d.vert", "shaders/renderer-2d.frag");
    ObjectShader->Link();
    ObjectShader->SetUniform("u_AmbientStrength", 0.1f);

    // Lighting shader
    uint32 lightingVertexBufferSize = sizeof(LightSourceVertexData) * 24;
    LightSourceVertexBuffer = Context->CreateVertexBuffer(lightingVertexBufferSize);
    LightSourceVertexBuffer->SetLayout(BufferLayout(lightingVertexBufferSize, {{ShaderDataType::Float4, "position"}}));
    LightSourceIndexBuffer = Context->CreateIndexBuffer(36);

    LightSourceVertexArray = Context->CreateVertexArray();
    LightSourceVertexArray->AddVertexBuffer(LightSourceVertexBuffer);
    LightSourceVertexArray->SetIndexBuffer(LightSourceIndexBuffer);

    LightSourceShader = Context->CreateShader();
    LightSourceShader->Bind();
    LightSourceShader->Load("shaders/light-source.vert", "shaders/light-source.frag");
    LightSourceShader->Link();

    Vertices = CreateUnique<std::array<VertexData, REN2D_MAX_VERTICES>>();
    Indices = CreateUnique<std::array<uint32, REN2D_MAX_INDICES>>();

    int samplers[REN2D_MAX_TEXTURE_SLOTS]{};
    for (uint32_t i = 0; i < REN2D_MAX_TEXTURE_SLOTS; i++)
      samplers[i] = i;
    ObjectShader->SetUniform("u_Textures", samplers, REN2D_MAX_TEXTURE_SLOTS);

    Texture2DSettings whiteTextureSettings{};
    whiteTextureSettings.Width = 1;
    whiteTextureSettings.Height = 1;
    whiteTextureSettings.Format = Texture2DFormat::RGBA8;
    WhiteTexture = Context->CreateTexture2D(whiteTextureSettings);

    uint32_t whiteTextureData = 0xffffffff;
    WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

    TextureSlots = CreateUnique<std::array<Ref<Texture2D>, REN2D_MAX_TEXTURE_SLOTS>>();
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
        {model * TRIANGLE_LOCAL_SPACE_VERTICES[0], TRIANGLE_NORMALS[0], color, textureCoords[0], textureSlotIndex},
        {model * TRIANGLE_LOCAL_SPACE_VERTICES[1], TRIANGLE_NORMALS[1], color, textureCoords[1], textureSlotIndex},
        {model * TRIANGLE_LOCAL_SPACE_VERTICES[2], TRIANGLE_NORMALS[2], color, textureCoords[2], textureSlotIndex},
    };

    uint32 indices[] = {VertexCount, VertexCount + 1, VertexCount + 2};
    AddVertices(&vertices[0], 3, &indices[0], 3);
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
        {model * QUAD_LOCAL_SPACE_VERTICES[0], QUAD_NORMALS[0], color, textureCoords[0], textureSlotIndex},
        {model * QUAD_LOCAL_SPACE_VERTICES[1], QUAD_NORMALS[1], color, textureCoords[1], textureSlotIndex},
        {model * QUAD_LOCAL_SPACE_VERTICES[2], QUAD_NORMALS[2], color, textureCoords[2], textureSlotIndex},
        {model * QUAD_LOCAL_SPACE_VERTICES[3], QUAD_NORMALS[3], color, textureCoords[3], textureSlotIndex},
    };

    uint32 indices[] = {VertexCount, VertexCount + 1, VertexCount + 2, VertexCount + 2, VertexCount + 3, VertexCount + 0};
    AddVertices(&vertices[0], 4, &indices[0], 6);
  }

#pragma endregion Drawing Quads

#pragma region Drawing Cubes

  void Renderer2D::DrawCube(Vec3 &pos, Vec3 &size, Vec4 &color, float rotation)
  {
    DrawCube(pos, size, rotation, color, DEFAULT_TEXTURE_SLOT_INDEX, QUAD_DEFAULT_TEXTURE_COORDS);
  }

  void Renderer2D::DrawCube(Vec3 &pos, Vec3 &size, Ref<Texture2D> texture, float rotation, Vec4 &tint)
  {
    DrawCube(pos, size, rotation, tint, GetTextureSlotIndex(texture), QUAD_DEFAULT_TEXTURE_COORDS);
  }

  void Renderer2D::DrawCube(Vec3 &pos, Vec3 &size, Ref<SubTexture2D> subTexture, float rotation, Vec4 &tint)
  {
    auto texture = subTexture->GetTexture();
    DrawCube(pos, size, rotation, tint, GetTextureSlotIndex(texture), subTexture->GetTextureCoords());
  }

  void Renderer2D::DrawCube(Vec3 &pos, Vec3 &size, float rotation, Vec4 &color, int textureSlotIndex, const Vec2 *textureCoords)
  {
    Mat4 model = glm::translate(MAT4_I, pos) * glm::rotate(MAT4_I, glm::radians(rotation), ROTATE_AXIS_Z) * glm::scale(MAT4_I, {size.x, size.y, size.z});

    VertexData vertices[24] = {
        // Front face
        {model * CUBE_LOCAL_SPACE_VERTICES[0], CUBE_NORMALS[0], color, textureCoords[0], textureSlotIndex},
        {model * CUBE_LOCAL_SPACE_VERTICES[1], CUBE_NORMALS[1], color, textureCoords[1], textureSlotIndex},
        {model * CUBE_LOCAL_SPACE_VERTICES[2], CUBE_NORMALS[2], color, textureCoords[2], textureSlotIndex},
        {model * CUBE_LOCAL_SPACE_VERTICES[3], CUBE_NORMALS[3], color, textureCoords[3], textureSlotIndex},

        // Back face
        {model * CUBE_LOCAL_SPACE_VERTICES[4], CUBE_NORMALS[4], color, textureCoords[0], textureSlotIndex},
        {model * CUBE_LOCAL_SPACE_VERTICES[5], CUBE_NORMALS[5], color, textureCoords[1], textureSlotIndex},
        {model * CUBE_LOCAL_SPACE_VERTICES[6], CUBE_NORMALS[6], color, textureCoords[2], textureSlotIndex},
        {model * CUBE_LOCAL_SPACE_VERTICES[7], CUBE_NORMALS[7], color, textureCoords[3], textureSlotIndex},

        // Left face
        {model * CUBE_LOCAL_SPACE_VERTICES[8], CUBE_NORMALS[8], color, textureCoords[0], textureSlotIndex},
        {model * CUBE_LOCAL_SPACE_VERTICES[9], CUBE_NORMALS[9], color, textureCoords[1], textureSlotIndex},
        {model * CUBE_LOCAL_SPACE_VERTICES[10], CUBE_NORMALS[10], color, textureCoords[2], textureSlotIndex},
        {model * CUBE_LOCAL_SPACE_VERTICES[11], CUBE_NORMALS[11], color, textureCoords[3], textureSlotIndex},

        // Right face
        {model * CUBE_LOCAL_SPACE_VERTICES[12], CUBE_NORMALS[12], color, textureCoords[0], textureSlotIndex},
        {model * CUBE_LOCAL_SPACE_VERTICES[13], CUBE_NORMALS[13], color, textureCoords[1], textureSlotIndex},
        {model * CUBE_LOCAL_SPACE_VERTICES[14], CUBE_NORMALS[14], color, textureCoords[2], textureSlotIndex},
        {model * CUBE_LOCAL_SPACE_VERTICES[15], CUBE_NORMALS[15], color, textureCoords[3], textureSlotIndex},

        // Top face
        {model * CUBE_LOCAL_SPACE_VERTICES[16], CUBE_NORMALS[16], color, textureCoords[0], textureSlotIndex},
        {model * CUBE_LOCAL_SPACE_VERTICES[17], CUBE_NORMALS[17], color, textureCoords[1], textureSlotIndex},
        {model * CUBE_LOCAL_SPACE_VERTICES[18], CUBE_NORMALS[18], color, textureCoords[2], textureSlotIndex},
        {model * CUBE_LOCAL_SPACE_VERTICES[19], CUBE_NORMALS[19], color, textureCoords[3], textureSlotIndex},

        // Bottom face
        {model * CUBE_LOCAL_SPACE_VERTICES[20], CUBE_NORMALS[20], color, textureCoords[0], textureSlotIndex},
        {model * CUBE_LOCAL_SPACE_VERTICES[21], CUBE_NORMALS[21], color, textureCoords[1], textureSlotIndex},
        {model * CUBE_LOCAL_SPACE_VERTICES[22], CUBE_NORMALS[22], color, textureCoords[2], textureSlotIndex},
        {model * CUBE_LOCAL_SPACE_VERTICES[23], CUBE_NORMALS[23], color, textureCoords[3], textureSlotIndex},
    };

    uint32 indices[36] = {
        // Front face
        VertexCount,
        VertexCount + 1,
        VertexCount + 2,
        VertexCount + 2,
        VertexCount + 3,
        VertexCount,

        // Back face
        VertexCount + 4,
        VertexCount + 5,
        VertexCount + 6,
        VertexCount + 6,
        VertexCount + 7,
        VertexCount + 4,

        // Left face
        VertexCount + 8,
        VertexCount + 9,
        VertexCount + 10,
        VertexCount + 10,
        VertexCount + 11,
        VertexCount + 8,

        // Right face
        VertexCount + 12,
        VertexCount + 13,
        VertexCount + 14,
        VertexCount + 14,
        VertexCount + 15,
        VertexCount + 12,

        // Top face
        VertexCount + 16,
        VertexCount + 17,
        VertexCount + 18,
        VertexCount + 18,
        VertexCount + 19,
        VertexCount + 16,

        // Bottom face
        VertexCount + 20,
        VertexCount + 21,
        VertexCount + 22,
        VertexCount + 22,
        VertexCount + 23,
        VertexCount + 20,
    };

    AddVertices(&vertices[0], 24, &indices[0], 36);
  }

#pragma endregion Drawing Cubes

  void Renderer2D::DrawLightSourceCube(Vec3 &pos, Vec3 &size, float rotation)
  {
    Mat4 model = glm::translate(MAT4_I, pos) * glm::rotate(MAT4_I, glm::radians(rotation), ROTATE_AXIS_Z) * glm::scale(MAT4_I, {size.x, size.y, size.z});

    LightSourceVertexData vertices[24] = {
        // Front face
        {model * CUBE_LOCAL_SPACE_VERTICES[0]},
        {model * CUBE_LOCAL_SPACE_VERTICES[1]},
        {model * CUBE_LOCAL_SPACE_VERTICES[2]},
        {model * CUBE_LOCAL_SPACE_VERTICES[3]},

        // Back face
        {model * CUBE_LOCAL_SPACE_VERTICES[4]},
        {model * CUBE_LOCAL_SPACE_VERTICES[5]},
        {model * CUBE_LOCAL_SPACE_VERTICES[6]},
        {model * CUBE_LOCAL_SPACE_VERTICES[7]},

        // Left face
        {model * CUBE_LOCAL_SPACE_VERTICES[8]},
        {model * CUBE_LOCAL_SPACE_VERTICES[9]},
        {model * CUBE_LOCAL_SPACE_VERTICES[10]},
        {model * CUBE_LOCAL_SPACE_VERTICES[11]},

        // Right face
        {model * CUBE_LOCAL_SPACE_VERTICES[12]},
        {model * CUBE_LOCAL_SPACE_VERTICES[13]},
        {model * CUBE_LOCAL_SPACE_VERTICES[14]},
        {model * CUBE_LOCAL_SPACE_VERTICES[15]},

        // Top face
        {model * CUBE_LOCAL_SPACE_VERTICES[16]},
        {model * CUBE_LOCAL_SPACE_VERTICES[17]},
        {model * CUBE_LOCAL_SPACE_VERTICES[18]},
        {model * CUBE_LOCAL_SPACE_VERTICES[19]},

        // Bottom face
        {model * CUBE_LOCAL_SPACE_VERTICES[20]},
        {model * CUBE_LOCAL_SPACE_VERTICES[21]},
        {model * CUBE_LOCAL_SPACE_VERTICES[22]},
        {model * CUBE_LOCAL_SPACE_VERTICES[23]},
    };

    uint32 indices[36] = {
        // Front face
        0,
        1,
        2,
        2,
        3,
        0,

        // Back face
        4,
        5,
        6,
        6,
        7,
        4,

        // Left face
        8,
        9,
        10,
        10,
        11,
        8,

        // Right face
        12,
        13,
        14,
        14,
        15,
        12,

        // Top face
        16,
        17,
        18,
        18,
        19,
        16,

        // Bottom face
        20,
        21,
        22,
        22,
        23,
        20,
    };

    LightSourceShader->Bind();
    LightSourceVertexArray->Bind();
    LightSourceVertexBuffer->SetData(&vertices[0], 24 * sizeof(LightSourceVertexData));
    LightSourceIndexBuffer->SetData(indices, 36);

    glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, nullptr);
  }

  void Renderer2D::SetLightSourceColor(Vec4 &color)
  {
    ObjectShader->SetUniform("u_LightColor", color);
  }

  void Renderer2D::Reset()
  {
    VertexCount = 0;
    IndexCount = 0;
    TextureSlotIndex = 1; // 0 == WhiteTexture
  }

  void Renderer2D::BeginScene(Ref<Camera> camera)
  {
    auto &viewProjection = camera->GetViewProjection();
    ObjectShader->SetUniform("u_ViewProjection", viewProjection);
    LightSourceShader->SetUniform("u_ViewProjection", viewProjection);

    Reset();
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

    ObjectShader->Bind();
    ObjectVertexArray->Bind();
    ObjectVertexBuffer->SetData(Vertices->data(), VertexCount * sizeof(VertexData));
    ObjectIndexBuffer->SetData(Indices->data(), IndexCount);

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
    if (VertexCount + vertexCount >= REN2D_MAX_VERTICES || IndexCount + indexCount >= REN2D_MAX_INDICES)
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
      if (TextureSlotIndex == REN2D_MAX_TEXTURE_SLOTS - 1)
      {
        NextBatch();
      }
      textureSlotIndex = TextureSlotIndex++;
      textureSlots[textureSlotIndex] = texture;
    }

    return textureSlotIndex;
  }
}
