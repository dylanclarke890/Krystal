#pragma once

#include <array>

#include "Core.h"
#include "Window.h"
#include "Graphics/GraphicsContext.h"
#include "Graphics/Colors.h"
#include "Graphics/Camera/Camera.h"
#include "Graphics/Camera/Orthographic.h"
#include "Graphics/Transform.h"
#include "Graphics/Mesh.h"
#include "Graphics/Lighting/LightManager.h"

namespace Krys
{
  constexpr uint REN2D_MAX_TRIANGLES = 10000;
  constexpr uint REN2D_MAX_QUADS = REN2D_MAX_TRIANGLES / 2;
  constexpr uint REN2D_MAX_VERTICES = REN2D_MAX_QUADS * 4;
  constexpr uint REN2D_MAX_INDICES = REN2D_MAX_QUADS * 6;
  constexpr uint REN2D_MAX_TEXTURE_SLOTS = 32; // TODO: get this from the graphics API.
  constexpr uint REN2D_RESERVED_TEXTURE_SLOTS = 1;
  static Vec4 REN2D_DEFAULT_COLOR = {1.0f, 1.0f, 1.0f, 1.0f};

  struct VertexData
  {
    Vec4 Position;
    Vec3 Normal;
    Vec4 Color;
    Vec2 TextureCoords;
    int TextureSlotIndex;
    int SpecularTextureSlotIndex;
    int EmissionTextureSlotIndex;
    float Shininess;
  };

  class Renderer
  {
  private:
    struct TextureData
    {
      const Vec2 *TextureCoords;
      Vec4 Tint;
      int Texture = -1;
      int Specular = -1;
      int Emission = -1;
      float Shininess = 32.0f;
    };

    static Ref<GraphicsContext> Context;
    static Ref<Framebuffer> DefaultFramebuffer, DepthPassFramebuffer, PostProcessingFramebuffer;
    static Ref<Shader> DefaultShader, DepthPassShader, LightSourceShader, SkyboxShader, PostProcessingShader;
    static Ref<VertexArray> DefaultVertexArray, PostProcessingVertexArray, SkyboxVertexArray;
    static Ref<VertexBuffer> DefaultVertexBuffer, PostProcessingVertexBuffer, SkyboxVertexBuffer;
    static Ref<IndexBuffer> DefaultIndexBuffer;
    static Ref<UniformBuffer> SharedUniformBuffer;
    static Ref<TextureCubemap> SkyboxCubemap;

    static Unique<std::array<VertexData, REN2D_MAX_VERTICES>> Vertices;
    static Unique<std::array<uint32, REN2D_MAX_INDICES>> Indices;
    static uint VertexCount, IndexCount;

    static Unique<std::array<Ref<Texture2D>, REN2D_MAX_TEXTURE_SLOTS>> TextureSlots;
    static int TextureSlotIndex;

    static Ref<Shader> ActiveShader;
    static Ref<Camera> ActiveCamera;
    static Mat4 DirectionalLightSpaceMatrix;
    static bool IsPostProcessingEnabled, IsWireFrameDrawingEnabled;

    static Ref<Transform> LightSourceTransform;

  public:
    static LightManager Lights;

    static void Init(Ref<Window> window, Ref<GraphicsContext> ctx);
    static void Shutdown();

    static void DrawTriangle(Ref<Transform> transform, Vec4 &color);
    static void DrawTriangle(Ref<Transform> transform, Ref<Material> material);
    static void DrawTriangle(Ref<Transform> transform, Ref<SubTexture2D> subTexture, Vec4 &tint = REN2D_DEFAULT_COLOR);

    static void DrawQuad(Ref<Transform> transform, Vec4 &color);
    static void DrawQuad(Ref<Transform> transform, Ref<Material> material);
    static void DrawQuad(Ref<Transform> transform, Ref<SubTexture2D> subTexture, Vec4 &tint = REN2D_DEFAULT_COLOR);

    static void DrawCube(Ref<Transform> transform, Vec4 &color);
    static void DrawCube(Ref<Transform> transform, Ref<Material> material);
    static void DrawCube(Ref<Transform> transform, Ref<TextureCubemap> cubemap);
    static void DrawCube(Ref<Transform> transform, Ref<SubTexture2D> subTexture, Vec4 &tint = REN2D_DEFAULT_COLOR);

    static void SetSkybox(std::array<string, 6> pathsToFaces);
    static void SetPostProcessingEnabled(bool enabled);
    static void SetWireFrameModeEnabled(bool enabled);

    static void BeginScene(Ref<Camera> camera, Ref<Shader> shaderToUse = nullptr);
    static void NextBatch();
    static void EndScene();

  private:
    static void Reset();
    static void Flush();

    static void DrawQuad(Ref<Transform> transform, TextureData &textureData);
    static void DrawTriangle(Ref<Transform> transform, TextureData &textureData);
    static void DrawCube(Ref<Transform> transform, TextureData &textureData);

    static void AddVertices(VertexData *vertices, uint vertexCount, uint32 *indices, uint32 indexCount);
    static int GetTextureSlotIndex(Ref<Texture2D> texture);
  };
}