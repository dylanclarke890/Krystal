#pragma once

#include <array>

#include "Core.h"
#include "Window.h"
#include "Graphics/Graphics.h"
#include "Graphics/GraphicsContext.h"
#include "Graphics/Colors.h"
#include "Graphics/Camera/Camera.h"
#include "Graphics/Camera/Orthographic.h"
#include "Graphics/Transform.h"
#include "Graphics/Mesh.h"
#include "Graphics/LightManager.h"

namespace Krys
{
  inline static void CalcTangentSpace(VertexData &v1, VertexData &v2, VertexData &v3, Mat3 &normalMatrix) noexcept
  {
    Vec3 edge1 = v2.Position - v1.Position;
    Vec3 edge2 = v3.Position - v1.Position;

    Vec2 deltaUV1 = v2.TextureCoords - v1.TextureCoords;
    Vec2 deltaUV2 = v3.TextureCoords - v1.TextureCoords;

    float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

    Vec3 tangent;
    tangent.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
    tangent.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
    tangent.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);

    tangent = glm::normalize(normalMatrix * tangent);

    v1.Tangent = tangent;
    v2.Tangent = tangent;
    v3.Tangent = tangent;
  }

  struct RendererFramebuffers
  {
    Ref<Framebuffer> MultiSample, SingleSample,
        DirectionalShadowMap, OmniDirectionalShadowMap,
        ExtractBrightness, PostProcessing;

    Ref<PingPongFramebuffer> GaussianBlur;
  };

  struct RendererShaders
  {
    Ref<Shader> Default, DirectionalShadowMap, OmniDirectionalShadowMap,
        LightSource, Skybox, PostProcessing, ExtractBrightness, GaussianBlur;
  };

  class Renderer
  {
  private:
    static Ref<GraphicsContext> Context;
    static Ref<Window> AppWindow;
    static RendererFramebuffers Framebuffers;
    static RendererShaders Shaders;
    static Ref<Shader> ActiveShader;
    static Ref<VertexArray> DefaultVertexArray, ScreenQuadVertexArray, SkyboxVertexArray;
    static Ref<VertexBuffer> DefaultVertexBuffer, ScreenQuadVertexBuffer, SkyboxVertexBuffer;
    static Ref<IndexBuffer> DefaultIndexBuffer;
    static Ref<UniformBuffer> SharedUniformBuffer;
    static Ref<TextureCubemap> SkyboxCubemap;

    static Unique<std::array<VertexData, RENDERER_MAX_VERTICES>> Vertices;
    static Unique<std::array<uint32, RENDERER_MAX_INDICES>> Indices;
    static uint VertexCount, IndexCount;

    static ActiveTextureUnits TextureUnits;

    static Ref<Camera> ActiveCamera;
    static bool IsPostProcessingEnabled, IsWireFrameDrawingEnabled;

    static DeferredRendererData DeferredRenderer;
    static RenderMode CurrentRenderMode;

  public:
    static LightManager Lights;

    static void Init(Ref<Window> window, Ref<GraphicsContext> ctx);
    static void Shutdown();

    static void DrawTriangle(Ref<Transform> transform, Vec4 &color);
    static void DrawTriangle(Ref<Transform> transform, Ref<Material> material);
    static void DrawTriangle(Ref<Transform> transform, Ref<SubTexture2D> subTexture, Vec4 &tint = RENDERER_DEFAULT_OBJECT_COLOR);

    static void DrawQuad(Ref<Transform> transform, Vec4 &color);
    static void DrawQuad(Ref<Transform> transform, Ref<Material> material);
    static void DrawQuad(Ref<Transform> transform, Ref<SubTexture2D> subTexture, Vec4 &tint = RENDERER_DEFAULT_OBJECT_COLOR);

    static void DrawCube(Ref<Transform> transform, Vec4 &color);
    static void DrawCube(Ref<Transform> transform, Ref<Material> material);
    static void DrawCube(Ref<Transform> transform, Ref<TextureCubemap> cubemap);
    static void DrawCube(Ref<Transform> transform, Ref<SubTexture2D> subTexture, Vec4 &tint = RENDERER_DEFAULT_OBJECT_COLOR);

    static void SetSkybox(std::array<string, 6> pathsToFaces);
    static void SetPostProcessingEnabled(bool enabled);
    static void SetWireFrameModeEnabled(bool enabled);

    static void BeginScene(Ref<Camera> camera, Ref<Shader> shaderToUse = nullptr);
    static void NextBatch();
    static void EndScene();

  private:
    static void InitFramebuffers();
    static void InitShaders();
    static void InitBuffers();
    static void InitVertexArrays();
    static void InitLighting();
    static void InitDeferredRenderer();
    static void InitTextureUnits();

    static void Reset();
    static void Flush();
    static void ForwardRender();
    static void DeferredRender();

    static void DrawQuad(Ref<Transform> transform, TextureData &textureData);
    static void DrawTriangle(Ref<Transform> transform, TextureData &textureData);
    static void DrawCube(Ref<Transform> transform, TextureData &textureData);

    static void AddVertices(VertexData *vertices, uint vertexCount, uint32 *indices, uint32 indexCount);

    static int GetTextureSlotIndex(Ref<Texture2D> texture);
    static int GetTextureSlotIndex(Ref<TextureCubemap> texture);
    static int GetTextureSlotIndex(Ref<Texture> texture, TextureBindingInfo &bindingInfo);
  };
}