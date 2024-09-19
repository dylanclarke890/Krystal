#include <execution>
#include <algorithm>

#include "Renderer.h"
#include "Misc/Time.h"

namespace Krys
{
#pragma region Constants
  constexpr Vec2 QUAD_DEFAULT_TEXTURE_COORDS[] = {{0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}};
  constexpr Vec3 QUAD_SURFACE_NORMALS[] = {{0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}};
  constexpr Vec4 QUAD_LOCAL_SPACE_VERTICES[] = {{-0.5f, -0.5f, 0.0f, 1.0f}, {0.5f, -0.5f, 0.0f, 1.0f}, {0.5f, 0.5f, 0.0f, 1.0f}, {-0.5f, 0.5f, 0.0f, 1.0f}};

  constexpr Vec2 TRIANGLE_DEFAULT_TEXTURE_COORDS[] = {{0.0f, 0.0f}, {0.5f, 1.0f}, {1.0f, 0.0f}};
  constexpr Vec3 TRIANGLE_SURFACE_NORMALS[] = {{0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}};
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
  constexpr Vec3 CUBE_SURFACE_NORMALS[] = {
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

  static float SCREEN_QUAD_VERTICES[] = {
      //       Pos    Tex coords
      -1.0f, 1.0f, 0.0f, 1.0f,
      -1.0f, -1.0f, 0.0f, 0.0f,
      1.0f, -1.0f, 1.0f, 0.0f,
      -1.0f, 1.0f, 0.0f, 1.0f,
      1.0f, -1.0f, 1.0f, 0.0f,
      1.0f, 1.0f, 1.0f, 1.0f};

  constexpr auto AssignOneVertex = [](const Vec4 &position, const Vec3 &surfaceNormal, const TextureData &textureData)
  {
    VertexData vertex;

    vertex.Position = position;
    vertex.Normal = surfaceNormal;
    vertex.Color = textureData.Tint;
    vertex.TextureSlotIndex = textureData.Texture;
    vertex.SpecularTextureSlotIndex = textureData.Specular;
    vertex.EmissionTextureSlotIndex = textureData.Emission;
    vertex.NormalTextureSlotIndex = textureData.Normal;
    vertex.DisplacementTextureSlotIndex = textureData.Displacement;
    vertex.Shininess = textureData.Shininess;

    return vertex;
  };

#pragma endregion Constants

#pragma region Static Member Initialisation

  Ref<GraphicsContext> Renderer::Context;

  Ref<Framebuffer> Renderer::DefaultFramebuffer;
  Ref<Framebuffer> Renderer::DirectionalShadowMapFramebuffer;
  Ref<Framebuffer> Renderer::OmniDirectionalShadowMapFramebuffer;
  Ref<Framebuffer> Renderer::PostProcessingFramebuffer;

  Ref<Shader> Renderer::DefaultShader;
  Ref<Shader> Renderer::DirectionalShadowMapShader;
  Ref<Shader> Renderer::OmniDirectionalShadowMapShader;
  Ref<Shader> Renderer::LightSourceShader;
  Ref<Shader> Renderer::SkyboxShader;
  Ref<Shader> Renderer::PostProcessingShader;
  Ref<Shader> Renderer::ActiveShader;

  Ref<VertexArray> Renderer::DefaultVertexArray;
  Ref<VertexArray> Renderer::PostProcessingVertexArray;
  Ref<VertexArray> Renderer::SkyboxVertexArray;

  Ref<VertexBuffer> Renderer::DefaultVertexBuffer;
  Ref<VertexBuffer> Renderer::PostProcessingVertexBuffer;
  Ref<VertexBuffer> Renderer::SkyboxVertexBuffer;

  Ref<IndexBuffer> Renderer::DefaultIndexBuffer;
  Ref<UniformBuffer> Renderer::SharedUniformBuffer;

  Ref<TextureCubemap> Renderer::SkyboxCubemap;

  Unique<std::array<VertexData, REN2D_MAX_VERTICES>> Renderer::Vertices;
  Unique<std::array<uint32, REN2D_MAX_INDICES>> Renderer::Indices;
  uint Renderer::VertexCount;
  uint Renderer::IndexCount;

  Unique<std::array<Ref<Texture2D>, REN2D_MAX_TEXTURE_SLOTS>> Renderer::TextureSlots;
  int Renderer::TextureSlotIndex;

  Ref<Camera> Renderer::ActiveCamera;
  bool Renderer::IsPostProcessingEnabled;
  bool Renderer::IsWireFrameDrawingEnabled;

  Ref<Transform> Renderer::LightSourceTransform;
  LightManager Renderer::Lights;

#pragma endregion Static Member Initialisation

// TODO: Add `OnEvent` method for resizing framebuffers etc.
#pragma region Lifecycle Methods

  void Renderer::Init(Ref<Window> window, Ref<GraphicsContext> ctx)
  {
    Context = ctx;

    DefaultFramebuffer = Context->CreateFramebuffer(window->GetWidth(), window->GetHeight(), 4);
    DefaultFramebuffer->AddColorAttachment();
    DefaultFramebuffer->AddDepthStencilAttachment();
    KRYS_ASSERT(DefaultFramebuffer->IsComplete(), "DefaultFramebuffer Incomplete", 0);

    PostProcessingFramebuffer = Context->CreateFramebuffer(window->GetWidth(), window->GetHeight(), 1);
    PostProcessingFramebuffer->AddColorAttachment();
    PostProcessingFramebuffer->AddDepthStencilAttachment();
    KRYS_ASSERT(PostProcessingFramebuffer->IsComplete(), "PostProcessingFramebuffer Incomplete", 0);

    const uint SHADOW_MAP_RESOLUTION = 1024;
    DirectionalShadowMapFramebuffer = Context->CreateFramebuffer(SHADOW_MAP_RESOLUTION, SHADOW_MAP_RESOLUTION, 1);
    DirectionalShadowMapFramebuffer->AddDepthAttachment();
    DirectionalShadowMapFramebuffer->DisableReadBuffer();
    DirectionalShadowMapFramebuffer->DisableWriteBuffers();
    KRYS_ASSERT(DirectionalShadowMapFramebuffer->IsComplete(), "DirectionalShadowMapFramebuffer Incomplete", 0);

    OmniDirectionalShadowMapFramebuffer = Context->CreateFramebuffer(SHADOW_MAP_RESOLUTION, SHADOW_MAP_RESOLUTION, 1);
    OmniDirectionalShadowMapFramebuffer->AddDepthCubemapAttachment();
    OmniDirectionalShadowMapFramebuffer->DisableReadBuffer();
    OmniDirectionalShadowMapFramebuffer->DisableWriteBuffers();
    KRYS_ASSERT(OmniDirectionalShadowMapFramebuffer->IsComplete(), "OmniDirectionalShadowMapFramebuffer Incomplete", 0);

    DefaultVertexBuffer = Context->CreateVertexBuffer(sizeof(VertexData) * REN2D_MAX_VERTICES);
    DefaultVertexBuffer->SetLayout({{{ShaderDataType::Float4, "i_Position"},
                                     {ShaderDataType::Float3, "i_Normal"},
                                     {ShaderDataType::Float4, "i_Color"},
                                     {ShaderDataType::Float2, "i_TextureCoord"},
                                     {ShaderDataType::Int, "i_TextureSlot"},
                                     {ShaderDataType::Int, "i_SpecularSlot"},
                                     {ShaderDataType::Int, "i_EmissionSlot"},
                                     {ShaderDataType::Int, "i_NormalSlot"},
                                     {ShaderDataType::Int, "i_DisplacementSlot"},
                                     {ShaderDataType::Float, "i_Shininess"},
                                     {ShaderDataType::Float3, "i_Tangent"}}});

    PostProcessingVertexBuffer = Context->CreateVertexBuffer(SCREEN_QUAD_VERTICES, sizeof(SCREEN_QUAD_VERTICES));
    PostProcessingVertexBuffer->SetLayout({{{ShaderDataType::Float2, "i_Position"},
                                            {ShaderDataType::Float2, "i_TextureCoord"}}});

    DefaultIndexBuffer = Context->CreateIndexBuffer(REN2D_MAX_INDICES);

    DefaultVertexArray = Context->CreateVertexArray();
    DefaultVertexArray->AddVertexBuffer(DefaultVertexBuffer);
    DefaultVertexArray->SetIndexBuffer(DefaultIndexBuffer);

    PostProcessingVertexArray = Context->CreateVertexArray();
    PostProcessingVertexArray->AddVertexBuffer(PostProcessingVertexBuffer);

    const uint32 SHARED_UNIFORM_BUFFER_BINDING = 0;
    SharedUniformBuffer = Context->CreateUniformBuffer(SHARED_UNIFORM_BUFFER_BINDING,
                                                       {{UniformDataType::Mat4, "u_ViewProjection"},
                                                        {UniformDataType::Vec3, "u_CameraPosition"}});

    DefaultShader = Context->CreateShader("shaders/renderer/default.vert", "shaders/renderer/default.frag");
    DirectionalShadowMapShader = Context->CreateShader("shaders/renderer/directional-shadow-map.vert", "shaders/renderer/directional-shadow-map.frag");
    OmniDirectionalShadowMapShader = Context->CreateShader("shaders/renderer/omnidirectional-shadow-map.vert", "shaders/renderer/omnidirectional-shadow-map.frag", "shaders/renderer/omnidirectional-shadow-map.geo");
    LightSourceShader = Context->CreateShader("shaders/renderer/light-source.vert", "shaders/renderer/light-source.frag");
    SkyboxShader = Context->CreateShader("shaders/renderer/skybox.vert", "shaders/renderer/skybox.frag");
    PostProcessingShader = Context->CreateShader("shaders/renderer/post.vert", "shaders/renderer/post.frag");

    Vertices = CreateUnique<std::array<VertexData, REN2D_MAX_VERTICES>>();
    Indices = CreateUnique<std::array<uint32, REN2D_MAX_INDICES>>();

    TextureSlots = CreateUnique<std::array<Ref<Texture2D>, REN2D_MAX_TEXTURE_SLOTS>>();
    int samplers[REN2D_MAX_TEXTURE_SLOTS - 1]{};
    for (uint32 i = 0; i < REN2D_MAX_TEXTURE_SLOTS - 1; i++)
      samplers[i] = i;

    DefaultShader->SetUniform("u_Textures", samplers, REN2D_MAX_TEXTURE_SLOTS - 1);
    PostProcessingShader->SetUniform("u_Textures", samplers, REN2D_MAX_TEXTURE_SLOTS - 1);
    DefaultShader->TrySetUniform("u_CubeDepthMap", 31);

    Lights.Init(Context);
    LightSourceTransform = CreateRef<Transform>(Vec3(0.0f), Vec3(1.0f));

    // TODO: this probably needs moving to the lights manager.
    Mat4 directionalLightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 7.5f);
    Mat4 directionalLightView = glm::lookAt(Vec3(-2.0f, 4.0f, -1.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
    Mat4 directionalLightSpaceMatrix = directionalLightProjection * directionalLightView;
    DirectionalShadowMapShader->TrySetUniform("u_DirectionalLightSpaceMatrix", directionalLightSpaceMatrix);
    DefaultShader->TrySetUniform("u_DirectionalLightSpaceMatrix", directionalLightSpaceMatrix);

    float omniDirectionalShadowMapAspectRatio = static_cast<float>(SHADOW_MAP_RESOLUTION) / static_cast<float>(SHADOW_MAP_RESOLUTION);
    float omniDirectionalShadowMapFarPlane = 25.0f;
    Mat4 omniDirectionalShadowMapProjection = glm::perspective(glm::radians(90.0f), omniDirectionalShadowMapAspectRatio, 1.0f, omniDirectionalShadowMapFarPlane);

    Vec3 lightPos = Vec3(0.0f, 0.0f, 0.0f);
    Mat4 omniDirectionalLightSpaceMatrices[6] = {
        omniDirectionalShadowMapProjection * glm::lookAt(lightPos, lightPos + Vec3(1.0, 0.0, 0.0), Vec3(0.0, -1.0, 0.0)),
        omniDirectionalShadowMapProjection * glm::lookAt(lightPos, lightPos + Vec3(-1.0, 0.0, 0.0), Vec3(0.0, -1.0, 0.0)),
        omniDirectionalShadowMapProjection * glm::lookAt(lightPos, lightPos + Vec3(0.0, 1.0, 0.0), Vec3(0.0, 0.0, 1.0)),
        omniDirectionalShadowMapProjection * glm::lookAt(lightPos, lightPos + Vec3(0.0, -1.0, 0.0), Vec3(0.0, 0.0, -1.0)),
        omniDirectionalShadowMapProjection * glm::lookAt(lightPos, lightPos + Vec3(0.0, 0.0, 1.0), Vec3(0.0, -1.0, 0.0)),
        omniDirectionalShadowMapProjection * glm::lookAt(lightPos, lightPos + Vec3(0.0, 0.0, -1.0), Vec3(0.0, -1.0, 0.0))};

    for (uint i = 0; i < 6; i++)
      OmniDirectionalShadowMapShader->SetUniform("u_ShadowMatrices[" + std::to_string(i) + "]", omniDirectionalLightSpaceMatrices[i]);
    OmniDirectionalShadowMapShader->TrySetUniform("u_FarPlane", omniDirectionalShadowMapFarPlane);

    // TODO: get the light position from the lights uniform buffer
    OmniDirectionalShadowMapShader->TrySetUniform("u_LightPosition", lightPos);
    // TODO: add u_FarPlane as a light property
    DefaultShader->TrySetUniform("u_FarPlane", omniDirectionalShadowMapFarPlane);

    Context->SetDepthTestingEnabled(true);

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
    textureData.Normal = GetTextureSlotIndex(material->Normal);
    textureData.Displacement = GetTextureSlotIndex(material->Displacement);
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
    constexpr auto AssignOneTriangleVertex = [](int index, Mat4 &model, Mat3 &normalMatrix, TextureData &textureData)
    {
      Vec4 position = model * TRIANGLE_LOCAL_SPACE_VERTICES[index];
      Vec3 normal = normalMatrix * TRIANGLE_SURFACE_NORMALS[index];

      VertexData vertex = AssignOneVertex(position, normal, textureData);
      vertex.TextureCoords = textureData.TextureCoords[index];

      return vertex;
    };

    Mat4 model = transform->GetModel();
    Mat3 normalMatrix = Mat3(glm::transpose(glm::inverse(model)));

    const uint vertex_count = TRIANGLE_VERTEX_COUNT;
    VertexData vertices[TRIANGLE_VERTEX_COUNT] = {
        AssignOneTriangleVertex(0, model, normalMatrix, textureData),
        AssignOneTriangleVertex(1, model, normalMatrix, textureData),
        AssignOneTriangleVertex(2, model, normalMatrix, textureData),
    };

    CalcTangentSpace(vertices[0], vertices[1], vertices[2], normalMatrix);

    const uint index_count = TRIANGLE_VERTEX_COUNT;
    uint32 indices[TRIANGLE_VERTEX_COUNT] = {VertexCount, VertexCount + 1, VertexCount + 2};
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
    textureData.Normal = GetTextureSlotIndex(material->Normal);
    textureData.Displacement = GetTextureSlotIndex(material->Displacement);
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
    constexpr auto AssignOneQuadVertex = [](int index, Mat4 &model, Mat3 &normalMatrix, TextureData &textureData)
    {
      Vec4 position = model * QUAD_LOCAL_SPACE_VERTICES[index];
      Vec3 normal = normalMatrix * QUAD_SURFACE_NORMALS[index];

      VertexData vertex = AssignOneVertex(position, normal, textureData);
      vertex.TextureCoords = textureData.TextureCoords[index];

      return vertex;
    };

    Mat4 model = transform->GetModel();
    Mat3 normalMatrix = Mat3(glm::transpose(glm::inverse(model)));

    const uint vertex_count = 4;
    VertexData vertices[vertex_count] = {
        AssignOneQuadVertex(0, model, normalMatrix, textureData),
        AssignOneQuadVertex(1, model, normalMatrix, textureData),
        AssignOneQuadVertex(2, model, normalMatrix, textureData),
        AssignOneQuadVertex(3, model, normalMatrix, textureData),
    };

    const int triangle1[TRIANGLE_VERTEX_COUNT] = {0, 1, 2};
    const int triangle2[TRIANGLE_VERTEX_COUNT] = {2, 3, 0};

#define CALC_TRIANGLE_TANGENT_SPACE(triangle) CalcTangentSpace(vertices[triangle[0]], vertices[triangle[1]], vertices[triangle[2]], normalMatrix)
    CALC_TRIANGLE_TANGENT_SPACE(triangle1);
    CALC_TRIANGLE_TANGENT_SPACE(triangle2);

    const uint index_count = 6;
    uint32 indices[index_count] = {
        VertexCount + triangle1[0], VertexCount + triangle1[1], VertexCount + triangle1[2], // Triangle 1
        VertexCount + triangle2[0], VertexCount + triangle2[1], VertexCount + triangle2[2], // Triangle 2
    };

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
    textureData.Normal = GetTextureSlotIndex(material->Normal);
    textureData.Displacement = GetTextureSlotIndex(material->Displacement);
    textureData.Shininess = material->Shininess;
    DrawCube(transform, textureData);
  }

  void Renderer::DrawCube(Ref<Transform> transform, Ref<TextureCubemap> cubemap)
  {
    // TODO: ?? Implement this you fool (jk love you bitch)
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
    constexpr auto AssignOneCubeVertex = [](int index, int textureCoordIndex, Mat4 &model, Mat3 &normalMatrix, TextureData &textureData)
    {
      Vec4 position = model * CUBE_LOCAL_SPACE_VERTICES[index];
      Vec3 normal = normalMatrix * CUBE_SURFACE_NORMALS[index];

      VertexData vertex = AssignOneVertex(position, normal, textureData);
      vertex.TextureCoords = textureData.TextureCoords[textureCoordIndex];

      return vertex;
    };

    Mat4 model = transform->GetModel();
    Mat3 normalMatrix = Mat3(glm::transpose(glm::inverse(model)));

    const uint vertex_count = 24;
    VertexData vertices[vertex_count] = {
        AssignOneCubeVertex(0, 0, model, normalMatrix, textureData),
        AssignOneCubeVertex(1, 1, model, normalMatrix, textureData),
        AssignOneCubeVertex(2, 2, model, normalMatrix, textureData),
        AssignOneCubeVertex(3, 3, model, normalMatrix, textureData), // Front face

        AssignOneCubeVertex(4, 0, model, normalMatrix, textureData),
        AssignOneCubeVertex(5, 1, model, normalMatrix, textureData),
        AssignOneCubeVertex(6, 2, model, normalMatrix, textureData),
        AssignOneCubeVertex(7, 3, model, normalMatrix, textureData), // Back face

        AssignOneCubeVertex(8, 0, model, normalMatrix, textureData),
        AssignOneCubeVertex(9, 1, model, normalMatrix, textureData),
        AssignOneCubeVertex(10, 2, model, normalMatrix, textureData),
        AssignOneCubeVertex(11, 3, model, normalMatrix, textureData), // Left face

        AssignOneCubeVertex(12, 0, model, normalMatrix, textureData),
        AssignOneCubeVertex(13, 1, model, normalMatrix, textureData),
        AssignOneCubeVertex(14, 2, model, normalMatrix, textureData),
        AssignOneCubeVertex(15, 3, model, normalMatrix, textureData), // Right face

        AssignOneCubeVertex(16, 0, model, normalMatrix, textureData),
        AssignOneCubeVertex(17, 1, model, normalMatrix, textureData),
        AssignOneCubeVertex(18, 2, model, normalMatrix, textureData),
        AssignOneCubeVertex(19, 3, model, normalMatrix, textureData), // Top face

        AssignOneCubeVertex(20, 0, model, normalMatrix, textureData),
        AssignOneCubeVertex(21, 1, model, normalMatrix, textureData),
        AssignOneCubeVertex(22, 2, model, normalMatrix, textureData),
        AssignOneCubeVertex(23, 3, model, normalMatrix, textureData), // Bottom face
    };

    const int frontTriangle1[TRIANGLE_VERTEX_COUNT] = {0, 1, 2};
    const int frontTriangle2[TRIANGLE_VERTEX_COUNT] = {2, 3, 0};
    const int backTriangle1[TRIANGLE_VERTEX_COUNT] = {4, 5, 6};
    const int backTriangle2[TRIANGLE_VERTEX_COUNT] = {6, 7, 4};
    const int leftTriangle1[TRIANGLE_VERTEX_COUNT] = {8, 9, 10};
    const int leftTriangle2[TRIANGLE_VERTEX_COUNT] = {10, 11, 8};
    const int rightTriangle1[TRIANGLE_VERTEX_COUNT] = {12, 13, 14};
    const int rightTriangle2[TRIANGLE_VERTEX_COUNT] = {14, 15, 12};
    const int topTriangle1[TRIANGLE_VERTEX_COUNT] = {16, 17, 18};
    const int topTriangle2[TRIANGLE_VERTEX_COUNT] = {18, 19, 16};
    const int bottomTriangle1[TRIANGLE_VERTEX_COUNT] = {20, 21, 22};
    const int bottomTriangle2[TRIANGLE_VERTEX_COUNT] = {22, 23, 20};

#define CALC_TRIANGLE_TANGENT_SPACE(triangle) CalcTangentSpace(vertices[triangle[0]], vertices[triangle[1]], vertices[triangle[2]], normalMatrix)

    CALC_TRIANGLE_TANGENT_SPACE(frontTriangle1);
    CALC_TRIANGLE_TANGENT_SPACE(frontTriangle2);
    CALC_TRIANGLE_TANGENT_SPACE(backTriangle1);
    CALC_TRIANGLE_TANGENT_SPACE(backTriangle2);
    CALC_TRIANGLE_TANGENT_SPACE(leftTriangle1);
    CALC_TRIANGLE_TANGENT_SPACE(leftTriangle2);
    CALC_TRIANGLE_TANGENT_SPACE(rightTriangle1);
    CALC_TRIANGLE_TANGENT_SPACE(rightTriangle2);
    CALC_TRIANGLE_TANGENT_SPACE(topTriangle1);
    CALC_TRIANGLE_TANGENT_SPACE(topTriangle2);
    CALC_TRIANGLE_TANGENT_SPACE(bottomTriangle1);
    CALC_TRIANGLE_TANGENT_SPACE(bottomTriangle2);

    const uint index_count = 36;
    uint32 indices[index_count] = {
        VertexCount + frontTriangle1[0],
        VertexCount + frontTriangle1[1],
        VertexCount + frontTriangle1[2], // Front face 1
        VertexCount + frontTriangle2[0],
        VertexCount + frontTriangle2[1],
        VertexCount + frontTriangle2[2], // Front face 2

        VertexCount + backTriangle1[0],
        VertexCount + backTriangle1[1],
        VertexCount + backTriangle1[2], // Back face 1
        VertexCount + backTriangle2[0],
        VertexCount + backTriangle2[1],
        VertexCount + backTriangle2[2], // Back face 2

        VertexCount + leftTriangle1[0],
        VertexCount + leftTriangle1[1],
        VertexCount + leftTriangle1[2], // Left face 1
        VertexCount + leftTriangle2[0],
        VertexCount + leftTriangle2[1],
        VertexCount + leftTriangle2[2], // Left face 2

        VertexCount + rightTriangle1[0],
        VertexCount + rightTriangle1[1],
        VertexCount + rightTriangle1[2], // Right face 1
        VertexCount + rightTriangle2[0],
        VertexCount + rightTriangle2[1],
        VertexCount + rightTriangle2[2], // Right face 2

        VertexCount + topTriangle1[0],
        VertexCount + topTriangle1[1],
        VertexCount + topTriangle1[2], // Top face 1
        VertexCount + topTriangle2[0],
        VertexCount + topTriangle2[1],
        VertexCount + topTriangle2[2], // Top face 2

        VertexCount + bottomTriangle1[0],
        VertexCount + bottomTriangle1[1],
        VertexCount + bottomTriangle1[2], // Bottom face 1
        VertexCount + bottomTriangle2[0],
        VertexCount + bottomTriangle2[1],
        VertexCount + bottomTriangle2[2], // Bottom face 2
    };

    AddVertices(&vertices[0], vertex_count, &indices[0], index_count);
  }

#pragma endregion Drawing Cubes

#pragma region Skybox

  void Renderer::SetSkybox(std::array<string, 6> pathsToFaces)
  {
    // TODO: do this better
    KRYS_ASSERT(!SkyboxVertexArray, "Skybox already set", 0);

    float skyboxVertices[108] = {
        // positions
        -1.0f, 1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,

        -1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,

        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,

        -1.0f, 1.0f, -1.0f,
        1.0f, 1.0f, -1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 1.0f};

    SkyboxVertexArray = Context->CreateVertexArray();
    SkyboxVertexBuffer = Context->CreateVertexBuffer(skyboxVertices, sizeof(skyboxVertices));
    SkyboxVertexBuffer->SetLayout(VertexBufferLayout({{ShaderDataType::Float3, "a_Position"}}));
    SkyboxVertexArray->AddVertexBuffer(SkyboxVertexBuffer);

    SkyboxCubemap = Context->CreateTextureCubemap(pathsToFaces);
  }

#pragma endregion Skybox

  void Renderer::SetPostProcessingEnabled(bool enabled)
  {
    IsPostProcessingEnabled = enabled;
  }

  void Renderer::SetWireFrameModeEnabled(bool enabled)
  {
    IsWireFrameDrawingEnabled = enabled;
  }

  void Renderer::BeginScene(Ref<Camera> camera, Ref<Shader> shaderToUse)
  {
    KRYS_ASSERT(camera, "Cannot begin scene with a null camera.", 0);
    ActiveCamera = camera;
    ActiveShader = shaderToUse ? shaderToUse : DefaultShader;

    SharedUniformBuffer->SetData("u_ViewProjection", camera->GetViewProjection());
    SharedUniformBuffer->SetData("u_CameraPosition", camera->GetPosition());

    Reset();
  }

  void Renderer::EndScene()
  {
    Flush();
  }

  void Renderer::Reset()
  {
    VertexCount = 0;
    IndexCount = 0;
    TextureSlotIndex = REN2D_RESERVED_TEXTURE_SLOTS;
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

    auto &textureSlots = *TextureSlots;
    for (int i = REN2D_RESERVED_TEXTURE_SLOTS; i < TextureSlotIndex; i++)
      textureSlots[i]->Bind(i);

    DefaultVertexArray->Bind();
    DefaultVertexBuffer->SetData(Vertices->data(), VertexCount * sizeof(VertexData));
    DefaultIndexBuffer->SetData(Indices->data(), IndexCount);

    if (IsWireFrameDrawingEnabled)
      Context->SetWireframeModeEnabled(true);

    // Depth Passes
    {
      // Directional
      {
        DirectionalShadowMapFramebuffer->Bind();
        Context->SetViewport(DirectionalShadowMapFramebuffer->GetWidth(), DirectionalShadowMapFramebuffer->GetHeight());
        Context->Clear(RenderBuffer::Depth);

        Context->SetFaceCulling(CullMode::Front);
        {
          DirectionalShadowMapShader->Bind();
          Context->DrawIndices(IndexCount, DrawMode::Triangles);
        }
        Context->SetFaceCulling(CullMode::Back);
      }

      // Omnidirectional
      {
        OmniDirectionalShadowMapFramebuffer->Bind();
        Context->SetViewport(OmniDirectionalShadowMapFramebuffer->GetWidth(), OmniDirectionalShadowMapFramebuffer->GetHeight());
        Context->Clear(RenderBuffer::Depth);

        OmniDirectionalShadowMapShader->Bind();
        Context->DrawIndices(IndexCount, DrawMode::Triangles);
      }
    }

    // Geometry Pass
    {
      DefaultFramebuffer->Bind();

      Context->SetViewport(DefaultFramebuffer->GetWidth(), DefaultFramebuffer->GetHeight());
      Context->Clear(RenderBuffer::All);

      ActiveShader->Bind();
      DirectionalShadowMapFramebuffer->GetDepthAttachment()->Bind(0);
      OmniDirectionalShadowMapFramebuffer->GetDepthAttachment()->Bind(31);

      Context->DrawIndices(IndexCount, DrawMode::Triangles);
    }

    // Draw Lights
    {
      LightSourceShader->Bind();
      Reset();

      for (auto pointLight : Renderer::Lights.GetPointLights())
      {
        if (!pointLight.Enabled)
          continue;
        LightSourceTransform->Position = pointLight.Position;
        Renderer::DrawCube(LightSourceTransform, Colors::Blue);
      }

      for (auto spotLight : Renderer::Lights.GetSpotLights())
      {
        if (!spotLight.Enabled)
          continue;
        LightSourceTransform->Position = spotLight.Position;
        Renderer::DrawCube(LightSourceTransform, Colors::Yellow);
      }

      DefaultVertexBuffer->SetData(Vertices->data(), VertexCount * sizeof(VertexData));
      DefaultIndexBuffer->SetData(Indices->data(), IndexCount);
      Context->DrawIndices(IndexCount, DrawMode::Triangles);
    }

    // Draw Skybox
    if (SkyboxCubemap)
    {
      // TODO: save and restore the depth test func that's set before we draw the skybox
      auto view = Mat4(Mat3(ActiveCamera->GetView()));
      auto viewProjection = ActiveCamera->GetProjection() * view;
      Context->SetDepthTestFunc(DepthTestFunc::EqualOrLess);
      {
        SkyboxVertexArray->Bind();
        SkyboxCubemap->Bind();
        SkyboxShader->Bind();
        SkyboxShader->SetUniform("u_ViewProjection", viewProjection);
        Context->DrawVertices(36);
      }
      Context->SetDepthTestFunc(DepthTestFunc::Less);
    }

    if (IsWireFrameDrawingEnabled)
      Context->SetWireframeModeEnabled(false);

    // Post Processing / Output to Screen
    DefaultFramebuffer->Unbind();
    if (IsPostProcessingEnabled)
    {
      DefaultFramebuffer->BlitTo(PostProcessingFramebuffer,
                                 DefaultFramebuffer->GetWidth(), DefaultFramebuffer->GetHeight(),
                                 RenderBuffer::All);

      PostProcessingShader->Bind();
      PostProcessingVertexArray->Bind();

      PostProcessingFramebuffer->GetColorAttachment()->Bind(0);
      Context->DrawVertices(6, DrawMode::Triangles);
    }
    else
    {
      DefaultFramebuffer->BlitToScreen(DefaultFramebuffer->GetWidth(), DefaultFramebuffer->GetHeight(),
                                       RenderBuffer::All);
    }
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

  /* Adds a new texture to the current batch or retrieves it's index if it already exists. NOT to be used for reserved texture slots.*/
  int Renderer::GetTextureSlotIndex(Ref<Texture2D> texture)
  {
    // TODO: rework the reserved texture slots logic, this approach seems buggy af
    int textureSlotIndex = -1;

    if (!texture)
      return textureSlotIndex;

    auto &textureSlots = *TextureSlots;
    for (int i = REN2D_RESERVED_TEXTURE_SLOTS; i < TextureSlotIndex; i++)
    {
      if (textureSlots[i]->GetId() == texture->GetId())
      {
        textureSlotIndex = i;
        break;
      }
    }

    if (textureSlotIndex == -1)
    {
      if (TextureSlotIndex == REN2D_MAX_TEXTURE_SLOTS - (1 + REN2D_RESERVED_TEXTURE_SLOTS))
      {
        NextBatch();
      }
      textureSlotIndex = TextureSlotIndex++;
      textureSlots[textureSlotIndex] = texture;
    }

    return textureSlotIndex;
  }
}
