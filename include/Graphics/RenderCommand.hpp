#pragma once

#include "Base/Types.hpp"
#include "Base/Pointers.hpp"
#include "Graphics/Handles.hpp"
#include "Graphics/PrimitiveType.hpp"

namespace Krys::Gfx
{
  // TODO: right now we support both meshes and VBOs
  // consider splitting this into two separate commands
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