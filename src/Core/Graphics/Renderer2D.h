#pragma once

#include <array>

#include "Krystal.h"
#include "Graphics/GraphicsContext.h"

namespace Krys
{
  constexpr uint KRYS_MAX_TRIANGLES = 10000;
  constexpr uint KRYS_MAX_QUADS = KRYS_MAX_TRIANGLES / 2;
  constexpr uint KRYS_MAX_VERTICES = KRYS_MAX_QUADS * 4;
  constexpr uint KRYS_MAX_INDICES = KRYS_MAX_QUADS * 6;
  constexpr uint KRYS_MAX_TEXTURE_SLOTS = 32; // TODO: get this from the graphics API.

  struct VertexData
  {
    Vec3 Position;
    Vec4 Color;
    Vec2 TextureCoords;
    float TextureSlotIndex;
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

    static void DrawTriangle(Vec3 &posA, Vec3 &posB, Vec3 &posC, Vec4 &color);
    static void DrawTriangle(Vec3 &posA, Vec3 &posB, Vec3 &posC, Ref<Texture2D> texture);
    static void DrawTriangle(Vec3 &posA, Vec3 &posB, Vec3 &posC, Ref<Texture2D> texture, Vec4 &tint);
    static void DrawTriangle(Vec3 &posA, Vec3 &posB, Vec3 &posC, Ref<SubTexture2D> subTexture);
    static void DrawTriangle(Vec3 &posA, Vec3 &posB, Vec3 &posC, Ref<SubTexture2D> subTexture, Vec4 &tint);
    // TODO: tiling factor

    static void DrawQuad(Vec3 &pos, Vec2 &size, Vec4 &color);
    static void DrawQuad(Vec3 &pos, Vec2 &size, Ref<Texture2D> texture);
    static void DrawQuad(Vec3 &pos, Vec2 &size, Ref<Texture2D> texture, Vec4 &tint);
    static void DrawQuad(Vec3 &pos, Vec2 &size, Ref<SubTexture2D> subTexture);
    static void DrawQuad(Vec3 &pos, Vec2 &size, Ref<SubTexture2D> subTexture, Vec4 &tint);
    // TODO: tiling factor

    static void BeginScene();
    static void NextBatch();
    static void EndScene();

  private:
    static void Reset();
    static void AddVertices(VertexData *vertices, uint vertexCount, uint32 *indices, uint32 indexCount);
    static float GetTextureSlotIndex(Ref<Texture2D> texture);
  };
}