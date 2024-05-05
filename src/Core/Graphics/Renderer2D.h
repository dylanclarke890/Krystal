#pragma once

#include <array>

#include "Krystal.h"
#include "Graphics/GraphicsContext.h"

namespace Krys
{
  constexpr uint KRYS_MAX_TRIANGLES = 10000;
  constexpr uint KRYS_MAX_VERTICES = KRYS_MAX_TRIANGLES * 3;

  struct VertexData
  {
    Vec3 Position;
    Vec4 Color;
  };

  class Renderer2D
  {
  private:
    static Ref<GraphicsContext> Context;
    static Ref<Shader> ColorShader;
    static Ref<VertexArray> VertexArray;
    static Ref<VertexBuffer> VertexBuffer;
    static std::array<VertexData, KRYS_MAX_VERTICES> Vertices;
    static uint VertexCount;

  public:
    static void Init(Ref<GraphicsContext> ctx);
    static void Shutdown();

    static void DrawTriangle(Vec3 &posA, Vec3 &posB, Vec3 &posC, Vec4 &color);
    static void DrawQuad(Vec3 &pos, Vec2 &size, Vec4 &color);

    static void Begin();
    static void End();

  private:
    static void AddVertices(VertexData *vertices, uint count);
  };
}