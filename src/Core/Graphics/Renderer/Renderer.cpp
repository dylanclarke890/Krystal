#include <execution>
#include <algorithm>

#include "Renderer.h"
#include "Misc/Time.h"

namespace Krys
{
#pragma region Constants

  constexpr Vec2 QUAD_DEFAULT_TEXTURE_COORDS[] = {{0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}};
  constexpr Vec3 QUAD_NORMALS[] = {{0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}};
  constexpr Vec4 QUAD_LOCAL_SPACE_VERTICES[] = {{-0.5f, -0.5f, 0.0f, 1.0f}, {0.5f, -0.5f, 0.0f, 1.0f}, {0.5f, 0.5f, 0.0f, 1.0f}, {-0.5f, 0.5f, 0.0f, 1.0f}};

  constexpr Vec2 TRIANGLE_DEFAULT_TEXTURE_COORDS[] = {{0.0f, 0.0f}, {0.5f, 1.0f}, {1.0f, 0.0f}};
  constexpr Vec3 TRIANGLE_NORMALS[] = {{0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}};
  constexpr Vec4 TRIANGLE_LOCAL_SPACE_VERTICES[] = {{0.5f, -0.5f, 0.0f, 1.0f}, {-0.5f, -0.5f, 0.0f, 1.0f}, {0.0f, 0.5f, 0.0f, 1.0f}};

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

  Ref<GraphicsContext> Renderer::Context;

  Ref<Shader> Renderer::ObjectShader;
  Ref<VertexArray> Renderer::ObjectVertexArray;
  Ref<VertexBuffer> Renderer::ObjectVertexBuffer;
  Ref<IndexBuffer> Renderer::ObjectIndexBuffer;
  Ref<UniformBuffer> Renderer::ObjectUniformBuffer;

  Unique<std::array<VertexData, REN2D_MAX_VERTICES>> Renderer::Vertices;
  uint Renderer::VertexCount;

  Unique<std::array<uint32, REN2D_MAX_INDICES>> Renderer::Indices;
  uint Renderer::IndexCount;

  Unique<std::array<Ref<Texture2D>, REN2D_MAX_TEXTURE_SLOTS>> Renderer::TextureSlots;
  int Renderer::TextureSlotIndex;

  Ref<Shader> Renderer::ShaderInUse;
  Vec4 Renderer::SceneCameraPosition;

#pragma endregion Static Member Initialisation

#pragma region Lifecycle Methods

  void Renderer::Init(Ref<GraphicsContext> ctx)
  {
    Context = ctx;

    // Object shader
    ObjectVertexBuffer = Context->CreateVertexBuffer(sizeof(VertexData) * REN2D_MAX_VERTICES);
    ObjectVertexBuffer->SetLayout(VertexBufferLayout({{ShaderDataType::Float4, "i_ModelPosition"},
                                                      {ShaderDataType::Float3, "i_Normal"},
                                                      {ShaderDataType::Float4, "i_Color"},
                                                      {ShaderDataType::Float2, "i_TextureCoord"},
                                                      {ShaderDataType::Int, "i_TextureSlot"},
                                                      {ShaderDataType::Int, "i_SpecularSlot"},
                                                      {ShaderDataType::Int, "i_EmissionSlot"},
                                                      {ShaderDataType::Float, "i_Shininess"}}));
    ObjectIndexBuffer = Context->CreateIndexBuffer(REN2D_MAX_INDICES);

    ObjectVertexArray = Context->CreateVertexArray();
    ObjectVertexArray->AddVertexBuffer(ObjectVertexBuffer);
    ObjectVertexArray->SetIndexBuffer(ObjectIndexBuffer);
    ObjectUniformBuffer = Context->CreateUniformBuffer(0,
                                                       {{UniformDataType::Mat4, "u_ViewProjection"},
                                                        {UniformDataType::Vec3, "u_CameraPosition"}});

    ObjectShader = Context->CreateShader("shaders/renderer-2d/v.vert", "shaders/renderer-2d/f.frag");

    Vertices = CreateUnique<std::array<VertexData, REN2D_MAX_VERTICES>>();
    Indices = CreateUnique<std::array<uint32, REN2D_MAX_INDICES>>();

    TextureSlots = CreateUnique<std::array<Ref<Texture2D>, REN2D_MAX_TEXTURE_SLOTS>>();
    int samplers[REN2D_MAX_TEXTURE_SLOTS]{};
    for (uint32_t i = 0; i < REN2D_MAX_TEXTURE_SLOTS; i++)
      samplers[i] = i;
    ObjectShader->SetUniform("u_Textures", samplers, REN2D_MAX_TEXTURE_SLOTS);

    Reset();
  }

  void Renderer::Shutdown()
  {
    // Everything is static and will get cleaned up when the program terminates, nothing needed for now.
  }

#pragma endregion Lifecycle Methods

#pragma region Drawing Triangles

  void Renderer::DrawTriangle(Ref<Transform> transform, Vec4 &color)
  {
    TextureData textureData{TRIANGLE_DEFAULT_TEXTURE_COORDS, color};
    DrawTriangle(transform, textureData);
  }

  void Renderer::DrawTriangle(Ref<Transform> transform, Ref<Material> material)
  {
    TextureData textureData{TRIANGLE_DEFAULT_TEXTURE_COORDS, material->Tint};
    textureData.Texture = GetTextureSlotIndex(material->Diffuse);
    textureData.Specular = GetTextureSlotIndex(material->Specular);
    textureData.Emission = GetTextureSlotIndex(material->Emission);
    textureData.Shininess = material->Shininess;
    DrawTriangle(transform, textureData);
  }

  void Renderer::DrawTriangle(Ref<Transform> transform, Ref<SubTexture2D> subTexture, Vec4 &tint)
  {
    TextureData textureData{subTexture->GetTextureCoords(), tint};
    textureData.Texture = GetTextureSlotIndex(subTexture->GetTexture());
    DrawTriangle(transform, textureData);
  }

  void Renderer::DrawTriangle(Ref<Transform> transform, TextureData &textureData)
  {
    const uint vertex_count = 3;
    const uint index_count = 3;

    Mat4 model = transform->GetModel();
    Mat3 normal = Mat3(glm::transpose(glm::inverse(model)));

    auto &td = textureData;
    VertexData vertices[vertex_count] = {
        {model * TRIANGLE_LOCAL_SPACE_VERTICES[0], normal * TRIANGLE_NORMALS[0], td.Tint, td.TextureCoords[0], td.Texture, td.Specular, td.Emission, td.Shininess},
        {model * TRIANGLE_LOCAL_SPACE_VERTICES[1], normal * TRIANGLE_NORMALS[1], td.Tint, td.TextureCoords[1], td.Texture, td.Specular, td.Emission, td.Shininess},
        {model * TRIANGLE_LOCAL_SPACE_VERTICES[2], normal * TRIANGLE_NORMALS[2], td.Tint, td.TextureCoords[2], td.Texture, td.Specular, td.Emission, td.Shininess},
    };

    uint32 indices[index_count] = {VertexCount, VertexCount + 1, VertexCount + 2};
    AddVertices(&vertices[0], vertex_count, &indices[0], index_count);
  }

#pragma endregion Drawing Triangles

#pragma region Drawing Quads

  void Renderer::DrawQuad(Ref<Transform> transform, Vec4 &color)
  {
    TextureData textureData{QUAD_DEFAULT_TEXTURE_COORDS, color};
    DrawQuad(transform, textureData);
  }

  void Renderer::DrawQuad(Ref<Transform> transform, Ref<Material> material)
  {
    TextureData textureData{QUAD_DEFAULT_TEXTURE_COORDS, material->Tint};
    textureData.Texture = GetTextureSlotIndex(material->Diffuse);
    textureData.Specular = GetTextureSlotIndex(material->Specular);
    textureData.Emission = GetTextureSlotIndex(material->Emission);
    textureData.Shininess = material->Shininess;
    DrawQuad(transform, textureData);
  }

  void Renderer::DrawQuad(Ref<Transform> transform, Ref<SubTexture2D> subTexture, Vec4 &tint)
  {
    TextureData textureData{subTexture->GetTextureCoords(), tint};
    textureData.Texture = GetTextureSlotIndex(subTexture->GetTexture());
    DrawQuad(transform, textureData);
  }

  void Renderer::DrawQuad(Ref<Transform> transform, TextureData &textureData)
  {
    const uint vertex_count = 4;
    const uint index_count = 6;

    Mat4 model = transform->GetModel();
    Mat3 normal = Mat3(glm::transpose(glm::inverse(model)));

    auto &td = textureData;
    VertexData vertices[vertex_count] = {
        {model * QUAD_LOCAL_SPACE_VERTICES[0], normal * QUAD_NORMALS[0], td.Tint, td.TextureCoords[0], td.Texture, td.Specular, td.Emission, td.Shininess},
        {model * QUAD_LOCAL_SPACE_VERTICES[1], normal * QUAD_NORMALS[1], td.Tint, td.TextureCoords[1], td.Texture, td.Specular, td.Emission, td.Shininess},
        {model * QUAD_LOCAL_SPACE_VERTICES[2], normal * QUAD_NORMALS[2], td.Tint, td.TextureCoords[2], td.Texture, td.Specular, td.Emission, td.Shininess},
        {model * QUAD_LOCAL_SPACE_VERTICES[3], normal * QUAD_NORMALS[3], td.Tint, td.TextureCoords[3], td.Texture, td.Specular, td.Emission, td.Shininess},
    };

    uint32 indices[index_count] = {VertexCount, VertexCount + 1, VertexCount + 2, VertexCount + 2, VertexCount + 3, VertexCount + 0};
    AddVertices(&vertices[0], vertex_count, &indices[0], index_count);
  }

#pragma endregion Drawing Quads

#pragma region Drawing Cubes

  void Renderer::DrawCube(Ref<Transform> transform, Vec4 &color)
  {
    TextureData textureData{QUAD_DEFAULT_TEXTURE_COORDS, color};
    DrawCube(transform, textureData);
  }

  void Renderer::DrawCube(Ref<Transform> transform, Ref<Material> material)
  {
    TextureData textureData{QUAD_DEFAULT_TEXTURE_COORDS, material->Tint};
    textureData.Texture = GetTextureSlotIndex(material->Diffuse);
    textureData.Specular = GetTextureSlotIndex(material->Specular);
    textureData.Emission = GetTextureSlotIndex(material->Emission);
    textureData.Shininess = material->Shininess;
    DrawCube(transform, textureData);
  }

  void Renderer::DrawCube(Ref<Transform> transform, Ref<TextureCubemap> cubemap)
  {
    TextureData textureData{QUAD_DEFAULT_TEXTURE_COORDS, REN2D_DEFAULT_COLOR};
    DrawCube(transform, textureData);
  }

  void Renderer::DrawCube(Ref<Transform> transform, Ref<SubTexture2D> subTexture, Vec4 &tint)
  {
    TextureData textureData{subTexture->GetTextureCoords(), tint};
    textureData.Texture = GetTextureSlotIndex(subTexture->GetTexture());
    DrawCube(transform, textureData);
  }

  void Renderer::DrawCube(Ref<Transform> transform, TextureData &textureData)
  {
    const uint vertex_count = 24;
    const uint index_count = 36;

    Mat4 model = transform->GetModel();
    Mat3 normal = Mat3(glm::transpose(glm::inverse(model)));

    auto &td = textureData;
    VertexData vertices[vertex_count] = {
        // Front face
        {model * CUBE_LOCAL_SPACE_VERTICES[0], normal * CUBE_NORMALS[0], td.Tint, td.TextureCoords[0], td.Texture, td.Specular, td.Emission, td.Shininess},
        {model * CUBE_LOCAL_SPACE_VERTICES[1], normal * CUBE_NORMALS[1], td.Tint, td.TextureCoords[1], td.Texture, td.Specular, td.Emission, td.Shininess},
        {model * CUBE_LOCAL_SPACE_VERTICES[2], normal * CUBE_NORMALS[2], td.Tint, td.TextureCoords[2], td.Texture, td.Specular, td.Emission, td.Shininess},
        {model * CUBE_LOCAL_SPACE_VERTICES[3], normal * CUBE_NORMALS[3], td.Tint, td.TextureCoords[3], td.Texture, td.Specular, td.Emission, td.Shininess},

        // Back face
        {model * CUBE_LOCAL_SPACE_VERTICES[4], normal * CUBE_NORMALS[4], td.Tint, td.TextureCoords[0], td.Texture, td.Specular, td.Emission, td.Shininess},
        {model * CUBE_LOCAL_SPACE_VERTICES[5], normal * CUBE_NORMALS[5], td.Tint, td.TextureCoords[1], td.Texture, td.Specular, td.Emission, td.Shininess},
        {model * CUBE_LOCAL_SPACE_VERTICES[6], normal * CUBE_NORMALS[6], td.Tint, td.TextureCoords[2], td.Texture, td.Specular, td.Emission, td.Shininess},
        {model * CUBE_LOCAL_SPACE_VERTICES[7], normal * CUBE_NORMALS[7], td.Tint, td.TextureCoords[3], td.Texture, td.Specular, td.Emission, td.Shininess},

        // Left face
        {model * CUBE_LOCAL_SPACE_VERTICES[8], normal * CUBE_NORMALS[8], td.Tint, td.TextureCoords[0], td.Texture, td.Specular, td.Emission, td.Shininess},
        {model * CUBE_LOCAL_SPACE_VERTICES[9], normal * CUBE_NORMALS[9], td.Tint, td.TextureCoords[1], td.Texture, td.Specular, td.Emission, td.Shininess},
        {model * CUBE_LOCAL_SPACE_VERTICES[10], normal * CUBE_NORMALS[10], td.Tint, td.TextureCoords[2], td.Texture, td.Specular, td.Emission, td.Shininess},
        {model * CUBE_LOCAL_SPACE_VERTICES[11], normal * CUBE_NORMALS[11], td.Tint, td.TextureCoords[3], td.Texture, td.Specular, td.Emission, td.Shininess},

        // Right face
        {model * CUBE_LOCAL_SPACE_VERTICES[12], normal * CUBE_NORMALS[12], td.Tint, td.TextureCoords[0], td.Texture, td.Specular, td.Emission, td.Shininess},
        {model * CUBE_LOCAL_SPACE_VERTICES[13], normal * CUBE_NORMALS[13], td.Tint, td.TextureCoords[1], td.Texture, td.Specular, td.Emission, td.Shininess},
        {model * CUBE_LOCAL_SPACE_VERTICES[14], normal * CUBE_NORMALS[14], td.Tint, td.TextureCoords[2], td.Texture, td.Specular, td.Emission, td.Shininess},
        {model * CUBE_LOCAL_SPACE_VERTICES[15], normal * CUBE_NORMALS[15], td.Tint, td.TextureCoords[3], td.Texture, td.Specular, td.Emission, td.Shininess},
        // Top face
        {model * CUBE_LOCAL_SPACE_VERTICES[16], normal * CUBE_NORMALS[16], td.Tint, td.TextureCoords[0], td.Texture, td.Specular, td.Emission, td.Shininess},
        {model * CUBE_LOCAL_SPACE_VERTICES[17], normal * CUBE_NORMALS[17], td.Tint, td.TextureCoords[1], td.Texture, td.Specular, td.Emission, td.Shininess},
        {model * CUBE_LOCAL_SPACE_VERTICES[18], normal * CUBE_NORMALS[18], td.Tint, td.TextureCoords[2], td.Texture, td.Specular, td.Emission, td.Shininess},
        {model * CUBE_LOCAL_SPACE_VERTICES[19], normal * CUBE_NORMALS[19], td.Tint, td.TextureCoords[3], td.Texture, td.Specular, td.Emission, td.Shininess},

        // Bottom face
        {model * CUBE_LOCAL_SPACE_VERTICES[20], normal * CUBE_NORMALS[20], td.Tint, td.TextureCoords[0], td.Texture, td.Specular, td.Emission, td.Shininess},
        {model * CUBE_LOCAL_SPACE_VERTICES[21], normal * CUBE_NORMALS[21], td.Tint, td.TextureCoords[1], td.Texture, td.Specular, td.Emission, td.Shininess},
        {model * CUBE_LOCAL_SPACE_VERTICES[22], normal * CUBE_NORMALS[22], td.Tint, td.TextureCoords[2], td.Texture, td.Specular, td.Emission, td.Shininess},
        {model * CUBE_LOCAL_SPACE_VERTICES[23], normal * CUBE_NORMALS[23], td.Tint, td.TextureCoords[3], td.Texture, td.Specular, td.Emission, td.Shininess},
    };

    uint32 indices[index_count] = {
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

    AddVertices(&vertices[0], vertex_count, &indices[0], index_count);
  }

#pragma endregion Drawing Cubes

  void Renderer::Reset()
  {
    VertexCount = 0;
    IndexCount = 0;
    TextureSlotIndex = 0;
  }

  void Renderer::BeginScene(Ref<Camera> camera, Ref<Shader> shaderToUse)
  {
    ObjectUniformBuffer->SetData("u_ViewProjection", &camera->GetViewProjection());
    ObjectUniformBuffer->SetData("u_CameraPosition", &camera->GetPosition());

    ShaderInUse = shaderToUse ? shaderToUse : ObjectShader;
    SceneCameraPosition = Vec4(camera->GetPosition(), 1.0f);
    Reset();
  }

  void Renderer::NextBatch()
  {
    Flush();
    Reset();
  }

  void Renderer::Flush()
  {
    if (VertexCount == 0)
      return;

    ShaderInUse->Bind();
    ObjectVertexArray->Bind();

    ObjectVertexBuffer->SetData(Vertices->data(), VertexCount * sizeof(VertexData));
    ObjectIndexBuffer->SetData(Indices->data(), IndexCount);

    auto &textureSlots = *TextureSlots;
    for (int i = 0; i < TextureSlotIndex; i++)
      textureSlots[i]->Bind(i);

    Context->DrawIndices(IndexCount, DrawMode::Triangles);
  }

  void Renderer::EndScene()
  {
    Flush();
  }

  void Renderer::AddVertices(VertexData *vertices, uint vertexCount, uint32 *indices, uint32 indexCount)
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

  int Renderer::GetTextureSlotIndex(Ref<Texture2D> texture)
  {
    int textureSlotIndex = -1;

    if (!texture)
      return textureSlotIndex;

    auto &textureSlots = *TextureSlots;
    for (int i = 0; i < TextureSlotIndex; i++)
    {
      if (textureSlots[i]->GetId() == texture->GetId())
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