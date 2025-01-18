#pragma once

#include "Types.h"
#include "Maths/Vector.h"
#include "Graphics/BufferLayout.h"
#include "Graphics/Nodes/GeometryNode.h"
#include "Graphics/GraphicsContext.h"

namespace Krys::Gfx
{
  constexpr uint32 MAX_VERTICES_PER_BATCH = 50000;
  constexpr uint32 MAX_INDICES_PER_BATCH = 200000;

  static VertexBufferLayout VERTEX_BUFFER_LAYOUT_BATCH = {
      {ShaderDataType::Float3, "i_Position"},
      {ShaderDataType::Float3, "i_Normal"},
      {ShaderDataType::Float4, "i_Color"},
      {ShaderDataType::Float2, "i_TextureCoords"},
      {ShaderDataType::Float3, "i_Tangent"},
  };

  class Renderer
  {
  public:
    void Init(Ref<GraphicsContext> context) noexcept {}

    void BeginFrame() noexcept {}
    void Submit(const GeometryNode &node) noexcept {}
    void Render() noexcept {}
    void EndFrame() noexcept {}
  };
}