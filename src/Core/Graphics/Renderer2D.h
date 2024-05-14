#pragma once

#include <array>

#include "Core.h"
#include "Graphics/GraphicsContext.h"
#include "Graphics/Camera/Camera.h"

namespace Krys
{
  // TODO: we're in the Krys namespace. Prefix these with REN2D instead.
  constexpr uint KRYS_MAX_TRIANGLES = 10000;
  constexpr uint KRYS_MAX_QUADS = KRYS_MAX_TRIANGLES / 2;
  constexpr uint KRYS_MAX_VERTICES = KRYS_MAX_QUADS * 4;
  constexpr uint KRYS_MAX_INDICES = KRYS_MAX_QUADS * 6;
  constexpr uint KRYS_MAX_TEXTURE_SLOTS = 32; // TODO: get this from the graphics API.
  static Vec4 KRYS_DEFAULT_COLOR = {1.0f, 1.0f, 1.0f, 1.0f};

  struct VertexData
  {
    Vec4 Position;
    Vec4 Color;
    Vec2 TextureCoords;
    int TextureSlotIndex;
  };

  class Renderer2D
  {
  private:
    static Ref<GraphicsContext> Context;

    static Ref<Shader> Shader;

    static Ref<VertexArray> VertexArray;
    static Ref<VertexBuffer> VertexBuffer;
    static Ref<IndexBuffer> IndexBuffer;

    static Unique<std::array<VertexData, KRYS_MAX_VERTICES>> Vertices;
    static uint VertexCount;
    
    static Unique<std::array<uint32, KRYS_MAX_INDICES>> Indices;
    static uint IndexCount;

    static Unique<std::array<Ref<Texture2D>, KRYS_MAX_TEXTURE_SLOTS>> TextureSlots;
    static int TextureSlotIndex;
    static Ref<Texture2D> WhiteTexture;

  public:
    static void Init(Ref<GraphicsContext> ctx);
    static void Shutdown();

    static void DrawTriangle(Vec3 &pos, Vec2 &size, Vec4 &color);
    static void DrawTriangle(Vec3 &pos, Vec2 &size, Ref<Texture2D> texture, Vec4 &tint = KRYS_DEFAULT_COLOR);
    static void DrawTriangle(Vec3 &pos, Vec2 &size, Ref<SubTexture2D> subTexture, Vec4 &tint = KRYS_DEFAULT_COLOR);
    // TODO: tiling factor

    static void DrawQuad(Vec3 &pos, Vec2 &size, Vec4 &color);
    static void DrawQuad(Vec3 &pos, Vec2 &size, Ref<Texture2D> texture, Vec4 &tint = KRYS_DEFAULT_COLOR);
    static void DrawQuad(Vec3 &pos, Vec2 &size, Ref<SubTexture2D> subTexture, Vec4 &tint = KRYS_DEFAULT_COLOR);
    // TODO: tiling factor

    static void BeginScene(Ref<Camera> camera);
    static void NextBatch();
    static void EndScene();

  private:
    static void Reset();
    static void Flush();

    static void DrawQuad(Vec3 &pos, Vec2 &size, Vec4 &color, int textureSlotIndex, const Vec2 *textureCoords);
    static void DrawTriangle(Vec3 &pos, Vec2 &size, Vec4 &color, int textureSlotIndex, const Vec2 *textureCoords);

    static void AddVertices(VertexData *vertices, uint vertexCount, uint32 *indices, uint32 indexCount);
    static int GetTextureSlotIndex(Ref<Texture2D> texture);
  };
}