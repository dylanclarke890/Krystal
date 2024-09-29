#include "Renderer.h"
#include "Misc/Time.h"

namespace Krys
{
  constexpr auto AssignOneVertex = [](const Vec4 &position, const Vec3 &surfaceNormal, const TextureData &textureData)
  {
    VertexData vertex{};

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

#pragma region Static Member Initialisation

  Ref<GraphicsContext> Renderer::Context;
  Ref<Window> Renderer::AppWindow;

  RendererFramebuffers Renderer::Framebuffers;
  RendererShaders Renderer::Shaders;
  Ref<Shader> Renderer::ActiveShader;

  Ref<VertexArray> Renderer::DefaultVertexArray;
  Ref<VertexArray> Renderer::ScreenQuadVertexArray;
  Ref<VertexArray> Renderer::SkyboxVertexArray;

  Ref<VertexBuffer> Renderer::DefaultVertexBuffer;
  Ref<VertexBuffer> Renderer::ScreenQuadVertexBuffer;
  Ref<VertexBuffer> Renderer::SkyboxVertexBuffer;

  Ref<IndexBuffer> Renderer::DefaultIndexBuffer;
  Ref<UniformBuffer> Renderer::SharedUniformBuffer;

  Ref<TextureCubemap> Renderer::SkyboxCubemap;

  Unique<std::array<VertexData, RENDERER_MAX_VERTICES>> Renderer::Vertices;
  Unique<std::array<uint32, RENDERER_MAX_INDICES>> Renderer::Indices;
  uint Renderer::VertexCount;
  uint Renderer::IndexCount;

  Ref<ActiveTextureUnits> Renderer::TextureUnits;

  Ref<Camera> Renderer::ActiveCamera;
  bool Renderer::IsPostProcessingEnabled;
  bool Renderer::IsWireFrameDrawingEnabled;

  LightManager Renderer::Lights;

  RenderMode Renderer::CurrentRenderMode;
  DeferredRendererData Renderer::DeferredRenderer;

#pragma endregion Static Member Initialisation

// TODO: Add `OnEvent` method for resizing framebuffers etc.
#pragma region Lifecycle Methods

  void Renderer::Init(Ref<Window> window, Ref<GraphicsContext> ctx)
  {
    Context = ctx;
    AppWindow = window;

    Vertices = CreateUnique<std::array<VertexData, RENDERER_MAX_VERTICES>>();
    Indices = CreateUnique<std::array<uint32, RENDERER_MAX_INDICES>>();

    InitTextureUnits();
    Lights.Init(Context, TextureUnits);

    InitShaders();
    InitDeferredRenderer();
    InitFramebuffers();
    InitBuffers();
    InitVertexArrays();
    Reset();

    Context->SetDepthTestingEnabled(true);
    CurrentRenderMode = RenderMode::Forward;
  }

  void Renderer::Shutdown()
  {
    // Everything is static and will get cleaned up when the program terminates, nothing needed for now.
  }

#pragma endregion Lifecycle Methods

#pragma region Init Helpers

  void Renderer::InitTextureUnits()
  {
    const int TOTAL_MAX_SLOTS = Context->QueryCapabilities().MaxTextureImageUnits;
    auto max2DSamplers = TOTAL_MAX_SLOTS - static_cast<int>(CUBEMAP_SLOTS);

    std::vector<int> samplers2D(max2DSamplers);
    for (int i = 0; i < max2DSamplers; i++)
      samplers2D[i] = i;

    std::vector<int> samplersCubemap(CUBEMAP_SLOTS);
    for (int i = 0; i < static_cast<int>(CUBEMAP_SLOTS); i++)
      samplersCubemap[i] = max2DSamplers + i;

    TextureUnits = CreateRef<ActiveTextureUnits>();
    TextureUnits->Texture2D.NextSlotIndex = 0;
    TextureUnits->Texture2D.MaxSlots = max2DSamplers;
    TextureUnits->Texture2D.ReservedSlots = LIGHTING_MAX_DIRECTIONAL_SHADOW_CASTERS + LIGHTING_MAX_SPOT_LIGHT_SHADOW_CASTERS;
    TextureUnits->Texture2D.SlotIndices = samplers2D;
    TextureUnits->Texture2D.Slots = std::vector<Ref<Texture>>{static_cast<size_t>(TextureUnits->Texture2D.MaxSlots)};

    TextureUnits->TextureCubemap.NextSlotIndex = 0;
    TextureUnits->TextureCubemap.MaxSlots = CUBEMAP_SLOTS;
    TextureUnits->TextureCubemap.ReservedSlots = LIGHTING_MAX_POINT_LIGHT_SHADOW_CASTERS;
    TextureUnits->TextureCubemap.SlotIndices = samplersCubemap;
    TextureUnits->TextureCubemap.Slots = std::vector<Ref<Texture>>{static_cast<size_t>(TextureUnits->TextureCubemap.MaxSlots)};
  }

  void Renderer::InitShaders()
  {
    Shaders = {};
    Shaders.Default = Context->CreateShader("shaders/renderer/default.vert", "shaders/renderer/default.frag");
    Shaders.DirectionalShadowMap = Context->CreateShader("shaders/renderer/directional-shadow-map.vert", "shaders/renderer/empty.frag");
    Shaders.PointLightShadowMap = Context->CreateShader("shaders/renderer/point-light-shadow-map.vert", "shaders/renderer/point-light-shadow-map.frag", "shaders/renderer/point-light-shadow-map.geo");
    Shaders.SpotLightShadowMap = Context->CreateShader("shaders/renderer/spot-light-shadow-map.vert", "shaders/renderer/empty.frag");
    Shaders.LightSource = Context->CreateShader("shaders/renderer/light-source.vert", "shaders/renderer/light-source.frag");
    Shaders.Skybox = Context->CreateShader("shaders/renderer/skybox.vert", "shaders/renderer/skybox.frag");
    Shaders.PostProcessing = Context->CreateShader("shaders/renderer/post.vert", "shaders/renderer/post.frag");
    Shaders.ExtractBrightness = Context->CreateShader("shaders/renderer/screen-quad.vert", "shaders/renderer/extract-brightness.frag");
    Shaders.GaussianBlur = Context->CreateShader("shaders/renderer/screen-quad.vert", "shaders/effects/gaussian-blur.frag");

    TextureUnits->SetSamplerUniforms({Shaders.Default, Shaders.PostProcessing});
  }

  void Renderer::InitDeferredRenderer()
  {
    auto gBuffer = Context->CreateFramebuffer(AppWindow->GetWidth(), AppWindow->GetHeight());
    auto gPosition = gBuffer->AddColorAttachment(TextureInternalFormat::RGBA16F);
    auto gNormal = gBuffer->AddColorAttachment(TextureInternalFormat::RGBA16F);
    auto gAlbedoSpec = gBuffer->AddColorAttachment(TextureInternalFormat::RGBA);
    gBuffer->SetWriteBuffers({0, 1, 2});
    gBuffer->AddDepthAttachment();

    KRYS_ASSERT(gBuffer->IsComplete(), "GBuffer is incomplete!", 0);

    DeferredRenderer = DeferredRendererData{gBuffer, gPosition, gNormal, gAlbedoSpec};
  }

  void Renderer::InitFramebuffers()
  {
    Framebuffers = {};

    Framebuffers.MultiSample = Context->CreateFramebuffer(AppWindow->GetWidth(), AppWindow->GetHeight(), 4);
    Framebuffers.MultiSample->AddColorAttachment(TextureInternalFormat::RGBA16F);
    Framebuffers.MultiSample->AddDepthStencilAttachment();
    KRYS_ASSERT(Framebuffers.MultiSample->IsComplete(), "MultiSampleFramebuffer Incomplete", 0);

    Framebuffers.SingleSample = Context->CreateFramebuffer(AppWindow->GetWidth(), AppWindow->GetHeight(), 1);
    Framebuffers.SingleSample->AddColorAttachment(TextureInternalFormat::RGBA16F);
    Framebuffers.SingleSample->AddDepthStencilAttachment();
    KRYS_ASSERT(Framebuffers.SingleSample->IsComplete(), "SingleSampleFramebuffer Incomplete", 0);

    Framebuffers.ExtractBrightness = Context->CreateFramebuffer(AppWindow->GetWidth(), AppWindow->GetHeight(), 1);
    Framebuffers.ExtractBrightness->AddColorAttachment(TextureInternalFormat::RGBA16F);
    KRYS_ASSERT(Framebuffers.ExtractBrightness->IsComplete(), "ExtractBrightnessFramebuffer Incomplete", 0);

    Framebuffers.PostProcessing = Context->CreateFramebuffer(AppWindow->GetWidth(), AppWindow->GetHeight(), 1);
    Framebuffers.PostProcessing->AddColorAttachment(TextureInternalFormat::RGBA16F);
    KRYS_ASSERT(Framebuffers.PostProcessing->IsComplete(), "PostProcessingFramebuffer Incomplete", 0);

    Framebuffers.DirectionalShadowMap = Context->CreateFramebuffer(LIGHTING_DEFAULT_SHADOW_MAP_RESOLUTION, LIGHTING_DEFAULT_SHADOW_MAP_RESOLUTION, 1);
    Framebuffers.DirectionalShadowMap->AddDepthAttachment();
    Framebuffers.DirectionalShadowMap->DisableReadBuffer();
    Framebuffers.DirectionalShadowMap->DisableWriteBuffers();
    KRYS_ASSERT(Framebuffers.DirectionalShadowMap->IsComplete(), "DirectionalShadowMapFramebuffer Incomplete", 0);

    Framebuffers.SpotLightShadowMap = Context->CreateFramebuffer(LIGHTING_DEFAULT_SHADOW_MAP_RESOLUTION, LIGHTING_DEFAULT_SHADOW_MAP_RESOLUTION, 1);
    Framebuffers.SpotLightShadowMap->AddDepthAttachment();
    Framebuffers.SpotLightShadowMap->DisableReadBuffer();
    Framebuffers.SpotLightShadowMap->DisableWriteBuffers();
    KRYS_ASSERT(Framebuffers.SpotLightShadowMap->IsComplete(), "SpotLightShadowMapFramebuffer Incomplete", 0);

    Framebuffers.PointLightShadowMap = Context->CreateFramebuffer(LIGHTING_DEFAULT_SHADOW_MAP_RESOLUTION, LIGHTING_DEFAULT_SHADOW_MAP_RESOLUTION, 1);
    Framebuffers.PointLightShadowMap->AddDepthCubemapAttachment();
    Framebuffers.PointLightShadowMap->DisableReadBuffer();
    Framebuffers.PointLightShadowMap->DisableWriteBuffers();
    KRYS_ASSERT(Framebuffers.PointLightShadowMap->IsComplete(), "PointLightShadowMapFramebuffer Incomplete", 0);

    TextureUnits->Texture2D.Slots[RESERVED_TEXTURE_SLOT__DIRECTIONAL_SHADOW_MAP] = Framebuffers.DirectionalShadowMap->GetDepthAttachment();
    TextureUnits->Texture2D.Slots[RESERVED_TEXTURE_SLOT__SPOT_LIGHT_SHADOW_MAP] = Framebuffers.SpotLightShadowMap->GetDepthAttachment();

    TextureUnits->TextureCubemap.Slots[RESERVED_TEXTURE_SLOT__POINT_LIGHT_SHADOW_CUBEMAP] = Framebuffers.PointLightShadowMap->GetDepthAttachment();

    {
      auto pingPongBufferA = Context->CreateFramebuffer(AppWindow->GetWidth(), AppWindow->GetHeight());
      auto pingPongBufferB = Context->CreateFramebuffer(AppWindow->GetWidth(), AppWindow->GetHeight());

      pingPongBufferA->AddColorAttachment(TextureInternalFormat::RGBA16F);
      pingPongBufferB->AddColorAttachment(TextureInternalFormat::RGBA16F);

      Framebuffers.GaussianBlur = Context->CreatePingPongFramebuffer(pingPongBufferA, pingPongBufferB);
      KRYS_ASSERT(Framebuffers.GaussianBlur->IsComplete(), "GaussianBlurFramebuffer Incomplete", 0);

      Framebuffers.GaussianBlur->SetBeforeRenderPassesCallback([&]()
                                                               { Shaders.GaussianBlur->Bind(); });

      bool horizontal = false;
      Framebuffers.GaussianBlur->SetRenderStepCallback([&]()
                                                       { Shaders.GaussianBlur->SetUniform("u_BlurHorizontally", horizontal);
                                                       Context->DrawVertices(6, DrawMode::Triangles);
                                                       horizontal = !horizontal; });
    }
  }

  void Renderer::InitBuffers()
  {
    DefaultVertexBuffer = Context->CreateVertexBuffer(sizeof(VertexData) * RENDERER_MAX_VERTICES);
    DefaultVertexBuffer->SetLayout(VERTEX_BUFFER_LAYOUT_DEFAULT);
    DefaultIndexBuffer = Context->CreateIndexBuffer(RENDERER_MAX_INDICES);

    ScreenQuadVertexBuffer = Context->CreateVertexBuffer(SCREEN_QUAD_VERTICES, sizeof(SCREEN_QUAD_VERTICES));
    ScreenQuadVertexBuffer->SetLayout(VERTEX_BUFFER_LAYOUT_SCREEN);

    SharedUniformBuffer = Context->CreateUniformBuffer(UNIFORM_BUFFER_BINDING_SHARED, UNIFORM_BUFFER_LAYOUT_SHARED);
  }

  void Renderer::InitVertexArrays()
  {
    DefaultVertexArray = Context->CreateVertexArray();
    DefaultVertexArray->AddVertexBuffer(DefaultVertexBuffer);
    DefaultVertexArray->SetIndexBuffer(DefaultIndexBuffer);

    ScreenQuadVertexArray = Context->CreateVertexArray();
    ScreenQuadVertexArray->AddVertexBuffer(ScreenQuadVertexBuffer);
  }

#pragma endregion Init Helpers

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
    TextureData textureData{QUAD_DEFAULT_TEXTURE_COORDS, RENDERER_DEFAULT_OBJECT_COLOR};
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
    ActiveShader = shaderToUse ? shaderToUse : Shaders.Default;

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
    TextureUnits->Reset();
    VertexCount = 0;
    IndexCount = 0;
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

    switch (CurrentRenderMode)
    {
    case RenderMode::Forward:
    {
      ForwardRender();
      break;
    }
    case RenderMode::Deferred:
    {
      DeferredRender();
      break;
    }
    default:
    {
      KRYS_ASSERT(false, "Unknown RenderMode", 0);
      break;
    }
    }
  }

  void Renderer::ForwardRender()
  {
    TextureUnits->Bind();
    TextureUnits->UnbindReserved();

    DefaultVertexArray->Bind();
    DefaultVertexBuffer->SetData(Vertices->data(), VertexCount * sizeof(VertexData));
    DefaultIndexBuffer->SetData(Indices->data(), IndexCount);

    if (IsWireFrameDrawingEnabled)
      Context->SetWireframeModeEnabled(true);

    // Depth Passes
    {
      // Directional
      {
        Framebuffers.DirectionalShadowMap->Bind();
        Context->SetViewport(Framebuffers.DirectionalShadowMap->GetWidth(), Framebuffers.DirectionalShadowMap->GetHeight());
        Context->Clear(RenderBuffer::Depth);

        Context->SetFaceCulling(CullMode::Front);
        {
          Shaders.DirectionalShadowMap->Bind();
          Context->DrawIndices(IndexCount, DrawMode::Triangles);
        }
        Context->SetFaceCulling(CullMode::Back);
      }

      // Point Light
      {
        Framebuffers.PointLightShadowMap->Bind();
        Context->SetViewport(Framebuffers.PointLightShadowMap->GetWidth(), Framebuffers.PointLightShadowMap->GetHeight());
        Context->Clear(RenderBuffer::Depth);

        Shaders.PointLightShadowMap->Bind();
        Context->DrawIndices(IndexCount, DrawMode::Triangles);
      }

      // Spot Light
      {
        Framebuffers.SpotLightShadowMap->Bind();
        Context->SetViewport(Framebuffers.SpotLightShadowMap->GetWidth(), Framebuffers.SpotLightShadowMap->GetHeight());
        Context->Clear(RenderBuffer::Depth);

        Shaders.SpotLightShadowMap->Bind();
        Context->DrawIndices(IndexCount, DrawMode::Triangles);
      }
    }

    TextureUnits->BindReserved();

    // Geometry Pass
    {
      Framebuffers.MultiSample->Bind();
      Context->SetViewport(Framebuffers.MultiSample->GetWidth(), Framebuffers.MultiSample->GetHeight());
      Context->Clear(RenderBuffer::All);

      ActiveShader->Bind();
      Context->DrawIndices(IndexCount, DrawMode::Triangles);
    }

    // Draw Lights
    {
      Shaders.LightSource->Bind();
      Reset();

      static Ref<Transform> LightSourceTransform = CreateRef<Transform>(Vec3(0.0f), Vec3(0.1f));

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

      if (IndexCount > 0)
      {
        DefaultVertexBuffer->SetData(Vertices->data(), VertexCount * sizeof(VertexData));
        DefaultIndexBuffer->SetData(Indices->data(), IndexCount);
        Context->DrawIndices(IndexCount, DrawMode::Triangles);
      }
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
        Shaders.Skybox->Bind();
        Shaders.Skybox->SetUniform("u_ViewProjection", viewProjection);
        Context->DrawVertices(36);
      }
      Context->SetDepthTestFunc(DepthTestFunc::Less);
    }

    // Otherwise we incorrectly render the screen quad in wireframe mode
    if (IsWireFrameDrawingEnabled)
      Context->SetWireframeModeEnabled(false);

    // Post Processing / Output to Screen
    if (IsPostProcessingEnabled)
    {
      ScreenQuadVertexArray->Bind();

      // Resolve multi sampled content
      Framebuffers.MultiSample->BlitTo(Framebuffers.SingleSample,
                                       Framebuffers.MultiSample->GetWidth(), Framebuffers.MultiSample->GetHeight(),
                                       RenderBuffer::All);

      // Collect brightness info
      Framebuffers.ExtractBrightness->Bind();
      Context->SetViewport(Framebuffers.ExtractBrightness->GetWidth(), Framebuffers.ExtractBrightness->GetHeight());
      Framebuffers.ExtractBrightness->Bind();
      Framebuffers.SingleSample->GetColorAttachment()->Bind();
      Context->DrawVertices(6, DrawMode::Triangles);

      Context->SetViewport(Framebuffers.GaussianBlur->GetWidth(), Framebuffers.GaussianBlur->GetHeight());
      auto blurredBrightness = Framebuffers.GaussianBlur->ExecutePasses(Framebuffers.ExtractBrightness->GetColorAttachment(), 10);

      // Composite/output
      Context->BindScreenFramebuffer(FramebufferBindType::Draw);
      Context->SetViewport(AppWindow->GetWidth(), AppWindow->GetHeight());
      Framebuffers.SingleSample->GetColorAttachment()->Bind();
      blurredBrightness->Bind(1);
      Shaders.PostProcessing->Bind();
      Context->DrawVertices(6, DrawMode::Triangles);
    }
    else
    {
      Context->BindScreenFramebuffer();
      Framebuffers.MultiSample->BlitToScreen(Framebuffers.MultiSample->GetWidth(), Framebuffers.MultiSample->GetHeight(), RenderBuffer::All);
    }
  }

  void Renderer::DeferredRender()
  {
  }

  void Renderer::AddVertices(VertexData *vertices, uint vertexCount, uint32 *indices, uint32 indexCount)
  {
    if (VertexCount + vertexCount >= RENDERER_MAX_VERTICES || IndexCount + indexCount >= RENDERER_MAX_INDICES)
    {
      NextBatch();
    }

    auto &vertexBuffer = *Vertices;
    for (uint i = 0; i < vertexCount; i++)
      vertexBuffer[VertexCount++] = vertices[i];

    auto &indexBuffer = *Indices;
    for (uint i = 0; i < indexCount; i++)
      indexBuffer[IndexCount++] = indices[i];
  }

  int Renderer::GetTextureSlotIndex(Ref<Texture2D> texture)
  {
    return GetTextureSlotIndex(texture, TextureUnits->Texture2D);
  }

  int Renderer::GetTextureSlotIndex(Ref<TextureCubemap> texture)
  {
    return GetTextureSlotIndex(texture, TextureUnits->TextureCubemap);
  }

  int Renderer::GetTextureSlotIndex(Ref<Texture> texture, TextureBindingInfo &bindingInfo)
  {
    int index = -1;
    if (!texture)
      return index; // Texture can be null, no need to assert here.

    for (int i = bindingInfo.ReservedSlots; i < bindingInfo.NextSlotIndex; i++)
    {
      if (texture->GetId() == bindingInfo.Slots[i]->GetId())
      {
        index = i;
        break;
      }
    }

    if (index == -1)
    {
      if (!bindingInfo.HasSlotsRemaining())
      {
        NextBatch();
      }

      index = bindingInfo.NextSlotIndex++;
      bindingInfo.Slots[index] = texture;
    }

    return index;
  }
}
