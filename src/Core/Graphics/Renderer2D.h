#pragma once

#include <array>

#include "Core.h"
#include "Graphics/GraphicsContext.h"
#include "Graphics/Camera/Camera.h"
#include "Graphics/Transform.h"
#include "Graphics/Mesh.h"

namespace Krys
{
  constexpr uint REN2D_MAX_TRIANGLES = 10000;
  constexpr uint REN2D_MAX_QUADS = REN2D_MAX_TRIANGLES / 2;
  constexpr uint REN2D_MAX_VERTICES = REN2D_MAX_QUADS * 4;
  constexpr uint REN2D_MAX_INDICES = REN2D_MAX_QUADS * 6;
  constexpr uint REN2D_MAX_TEXTURE_SLOTS = 32; // TODO: get this from the graphics API.
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

  class Renderer2D
  {
  private:
    struct LightSourceVertexData
    {
      Vec4 Position;
    };

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

    static Ref<Shader> ObjectShader;
    static Ref<VertexArray> ObjectVertexArray;
    static Ref<VertexBuffer> ObjectVertexBuffer;
    static Ref<IndexBuffer> ObjectIndexBuffer;

    static Ref<Shader> LightSourceShader;
    static Ref<VertexArray> LightSourceVertexArray;
    static Ref<VertexBuffer> LightSourceVertexBuffer;
    static Ref<IndexBuffer> LightSourceIndexBuffer;

    static Unique<std::array<VertexData, REN2D_MAX_VERTICES>> Vertices;
    static uint VertexCount;

    static Unique<std::array<uint32, REN2D_MAX_INDICES>> Indices;
    static uint IndexCount;

    static Unique<std::array<Ref<Texture2D>, REN2D_MAX_TEXTURE_SLOTS>> TextureSlots;
    static int TextureSlotIndex;

    static Ref<Shader> ShaderInUse;
    static Vec4 SceneCameraPosition;

  public:
    static void Init(Ref<GraphicsContext> ctx);
    static void Shutdown();

    static void DrawIndexed(uint count);

    static void DrawTriangle(Ref<Transform> transform, Vec4 &color);
    static void DrawTriangle(Ref<Transform> transform, Ref<Material> material);
    static void DrawTriangle(Ref<Transform> transform, Ref<SubTexture2D> subTexture, Vec4 &tint = REN2D_DEFAULT_COLOR);

    static void DrawQuad(Ref<Transform> transform, Vec4 &color);
    static void DrawQuad(Ref<Transform> transform, Ref<Material> material);
    static void DrawQuad(Ref<Transform> transform, Ref<SubTexture2D> subTexture, Vec4 &tint = REN2D_DEFAULT_COLOR);

    static void DrawCube(Ref<Transform> transform, Vec4 &color);
    static void DrawCube(Ref<Transform> transform, Ref<Material> material);
    static void DrawCube(Ref<Transform> transform, Ref<SubTexture2D> subTexture, Vec4 &tint = REN2D_DEFAULT_COLOR);

    // TODO: temp
    static Ref<Shader> GetObjectShader() { return ObjectShader; }
    static void DrawLightSourceCube(Ref<Transform> transform);

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