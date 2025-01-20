#pragma once

#include "Base/Types.hpp"
#include "Base/Pointers.hpp"
#include "Graphics/Handles.hpp"
#include "Graphics/PrimitiveType.hpp"

namespace Krys::Gfx
{
  struct RenderCommand
  {
    PipelineHandle Pipeline;
    MeshHandle Mesh;
    VertexBufferHandle VBO;
    IndexBufferHandle EBO;
    PrimitiveType Type{PrimitiveType::Triangles};
    uint32 Count;
  };
}