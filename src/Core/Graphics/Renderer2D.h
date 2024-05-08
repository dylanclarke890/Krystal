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

  struct VertexData
  {
    Vec3 Position;
    Vec4 Color;
    Vec2 TextureCoords;
  };

  class Renderer2D
  {
  private:
    static Ref<GraphicsContext> Context;

    static Ref<Shader> Shader;
    static Ref<Texture2D> WhiteTexture;

    static Ref<VertexArray> VertexArray;
    static Ref<VertexBuffer> VertexBuffer;
    static Ref<IndexBuffer> IndexBuffer;

    static Unique<std::array<VertexData, KRYS_MAX_VERTICES>> Vertices;
    static uint VertexCount;
    
    static Unique<std::array<uint32, KRYS_MAX_INDICES>> Indices;
    static uint IndexCount;

  public:
    static void Init(Ref<GraphicsContext> ctx);
    static void Shutdown();

    static void DrawTriangle(Vec3 &posA, Vec3 &posB, Vec3 &posC, Vec4 &color);
    static void DrawTriangle(Vec3 &posA, Vec3 &posB, Vec3 &posC, Ref<Texture2D> texture);

    static void DrawQuad(Vec3 &pos, Vec2 &size, Vec4 &color);
    static void DrawQuad(Vec3 &pos, Vec2 &size, Ref<Texture2D> texture);

    static void Begin();
    static void NextBatch();
    static void End();

  private:
    static void AddVertices(VertexData *vertices, uint vertexCount, uint32 *indices, uint32 indexCount);
  };
}