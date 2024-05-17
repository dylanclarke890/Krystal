#pragma once

#include <array>

#include "Core.h"
#include "Graphics/GraphicsContext.h"
#include "Graphics/Camera/Camera.h"

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
    Vec4 Color;
    Vec2 TextureCoords;
    int TextureSlotIndex;
  };

  struct LightSourceVertexData
  {
    Vec4 Position;
  };

  class Renderer2D
  {
  private:
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
    static Ref<Texture2D> WhiteTexture;

  public:
    static void Init(Ref<GraphicsContext> ctx);
    static void Shutdown();

    static void DrawTriangle(Vec3 &pos, Vec2 &size, Vec4 &color, float rotation = 0.0f);
    static void DrawTriangle(Vec3 &pos, Vec2 &size, Ref<Texture2D> texture, float rotation = 0.0f, Vec4 &tint = REN2D_DEFAULT_COLOR);
    static void DrawTriangle(Vec3 &pos, Vec2 &size, Ref<SubTexture2D> subTexture, float rotation = 0.0f, Vec4 &tint = REN2D_DEFAULT_COLOR);
    // TODO: Tiling factor

    static void DrawQuad(Vec3 &pos, Vec2 &size, Vec4 &color, float rotation = 0.0f);
    static void DrawQuad(Vec3 &pos, Vec2 &size, Ref<Texture2D> texture, float rotation = 0.0f, Vec4 &tint = REN2D_DEFAULT_COLOR);
    static void DrawQuad(Vec3 &pos, Vec2 &size, Ref<SubTexture2D> subTexture, float rotation = 0.0f, Vec4 &tint = REN2D_DEFAULT_COLOR);
    // TODO: Tiling factor

    static void DrawCube(Vec3 &pos, Vec3 &size, Vec4 &color, float rotation = 0.0f);
    static void DrawCube(Vec3 &pos, Vec3 &size, Ref<Texture2D> texture, float rotation = 0.0f, Vec4 &tint = REN2D_DEFAULT_COLOR);
    static void DrawCube(Vec3 &pos, Vec3 &size, Ref<SubTexture2D> subTexture, float rotation = 0.0f, Vec4 &tint = REN2D_DEFAULT_COLOR);
    // TODO: Tiling factor

    // TODO: temp
    static void SetLightSourceColor(Vec4 &color);
    static void DrawLightSourceCube(Vec3 &pos, Vec3 &size, float rotation = 0.0f);

    static void BeginScene(Ref<Camera> camera);
    static void NextBatch();
    static void EndScene();

  private:
    static void Reset();
    static void Flush();

    static void DrawQuad(Vec3 &pos, Vec2 &size, float rotation, Vec4 &color, int textureSlotIndex, const Vec2 *textureCoords);
    static void DrawTriangle(Vec3 &pos, Vec2 &size, float rotation, Vec4 &color, int textureSlotIndex, const Vec2 *textureCoords);
    static void DrawCube(Vec3 &pos, Vec3 &size, float rotation, Vec4 &color, int textureSlotIndex, const Vec2 *textureCoords);

    static void AddVertices(VertexData *vertices, uint vertexCount, uint32 *indices, uint32 indexCount);
    static int GetTextureSlotIndex(Ref<Texture2D> texture);
  };
}